#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <memory>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "LevelEvaluator.h"
#include "Leaderboard.h"


namespace gj {

    using TextType = std::shared_ptr<std::array<char, 1024>>;

    struct Attribute {
        ImVec2 coord;
        ImVec4 color;
        ImVec2 size;
    };

// Interface for GUI elements
    class IGuiElement {
    public:
        virtual ~IGuiElement() = default;

        virtual void render() = 0;  // Pure virtual function
    };


    class LabelElement : public IGuiElement {
    public:
        LabelElement(std::string label_txt, Attribute attr);

        void render() override;

    private:
        std::string label_txt;
        Attribute attr;
    };


    class ButtonElement : public IGuiElement {
    public:
        ButtonElement(std::string button_txt, Attribute attr,
                               std::function<void()> onClick);

        void render() override;

    private:
        std::string button_txt;
        Attribute attr;
        std::function<void()> onClick;
    };


    class TextFieldElement : public IGuiElement {
    public:
        TextFieldElement(TextType label_content, const Attribute &attr);

        void render() override;
    private:
        TextType label_content;
        Attribute attr;
        static int id;
        std::string id_str;
    };

    class ScoreElement : public IGuiElement {
        std::shared_ptr<int> player_score;
        Attribute attr;

    public:
        ScoreElement(std::shared_ptr<int> score, Attribute attr);

        void render() override;
    };


    class TestTableElement : public IGuiElement {
        std::shared_ptr<EvaluationsType> evaluations;
        Attribute attr;
    public:
        TestTableElement(std::shared_ptr<EvaluationsType> eval, Attribute attr);

        void render() override;
    };


    class LBTableElement : public IGuiElement {
        std::shared_ptr<std::vector<Score>> curr_best_scores;
        Attribute attr;
    public:
        LBTableElement(std::shared_ptr<std::vector<Score>> curr_best_scores, Attribute attr);

        void render() override;
    };
}


