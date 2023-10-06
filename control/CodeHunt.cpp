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
    this->model->setLeaderboard(std::move(fileHandler->readLBFromFile()));
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
    model->setMessage(error);
    if (error) return;

    model->setUserFunc(func);
    auto score = model->evaluateLevels();
    if (score) {
        if (score.value().first != -1)
            model->addScore(score.value().first);
        if (score.value().second) {
            model->setMessage("You have completed all levels!");
            model->getLeaderboard()->addScore({*model->getPlayerScore(), model->getPlayerName()});
            fileHandler->writeLBToFile(model->getLeaderboard());
        }
    }

    dlclose(handle);
}