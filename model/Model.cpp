#include "Model.h"

using namespace gj;

Model::Model(std::initializer_list<Level> init_levels) :
        error_message(std::nullopt),
        user_func_name("hunt"),
        levels(init_levels),
        player_score(std::make_shared<int>(0)),
        player_name("Player"),
        num_of_tries(0),
        current_level(0) {
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

void Model::setPlayerScore(int score) {
    *player_score = score;
}

std::string Model::getPlayerName() {
    return player_name;
}

void Model::setPlayerName(std::string name) {
    player_name = std::move(name);
}

void Model::setError(const std::optional<std::string> &error) {
    error_message = error;
}

std::optional<std::string> Model::getError() const {
    return error_message;
}

std::string Model::getUserFuncName() {
    return user_func_name;
}

std::string Model::getPreIncludedHeaders() {
    return pre_included_headers;
}

std::vector<Level> &Model::getLevels() {
    return levels;
}

TextType Model::TextManager::requestText(const std::string &key, const std::string &default_text) {
    auto new_text = std::make_shared<std::array<char, 1024>>();
    std::strcpy(new_text->data(), default_text.c_str());
    return texts.emplace(key, new_text).first->second;
}

TextType Model::TextManager::getText(const std::string &key) {
    return texts.at(key);
}

Model::Evaluation::Evaluation(bool passed, int user_input, int expected_output, int actual_output)
        : passed(passed), user_input(user_input), expected_output(expected_output),
          actual_output(actual_output) {}
