#include "View.h"

using namespace gj;

View::View(int w, int h, Model *m) :
        wWidth(w), wHeight(h), model(m) {

    buttons["HUNT"] = []() {};
    errorBox = std::nullopt;

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
                                                     ImVec2{(wWidth - 70) * 0.5f, 60},
                                                     ImVec4{109, 164, 252, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(name_label));

    auto name = model->requestText("player_name", "Player");
    std::unique_ptr<IGuiElement> name_text =
            std::make_unique<TextFieldElement>(
                    name,
                    Attribute{
                            ImVec2{wWidth * 0.5f + 20, 60},
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

    auto code = model->requestText("player_code",
                                   "int hunt(int x) {\n"
                                   "/* Necessary headers already included!\n"
                                   "    Write your solution \n"
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

    std::unique_ptr<IGuiElement> test_label
            = std::make_unique<LabelElement>("Test cases",
                                             Attribute{
                                                     ImVec2{(wWidth + 300) * 0.5f, 100},
                                                     ImVec4{255, 165, 0, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(test_label));

    std::unique_ptr<IGuiElement> test_table
            = std::make_unique<TestTableElement>(model->getEvaluations(),
                                                 Attribute{
                                                         ImVec2{(wWidth + 100) * 0.5f, 130},
                                                         ImVec4{0, 0, 0, 0},
                                                         ImVec2{300, 200}});
    guiElements.push_back(std::move(test_table));

    std::unique_ptr<IGuiElement> leaderboard_label
            = std::make_unique<LabelElement>("Leaderboard",
                                             Attribute{
                                                     ImVec2{(wWidth + 300) * 0.5f, 400},
                                                     ImVec4{219, 206, 15, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(leaderboard_label));

    std::unique_ptr<IGuiElement> leaderboard_table
            = std::make_unique<LBTableElement>(model->getLeaderboard()->getScores(),
                                                        Attribute{
                                                                ImVec2{(wWidth + 100) * 0.5f, 430},
                                                                ImVec4{0, 0, 0, 0},
                                                                ImVec2{300, 100}});
    guiElements.push_back(std::move(leaderboard_table));


    std::unique_ptr<IGuiElement> level_label
            = std::make_unique<LabelElement>("Level: " + std::to_string(model->getLevelCount()) + " / ",
                                             Attribute{
                                                     ImVec2{(wWidth / 2 - 100) * 0.5f, 470},
                                                     ImVec4{3, 252, 177, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(level_label));

    std::unique_ptr<IGuiElement> curr_level_text
            = std::make_unique<ScoreElement>(model->getCurrentLevel(),
                                             Attribute{
                                                     ImVec2{(wWidth / 2 + 50) * 0.5f, 470},
                                                     ImVec4{3, 252, 177, 255},
                                                     ImVec2{0, 0}});
    guiElements.push_back(std::move(curr_level_text));

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
        renderError();

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

void View::renderError() {
    auto error = model->getError();
    if (error) {
        setError(*error);
        errorBox->get()->render();
    } else {
        errorBox = std::nullopt;
    }
}


void View::setError(const std::string &error_msg) {
    errorBox = std::make_unique<LabelElement>(error_msg,
                                              Attribute{
                                                      ImVec2{100, 500},
                                                      ImVec4{255, 0, 0, 255},
                                                      ImVec2{0, 0}});
}


