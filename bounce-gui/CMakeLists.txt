cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# OpenGL packages
find_package(GLAD REQUIRED)
find_package(GLFW REQUIRED)
find_package(ImGui REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)
#find_package(OpenImageIO REQUIRED)

set(Rebound_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE Rebound_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(Rebound main.cpp
        ${Rebound_SOURCES}
        ${ImGui_SOURCES})
target_include_directories(Rebound PUBLIC
#        BounceRender
        ${Rebound_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${ImGui_INCLUDE_DIR}
        OpenGL::GL
        Boost::boost)
target_link_libraries(Rebound PUBLIC
#        BounceRender
        C:/dev/BounceRender/dependencies/boost_1_76_0/stage/x64/lib/libboost_filesystem-vc142-mt-gd-x64-1_76.lib
        ${GLFW_LIBRARY}
        ${GLAD_LIBRARIES}
        glm::glm
        OpenGL::GL
        Boost::boost)
