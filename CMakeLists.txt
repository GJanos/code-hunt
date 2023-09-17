cmake_minimum_required(VERSION 3.24)
project(nhf2)

set(CMAKE_CXX_STANDARD 23)

set(IMGUI_SOURCES
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_impl_glfw.cpp
        imgui/imgui_impl_opengl3.cpp
        )

add_executable(nhf2 main.cpp ${IMGUI_SOURCES})


target_include_directories(nhf2 PRIVATE
        imgui
        imgui/backends
        )

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(nhf2 PRIVATE glfw OpenGL::GL)
