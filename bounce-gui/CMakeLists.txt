cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(glfw3_DIR /usr/local/lib/cmake/glfw)

## Find dependencies
find_package(glfw3 3.1.2 REQUIRED)
set(GFLW_DEPENDENCIES dl X11 Xi Xcursor Xinerama Xrandr Xxf86vm pthread)

find_package(glew REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(imgui REQUIRED)

# Add bounce-render target and link its includes & libraries
add_executable(BounceGUI main.cpp)
target_include_directories(BounceGUI PRIVATE ${GLFW3_INCLUDE_DIR} src)
target_link_libraries(BounceGUI PUBLIC glfw3 GLEW::GLEW ${GFLW_DEPENDENCIES}
#        imgui::imgui
)
