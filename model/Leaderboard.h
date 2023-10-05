#pragma once

#include <string>
#include <vector>
#include <memory>

namespace gj{

    struct Score {
        int score;
        std::string player_name;

        Score();
        Score(int score, std::string player_name);
    };

    class Leaderboard {

        public:

        explicit Leaderboard(int size);

        void addScore(const Score& score);

        std::shared_ptr<std::vector<Score>> getScores();

        private:
        int leaderboard_size;

        std::shared_ptr<std::vector<Score>> scores;
    };

}



