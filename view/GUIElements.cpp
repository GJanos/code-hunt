#include "GUIElements.h"

using namespace gj;

int TextFieldElement::id = 1;

LabelElement::LabelElement(std::string label_txt, Attribute attr) :
        label_txt(std::move(label_txt)), attr(attr) {}

void LabelElement::render() {
    const auto &[r, g, b, a] = attr.color;

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
    ImGui::SetCursorPos(attr.coord);
    ImGui::TextUnformatted(label_txt.c_str());
    ImGui::PopStyleColor();
}


ButtonElement::ButtonElement(std::string button_txt, Attribute attr,
                             std::function<void()> onClick) :
        button_txt(std::move(button_txt)), attr(attr),
        onClick(std::move(onClick)) {}

void ButtonElement::render() {
    const auto &[r, g, b, a] = attr.color;

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
    ImGui::SetCursorPos(attr.coord);
    if (ImGui::Button(button_txt.c_str(), attr.size)) {
        if (onClick) {
            onClick();
        }
    }
    ImGui::PopStyleColor();
}

TextFieldElement::TextFieldElement(TextType label_content, const Attribute &attr)
        : label_content(std::move(label_content)), attr(attr) {
    id_str = "##" + std::to_string(id++);
}

void TextFieldElement::render() {
    const auto &[r, g, b, a] = attr.color;

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
    ImGui::SetCursorPos(attr.coord);
    ImGui::InputTextMultiline(id_str.c_str(), label_content->data(), label_content->size(),
                              attr.size, ImGuiInputTextFlags_AllowTabInput);
    ImGui::PopStyleColor();
}

ScoreElement::ScoreElement(std::shared_ptr<int> score, Attribute attr) :
        player_score(std::move(score)), attr(attr) {}

void ScoreElement::render() {
    const auto &[r, g, b, a] = attr.color;

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
    ImGui::SetCursorPos(attr.coord);
    ImGui::Text("%d", *player_score);
    ImGui::PopStyleColor();
}

TestTableElement::TestTableElement(std::shared_ptr<std::set<Evaluation, decltype(cmp_eval)>> eval,
                                   Attribute attr)
        : evaluations(std::move(eval)), attr(attr) {}


void TestTableElement::render() {
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;

    ImGui::SetCursorPos(attr.coord);
    if (ImGui::BeginTable("##TestCases", 4, flags, attr.size)) {
        ImGui::TableSetupColumn("Passed");
        ImGui::TableSetupColumn("Test");
        ImGui::TableSetupColumn("Expected");
        ImGui::TableSetupColumn("Actual");
        ImGui::TableHeadersRow();

        for (const auto &eval: *evaluations) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", eval.passed ? "True" : "False");

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", eval.user_input);

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%d", eval.expected_output);

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%d", eval.actual_output);
        }
        ImGui::EndTable();
    }
}


LBTableElement::LBTableElement(std::shared_ptr<std::vector<Score>> curr_best_scores, Attribute attr) :
        curr_best_scores(std::move(curr_best_scores)), attr(attr) {}


void LBTableElement::render() {
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;

    ImGui::SetCursorPos(attr.coord);
    if (ImGui::BeginTable("##Leaderboard", 4, flags, attr.size)) {
        ImGui::TableSetupColumn("Rank");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Score");
        ImGui::TableHeadersRow();

        for (int i = 0; i < curr_best_scores->size(); ++i) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", i + 1);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", curr_best_scores->at(i).player_name.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%d", curr_best_scores->at(i).score);
        }
        ImGui::EndTable();
    }
}