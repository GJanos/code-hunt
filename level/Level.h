#pragma once

#include <string>
#include <vector>

namespace gj {

    struct Level {
        std::string name;
        std::vector<std::pair<int, int>> cases;

        Level(std::string testName, std::initializer_list<std::pair<int, int>> cases);
    };

    struct Evaluation {
        const bool passed;
        const int user_input;
        const int expected_output;
        const int actual_output;

        Evaluation(bool passed, int user_input, int expected_output, int actual_output);
    };

} // namespace gj




