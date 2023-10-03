#include "Model.h"

using namespace gj;

Model::Model() {
    textManager = std::make_unique<TextManager>();
    player_score = std::make_shared<int>(0);
    player_name = "Player";
}

TextType Model::requestText(const std::string &key, const std::string &default_text) {
    return textManager->requestText(key, default_text);
}

TextType Model::getText(const std::string &key) {
    return textManager->getText(key);
}

std::shared_ptr<int> Model::getPlayerScore() {
    return player_score;
}

void Model::setPlayerScore(int score) {
    *player_score = score;
}

std::string Model::getPlayerName() {
    return player_name;
}

void Model::setPlayerName(std::string name) {
    player_name = std::move(name);
}

TextType Model::TextManager::requestText(const std::string &key, const std::string &default_text) {
    auto new_text = std::make_shared<std::array<char, 1024>>();
    std::strcpy(new_text->data(), default_text.c_str());
    return texts.emplace(key, new_text).first->second;
}

TextType Model::TextManager::getText(const std::string &key) {
    return texts.at(key);
}