#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Attribute {
    ImVec2 coord;
    Color color;
    ImVec2 size;
};

// Interface for GUI elements
class IGuiElement {
public:
    virtual ~IGuiElement() = default;
    virtual void render() = 0;  // Pure virtual function
};

class IComposableElement : public IGuiElement {
public:
    virtual void addLabel(const std::string& label, const Attribute& atr) = 0;
    virtual void addChildElement(std::unique_ptr<IGuiElement>&& child) = 0;
private:
    virtual void renderLabel(const std::pair<std::string, Attribute>& label) = 0;
};


// Base GUI Element class implementing the interface
class Element : public IComposableElement {
public:

    std::unordered_map<std::string, Attribute> labels;  // Map for label texts and coordinates
    std::vector<std::unique_ptr<IGuiElement>> childElements;  // Vector for child elements

    void render() override {
        // Default behavior
        if(!labels.empty()) {
            for(const auto& label : labels) {
                renderLabel(label);
            }
        }

        // Render child elements
        if(!childElements.empty()){
            for(const auto& child : childElements) {
                child->render();
            }
        }
    }

    void addLabel(const std::string& label, const Attribute& atr) override {
        labels.emplace(label, atr);
    }

    void addChildElement(std::unique_ptr<IGuiElement>&& child) override {
        childElements.push_back(std::move(child));
    }

private:
    void renderLabel(const std::pair<std::string, Attribute>& label) override {
        const auto& [label_name, attr] = label;
        const auto& [r, g, b, a] = attr.color;

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
        ImGui::SetCursorPos(ImVec2{attr.coord.x, attr.coord.y});
        ImGui::TextUnformatted(label_name.c_str());
        ImGui::PopStyleColor();
    }
};

//void drawTitle() {
//    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));
//    ImVec2 title_size = ImGui::CalcTextSize("Code Hunt");
//    ImGui::SetCursorPosX((800 - title_size.x) * 0.5f);
//    ImGui::TextUnformatted("Code Hunt");
//    ImGui::PopStyleColor();
//
//    // New components
//    ImGui::NewLine();
//
//    static char name[64] = "";  // Buffer to hold name
//
//    // Calculate center alignment for "Name:" and the input field
//    float center_pos = 800 * 0.5f;
//    float total_elements_width = ImGui::CalcTextSize("Name: ").x + 100;  // 70 for the input box
//    float starting_pos = center_pos - (total_elements_width * 0.5f);
//
//
//    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(109, 164, 252, 255));
//    ImGui::SetCursorPosX(starting_pos);
//    ImGui::Text("Name: ");
//    ImGui::SameLine();
//    ImGui::SetNextItemWidth(100);  // Set input box width to 70 pixels
//    ImGui::InputText("##Name", name, sizeof(name));
//    ImGui::PopStyleColor();
//}

// Specific GUI Element: Button
class ButtonElement : public IGuiElement {
public:
    void render() override {
        // Button specific functionality
    }
};

// Specific GUI Element: TextField
class TextFieldElement : public IGuiElement {
    Attribute attr;
    char label_content[2048];
    static int id;
    char id_str[10] = "##";
public:
    explicit TextFieldElement(std::string default_text, Attribute attr) : attr(attr) {
        strcpy(label_content, default_text.c_str());
        strcat(id_str, std::to_string(id++).c_str());
    }

    void render() override {
        const auto& [r, g, b, a] = attr.color;

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a));
        ImGui::SetCursorPos(ImVec2{attr.coord.x, attr.coord.y});
        ImGui::InputTextMultiline(id_str, label_content, sizeof(label_content),
                                  attr.size,
                                  ImGuiInputTextFlags_AllowTabInput);
        ImGui::PopStyleColor();
    }
};

class TableElement : public IGuiElement {
public:
    void render() override {
        // Text field specific functionality
    }
};

// CodeHunt class containing a GUI element
class CodeHunt {
private:
    std::unique_ptr<IGuiElement> guiElement;

public:
    CodeHunt(std::unique_ptr<IGuiElement>&& elem) : guiElement(std::move(elem)) {}

    void start() {
        guiElement->render();
    }
};


