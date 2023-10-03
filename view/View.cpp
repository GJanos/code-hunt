#include "View.h"

using namespace gj;

View::View(int w, int h, Model *m) :
        wWidth(w), wHeight(h), model(m) {

    buttons["HUNT"] = []() {};

    std::unique_ptr<IGuiElement> title_label
            = std::make_unique<LabelElement>("Code Hunt",
                                             Attribute{
                                                     ImVec2{(wWidth - 50) * 0.5f, 20},
                                                     ImVec4{0, 0, 255, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(title_label));

    std::unique_ptr<IGuiElement> name_label
            = std::make_unique<LabelElement>("Name: ",
                                             Attribute{
                                                     ImVec2{(wWidth - 70) * 0.5f, 40},
                                                     ImVec4{109, 164, 252, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(name_label));

    auto name = model->requestText("player_name", "Player");
    std::unique_ptr<IGuiElement> name_text =
            std::make_unique<TextFieldElement>(
                    name,
                    Attribute{
                            ImVec2{wWidth * 0.5f + 20, 40},
                            ImVec4{109, 164, 252, 255},
                            ImVec2{100, 20}});
    guiElements.push_back(std::move(name_text));

    std::unique_ptr<IGuiElement> user_code_label
            = std::make_unique<LabelElement>("User Code",
                                             Attribute{
                                                     ImVec2{(wWidth / 2 - 50) * 0.5f, 100},
                                                     ImVec4{0, 255, 0, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(user_code_label));

    auto code = model->requestText("player_code", "/*** Necessary headers already included! ***/\n\n"
                                                  "int hunt(int x) {\n"
                                                  "    /* Write your solution \n"
                                                  "    inside this function */\n"
                                                  "}");
    std::unique_ptr<IGuiElement> code_text = std::make_unique<TextFieldElement>(
            code,
            Attribute{
                    ImVec2{10, 130},
                    ImVec4{255, 255, 255, 255},
                    ImVec2{380, 250}});
    guiElements.push_back(std::move(code_text));

    std::unique_ptr<IGuiElement> hunt_button = std::make_unique<ButtonElement>(
            "HUNT",
            Attribute{
                    ImVec2{wWidth / 2 * 0.5f - 50, 400},
                    ImVec4{255, 0, 0, 255},
                    ImVec2{100, 30}},
            [&]() { buttons["HUNT"](); }
    );
    guiElements.push_back(std::move(hunt_button));

    std::unique_ptr<IGuiElement> score_label
            = std::make_unique<LabelElement>("Score: ",
                                             Attribute{
                                                     ImVec2{(wWidth / 2 - 100) * 0.5f, 440},
                                                     ImVec4{217, 101, 93, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(score_label));

    std::unique_ptr<IGuiElement> score_text
            = std::make_unique<ScoreElement>(model->getPlayerScore(),
                                             Attribute{
                                                     ImVec2{(wWidth / 2 + 20) * 0.5f, 440},
                                                     ImVec4{217, 101, 93, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(score_text));
}

int View::update() {

    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(wWidth, wHeight, "Code Hunt", NULL, NULL);
    if (window == NULL)
        return 1;

    glfwMakeContextCurrent(window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    while (!glfwWindowShouldClose(window)) {
        // Initialization and Setup
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;

        // Main Window
        ImGui::SetNextWindowSize(ImVec2(wWidth, wHeight));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Code Hunt", NULL,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        /// Render GUI elements of the Code Hunt game
        for (const auto &guiElement: guiElements) {
            guiElement->render();
        }

        // Rendering
        ImGui::End();
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
}

void View::setButtonClickListener(const std::string &button_id, std::function<void()> onClick) {
    buttons[button_id] = std::move(onClick);
}

