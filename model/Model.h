#pragma once

#include <array>
#include <memory>
#include <cstring>
#include <unordered_map>

namespace gj {
    using TextType = std::shared_ptr<std::array<char, 1024>>;

    class Model {
    public:
        Model();

        TextType requestText(const std::string &key, const std::string &default_text);

        TextType getText(const std::string &key);

        std::shared_ptr<int> getPlayerScore();

        void setPlayerScore(int score);

        std::string getPlayerName();

        void setPlayerName(std::string name);

    private:
        class TextManager {
        public:
            TextType requestText(const std::string &key, const std::string &default_text);

            TextType getText(const std::string &key);

        private:
            std::unordered_map<std::string, TextType> texts;
        };

    private:
        std::unique_ptr<TextManager> textManager;
        std::shared_ptr<int> player_score;
        std::string player_name;
    };

} // namespace gj


