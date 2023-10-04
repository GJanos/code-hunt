#include "Level.h"

using namespace gj;

Level::Level(std::string testName, std::initializer_list<std::pair<int, int>> cases) :
        name(std::move(testName)), cases(cases) {}

