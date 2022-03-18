cmake_minimum_required(VERSION 3.15)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# OpenGL packages
find_package(GLAD REQUIRED)
find_package(GLFW REQUIRED)
find_package(ImGui REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenImageIO REQUIRED)

message(${OpenImageIO_FOUND})

set(BounceGui_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE BounceGui_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(BounceGUI main.cpp
        ${BounceGui_SOURCES}
        ${ImGui_SOURCES} src/App/Events/ApplicationEvent.h src/App/Events/KeyEvent.h)
target_include_directories(BounceGUI PUBLIC
        BounceRender
        C:/dev/BounceRender/dependencies/boost_1_76_0/stage/x64/lib/libboost_filesystem-vc142-mt-gd-x64-1_76.lib
        Boost::filesystem
        OpenImageIO::OpenImageIO
        ${BounceGui_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${ImGui_INCLUDE_DIR}
        OpenGL::GL)
target_link_libraries(BounceGUI PUBLIC
        BounceRender
        C:/dev/BounceRender/dependencies/boost_1_76_0/stage/x64/lib/libboost_filesystem-vc142-mt-gd-x64-1_76.lib
        Boost::filesystem
        OpenImageIO::OpenImageIO
        ${GLFW_LIBRARY}
        ${GLAD_LIBRARIES}
        OpenGL::GL)
