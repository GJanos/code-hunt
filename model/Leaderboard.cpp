#include <algorithm>
#include "Leaderboard.h"

using namespace gj;

Score::Score() : score(0), player_name("") {}

Score::Score(int score, std::string player_name) :
        score(score), player_name(std::move(player_name)) {}

Leaderboard::Leaderboard(int size) : leaderboard_size(size), scores(std::make_shared<std::vector<Score>>()) {}

void Leaderboard::addScore(const Score &score) {
    scores->push_back(score);
    std::sort(scores->begin(), scores->end(), [](const Score &a, const Score &b) {
        return a.score > b.score;
    });
    if (scores->size() > leaderboard_size) {
        scores->resize(leaderboard_size);
    }
}

std::shared_ptr<std::vector<Score>> Leaderboard::getScores() {
    return scores;
}

