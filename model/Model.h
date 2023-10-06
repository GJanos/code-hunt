#pragma once

#include <unordered_map>

#include "LevelEvaluator.h"
#include "Leaderboard.h"

namespace gj {
    using TextType = std::shared_ptr<std::array<char, 1024>>;

    class Model {
    public:
        Model(std::initializer_list<Level> init_levels);

        TextType requestText(const std::string &key, const std::string &default_text);

        TextType getText(const std::string &key);

        std::shared_ptr<int> getPlayerScore();

        void addScore(int score);

        std::string getPlayerName();

        void setPlayerName(std::string name);

        std::string getPreIncludedHeaders();

        void setMessage(const std::optional<std::string> &error);

        std::optional<std::string> getError() const;

        std::optional<std::pair<int, bool>> evaluateLevels();

        void setUserFunc(UserFuncType user_func);

        std::shared_ptr<EvaluationsType> getEvaluations();

        void setLeaderboard(std::unique_ptr<Leaderboard> &&leaderboard);

        std::unique_ptr<Leaderboard> &getLeaderboard();

        int getLevelCount() const;

        std::shared_ptr<int> getCurrentLevel();

    private:
        class TextManager {
        public:
            TextType requestText(const std::string &key, const std::string &default_text);

            TextType getText(const std::string &key);

        private:
            std::unordered_map<std::string, TextType> texts;
        };

    private:
        std::optional<std::string> error_message;
        std::string user_func_name;
        std::string pre_included_headers;

        std::unique_ptr<TextManager> textManager;
        std::unique_ptr<LevelEvaluator> levelEvaluator;

        std::shared_ptr<int> player_score;
        std::string player_name;

        std::unique_ptr<Leaderboard> leaderboard;
    };

} // namespace gj