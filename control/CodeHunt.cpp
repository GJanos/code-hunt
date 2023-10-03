#include "CodeHunt.h"

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


    model->setPlayerScore(*(model->getPlayerScore()) + 1);
}