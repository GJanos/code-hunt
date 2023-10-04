#pragma once

#include <string>
#include <vector>

namespace gj {

    struct Level {
        std::string name;
        std::vector<std::pair<int, int>> cases;

        Level(std::string testName, std::initializer_list<std::pair<int, int>> cases);
    };


} // namespace gj




