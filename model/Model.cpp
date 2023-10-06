#include <cstring>
#include "Model.h"

using namespace gj;

Model::Model(std::initializer_list<Level> init_levels) :
        error_message(std::nullopt),
        user_func_name("hunt"),
        levelEvaluator(std::make_unique<LevelEvaluator>(init_levels)),
        player_score(std::make_shared<int>(0)),
        player_name("Player") {
    textManager = std::make_unique<TextManager>();
    pre_included_headers = R"(
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <functional>
extern "C" )";
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

std::string Model::getPlayerName() {
    return player_name;
}

void Model::setPlayerName(std::string name) {
    player_name = std::move(name);
}

void Model::setMessage(const std::optional<std::string> &error) {
    error_message = error;
}

std::optional<std::string> Model::getError() const {
    return error_message;
}

std::string Model::getPreIncludedHeaders() {
    return pre_included_headers;
}

std::optional<std::pair<int, bool>> Model::evaluateLevels() {
    return levelEvaluator->evaluateLevel();
}

void Model::setUserFunc(UserFuncType user_func) {
    levelEvaluator->setUserFunc(user_func);
}

std::shared_ptr<EvaluationsType> Model::getEvaluations() {
    return levelEvaluator->getEvaluations();
}

void Model::addScore(int score) {
    *player_score += score;
}

void Model::setLeaderboard(std::unique_ptr<Leaderboard> &&leaderboard) {
    this->leaderboard = std::move(leaderboard);
}

std::unique_ptr<Leaderboard> &Model::getLeaderboard() {
    return leaderboard;
}

int Model::getLevelCount() const {
    return levelEvaluator->getLevelCount();
}

std::shared_ptr<int> Model::getCurrentLevel() {
    return levelEvaluator->getCurrentLevel();
}

TextType Model::TextManager::requestText(const std::string &key, const std::string &default_text) {
    auto new_text = std::make_shared<std::array<char, 1024>>();
    std::strcpy(new_text->data(), default_text.c_str());
    return texts.emplace(key, new_text).first->second;
}

TextType Model::TextManager::getText(const std::string &key) {
    return texts.at(key);
}
