#include "LevelEvaluator.h"
#include "Exception.h"

#include <algorithm>

using namespace gj;

LevelEvaluator::LevelEvaluator(std::initializer_list<Level> init_levels) :
        levels(init_levels), current_level(std::make_shared<int>(0)),
        evaluations(std::make_shared<EvaluationsType>()),
        user_func(nullptr),
        calc() {
}

std::optional<std::pair<int, bool>> LevelEvaluator::evaluateLevel() {
    if (*current_level >= levels.size()) {
        evaluations->clear();
        return std::make_optional(std::make_pair(-1, true));
    }

    if (user_func == nullptr) {
        throw UserFuncNotFoundException("User function is not set!");
    }

    evaluateCurrentLevel();

    bool level_passed = isCurrentLevelPassed();
    calc.num_of_tries++;

    if (level_passed) {
        *current_level = *current_level + 1;
        evaluations->clear();
        bool all_levels_completed = (*current_level == levels.size());
        return std::make_optional(std::make_pair(calc.calculate_score(), all_levels_completed));
    }

    return std::make_optional(std::make_pair(0, false));
}

void LevelEvaluator::evaluateCurrentLevel() {
    evaluations->clear();
    for (const auto &[input, expected]: levels[*current_level].cases) {
        int actual = user_func(input);
        bool passed = (actual == expected);
        evaluations->insert(Evaluation(passed, input, expected, actual));
    }
}

bool LevelEvaluator::isCurrentLevelPassed() const {
    return std::all_of(evaluations->begin(), evaluations->end(),
                       [](const Evaluation &e) { return e.passed; });
}


void LevelEvaluator::setUserFunc(UserFuncType user_func) {
    this->user_func = user_func;
}

std::shared_ptr<EvaluationsType> LevelEvaluator::getEvaluations() {
    return evaluations;
}

int LevelEvaluator::getLevelCount() const {
    return levels.size();
}

std::shared_ptr<int> LevelEvaluator::getCurrentLevel() {
    return current_level;
}



