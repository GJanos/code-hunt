#pragma once

#include <utility>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <cstring>
#include <array>
#include <functional>


#include "Model.h"
#include "View.h"
#include "FileHandler.h"


namespace gj {

    class CodeHunt {
    private:
        Model *model;
        View *view;
        std::unique_ptr<FileHandler> fileHandler;

    public:
        CodeHunt();

        void start();

        void addModel(Model *model);

        void addView(View *view);

        void onHuntButtonClicked();
    };
}




