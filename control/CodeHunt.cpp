#include "CodeHunt.h"
#include "Exception.h"

#include <dlfcn.h>

using namespace gj;

CodeHunt::CodeHunt() : model(nullptr), view(nullptr) {
    fileHandler = std::make_unique<FileHandler>("../test.cpp");
}


void CodeHunt::start() {
    view->update();
}

void CodeHunt::addModel(Model *model) {
    this->model = model;
}

void CodeHunt::addView(View *view) {
    this->view = view;
}

void CodeHunt::onHuntButtonClicked() {
    model->setPlayerName(model->getText("player_name")->data());
    std::string user_typed_code = model->getText("player_code")->data();

    void *handle;
    std::string complete_code = model->getPreIncludedHeaders() + user_typed_code;
    auto [error, func] = fileHandler->getUserFunction(complete_code, handle);
    model->setError(error);
    if (error) return;

    /// todo 0 to be changed to current level
    for (auto [input, expected]: model->getLevels()[0].cases) {
        auto actual = func(input);
        std::cout << "input: " << input
                  << " expected: " << expected
                  << " actual: " << actual
                  << std::endl;
    }


    model->setPlayerScore(*(model->getPlayerScore()) + 1);


    dlclose(handle);
}