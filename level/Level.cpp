#include "Level.h"

using namespace gj;

Level::Level(std::string testName, std::initializer_list<std::pair<int, int>> cases) :
        name(std::move(testName)), cases(cases) {}

Evaluation::Evaluation(bool passed, int user_input, int expected_output, int actual_output)
        : passed(passed), user_input(user_input), expected_output(expected_output),
          actual_output(actual_output) {}

