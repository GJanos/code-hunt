cmake_minimum_required(VERSION 3.24)
project(nhf2)

set(CMAKE_CXX_STANDARD 23)

set(IMGUI_SOURCES
        imgui_ui/imgui.cpp
        imgui_ui/imgui_draw.cpp
        imgui_ui/imgui_widgets.cpp
        imgui_ui/imgui_tables.cpp
        imgui_ui/imgui_impl_glfw.cpp
        imgui_ui/imgui_impl_opengl3.cpp)

include_directories(${CMAKE_SOURCE_DIR}/control)
include_directories(${CMAKE_SOURCE_DIR}/view)
include_directories(${CMAKE_SOURCE_DIR}/model)
include_directories(${CMAKE_SOURCE_DIR}/file)

add_executable(nhf2
        main.cpp
        ${IMGUI_SOURCES}
        file/FileHandler.cpp
        file/Exception.cpp
        view/View.cpp
        control/CodeHunt.cpp
        model/Model.cpp
        view/GUIElements.cpp)


target_include_directories(nhf2 PRIVATE
        imgui_ui)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(nhf2 PRIVATE glfw OpenGL::GL)
