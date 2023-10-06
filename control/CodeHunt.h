#pragma once

#include "Model.h"
#include "View.h"
#include "FileHandler.h"

namespace gj {

    typedef int (*UserFuncType)(int);

    class CodeHunt {

    public:
        CodeHunt();

        void start();

        void addModel(Model *model);

        void addView(View *view);

        void onHuntButtonClicked();

    private:
        Model *model;
        View *view;
        std::unique_ptr<FileHandler> fileHandler;
    };
}




