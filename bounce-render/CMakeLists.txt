# Find external dependencies
find_package(embree 3.0 REQUIRED)
find_package(OpenImageIO REQUIRED)
find_package(Alembic REQUIRED)
find_package(Imath REQUIRED)

# Get all source files
file(GLOB_RECURSE SOURCES_FILES src/*.cpp)

# Exporting all the symbols on windows to force the .lib creation
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

# Add BounceRender target and link its includes & libraries
add_library(BounceRender SHARED ${SOURCES_FILES})
target_include_directories(BounceRender PRIVATE src embree Alembic::Alembic OpenImageIO::OpenImageIO Imath::Imath)
target_include_directories(BounceRender PRIVATE src PUBLIC include)
target_link_libraries(BounceRender PUBLIC
        embree
        Alembic::Alembic
        OpenImageIO::OpenImageIO
        Imath::Imath)

if(NOT DONT_BUILD_TESTS)
    add_executable(test_SimpleRender tests/simple_render.cpp)
    target_link_libraries(test_SimpleRender PUBLIC
            OpenImageIO::OpenImageIO
            Alembic::Alembic
            BounceRender)

endif()