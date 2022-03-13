# Find external dependencies
find_package(embree 3.0 REQUIRED)
find_package(OpenImageIO REQUIRED)
find_package(Alembic REQUIRED)

# Get all source files
file(GLOB_RECURSE SOURCES_FILES src/*)

# Add BounceRender target and link its includes & libraries
add_library(BounceRender SHARED ${SOURCES_FILES})
target_include_directories(BounceRender PUBLIC src $ENV{IlmBase_INCLUDE_DIR})
target_link_libraries(BounceRender embree Alembic OpenImageIO)
