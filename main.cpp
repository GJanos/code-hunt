#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "file/FileHandler.h"
#include "file/Exception.h"

#include "CodeHunt.h"
#include "Model.h"
#include "View.h"

using namespace gj;


void drawTitle() {
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));
    ImVec2 title_size = ImGui::CalcTextSize("Code Hunt");
    ImGui::SetCursorPosX((800 - title_size.x) * 0.5f);
    ImGui::TextUnformatted("Code Hunt");
    ImGui::PopStyleColor();

    // New components
    ImGui::NewLine();

    static char name[64] = "";  // Buffer to hold name

    // Calculate center alignment for "Name:" and the input field
    float center_pos = 800 * 0.5f;
    float total_elements_width = ImGui::CalcTextSize("Name: ").x + 100;  // 70 for the input box
    float starting_pos = center_pos - (total_elements_width * 0.5f);


    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(109, 164, 252, 255));
    ImGui::SetCursorPosX(starting_pos);
    ImGui::Text("Name: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);  // Set input box width to 70 pixels
    ImGui::InputText("##Name", name, sizeof(name));
    ImGui::PopStyleColor();
}


void drawUserCodeSegment(float &y_position, char *user_code, size_t buffer_size) {
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
    ImVec2 user_code_size = ImGui::CalcTextSize("User Code");
    ImGui::SetCursorPosX((400 - user_code_size.x) * 0.5f);
    ImGui::TextUnformatted("User Code");
    ImGui::PopStyleColor();
    y_position = ImGui::GetCursorPosY();
    ImGui::NewLine();
    ImGui::InputTextMultiline("##UserCode", user_code, buffer_size, ImVec2(400, 300),
                              ImGuiInputTextFlags_AllowTabInput);
}

void drawTestCasesSegment() {
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 165, 0, 255));
    ImGui::SetCursorPosX(400 + (400 - ImGui::CalcTextSize("Test Cases").x) * 0.5f);
    ImGui::TextUnformatted("Test Cases");
    ImGui::PopStyleColor();
    ImGui::NewLine();
    ImGui::SetCursorPosX(450);

    if (ImGui::BeginTable("##TestCases", 4)) {
        ImGui::TableSetupColumn("Passed");
        ImGui::TableSetupColumn("Test");
        ImGui::TableSetupColumn("Expected");
        ImGui::TableSetupColumn("Actual");
        ImGui::TableHeadersRow();

        for (int row = 0; row < 3; row++) {
            ImGui::TableNextRow();
            for (int col = 0; col < 4; col++) {
                ImGui::TableSetColumnIndex(col);
                ImGui::Text("Data %d,%d", row, col);
            }
        }
        ImGui::EndTable();
    }
}

void button_pressed(char *user_code, int player_score, bool &compilationSuccess, std::string &errorMessage) {


    try {
        FileHandler f("../test.cpp");
        f.write(user_code);
        f.compile_user_code();
        compilationSuccess = true;
    } catch (const FileException &e) {
        compilationSuccess = false;
        errorMessage = "File Error: " + std::string(e.what());
    } catch (const CompilationException &e) {
        compilationSuccess = false;
        errorMessage = "Compilation Error: " + std::string(e.what());
    } catch (const std::exception &e) {
        compilationSuccess = false;
        errorMessage = "Unexpected Error: " + std::string(e.what());
    }

    if (!compilationSuccess) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));  // Red text
        ImGui::Text("Error: %s", errorMessage.c_str());
        ImGui::PopStyleColor();
    }
}

void drawHuntButton(float y_position, char *user_code, int player_score, bool &compilationSuccess,
                    std::string &errorMessage) {
    ImGui::SetCursorPosY(y_position + 50);
    ImGui::SetCursorPosX((400 - ImGui::CalcTextSize("HUNT").x) * 0.5f);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 0, 0, 255));
    float buttonEndPosY = ImGui::GetCursorPosY();
    if (ImGui::Button("HUNT", ImVec2(100, 30))) {
        button_pressed(user_code, player_score, compilationSuccess, errorMessage);
    }
    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(buttonEndPosY + 50);
    ImGui::SetCursorPosX((400 - ImGui::CalcTextSize("Score: ").x) * 0.5f);

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(217, 101, 93, 255));
    ImGui::Text("Score: ");
    ImGui::SameLine();
    ImGui::Text("%d", player_score);
    ImGui::PopStyleColor();
}

void drawLeaderboardTable(float y_position) {

    ImGui::SetCursorPosY(y_position - 200);
    ImGui::SetCursorPosX((400 + (400 - ImGui::CalcTextSize("Leaderboard").x) * 0.5f));
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(219, 206, 15, 255));
    ImGui::TextUnformatted("Leaderboard");
    ImGui::PopStyleColor();

    ImGui::SetCursorPosX(500);
    if (ImGui::BeginTable("##Leaderboard", 3)) {
        ImGui::TableSetupColumn("Rank");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Score");
        ImGui::TableHeadersRow();

        for (int row = 0; row < 5; row++) {
            ImGui::TableNextRow();
            for (int col = 0; col < 3; col++) {
                ImGui::TableSetColumnIndex(col);
                ImGui::Text("Data %d,%d", row, col);
            }
        }
        ImGui::EndTable();
    }
}

int main(int argc, char **argv) {

    CodeHunt codeHunt;

    Model model({
                        {"Mul3", {{0, 0}, {1, 3}, {5, 15}, {34, 102}}},
                        {"Div5Mul3", {{0, 0}, {5, 3}, {25, 15}, {45, 27}}}
                });

    View view(800, 600, &model);
    view.setButtonClickListener("HUNT", [&]() { codeHunt.onHuntButtonClicked(); });

    codeHunt.addModel(&model);
    codeHunt.addView(&view);

    codeHunt.start();

    return 0;
}