#pragma once


#include <utility>
#include <vector>
#include <memory>
#include <optional>

#include "Model.h"
#include "GUIElements.h"

namespace gj {

    class View {
        const int wWidth, wHeight;

        std::vector<std::unique_ptr<IGuiElement>> guiElements;
        std::unordered_map<std::string, std::function<void()>> buttons;
        std::optional<std::unique_ptr<IGuiElement>> errorBox;

        Model *model;


    public:
        View(int w, int h, Model *m);

        int update();

        void setButtonClickListener(const std::string &button_id, std::function<void()> onClick);

        void setError(const std::string &error_msg);

    private:
        void renderError();
    };

}



