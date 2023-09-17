#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main(int argc, char** argv)
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Integration", NULL, NULL);
    if (window == NULL)
        return 1;

    glfwMakeContextCurrent(window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui test window
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is a simple ImGui window.");
        ImGui::End();

        // Rendering
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}



/*
 * Classes:
 * App
 *
 * Window
 *
 * AppWindow
 *
 * CodeInputWindow
 *
 * TestWindow
 *
 * EvaluateWindow
 *
 * InputFileHandler
 *
 *
 */