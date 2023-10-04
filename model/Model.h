#pragma once

#include <array>
#include <memory>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <optional>
#include "Level.h"

namespace gj {
    using TextType = std::shared_ptr<std::array<char, 1024>>;

    class Model {
    public:
        Model(std::initializer_list<Level> init_levels);

        TextType requestText(const std::string &key, const std::string &default_text);

        TextType getText(const std::string &key);

        std::vector<Level>& getLevels();

        std::shared_ptr<int> getPlayerScore();

        void setPlayerScore(int score);

        std::string getPlayerName();

        void setPlayerName(std::string name);

        std::string getUserFuncName();

        std::string getPreIncludedHeaders();

        void setError(const std::optional<std::string>& error);

        std::optional<std::string> getError() const;

    private:
        class TextManager {
        public:
            TextType requestText(const std::string &key, const std::string &default_text);

            TextType getText(const std::string &key);

        private:
            std::unordered_map<std::string, TextType> texts;
        };

        struct Evaluation {
            const bool passed;
            const int user_input;
            const int expected_output;
            const int actual_output;

            Evaluation(bool passed, int user_input, int expected_output, int actual_output);
        };

        constexpr static const auto cmp = [](const Evaluation& a, const Evaluation& b) -> bool {
            if(a.passed == b.passed) {
                return a.user_input < b.user_input;
            }
            return a.passed < b.passed;
        };

    private:
        std::optional<std::string> error_message;
        std::string user_func_name;
        std::string pre_included_headers;
        std::unique_ptr<TextManager> textManager;
        std::shared_ptr<int> player_score;
        std::string player_name;
        int num_of_tries;
        std::vector<Level> levels;
        int current_level;

        std::set<Evaluation, decltype(cmp)> evaluations;


        //leaderboards later

    };

} // namespace gj


