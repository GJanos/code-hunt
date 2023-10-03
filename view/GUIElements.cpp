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