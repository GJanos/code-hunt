#pragma once

#include <string>
#include <vector>
#include <set>
#include <memory>
#include "Level.h"
#include "ScoreCalculator.h"

namespace gj {

    /// todo talan egy kozos headerbe a typeokat kiszervezni
    typedef int (*UserFuncType)(int);

    constexpr inline const auto cmp_eval = [](const Evaluation& a, const Evaluation& b) -> bool {
        if(a.passed == b.passed) {
            return a.user_input < b.user_input;
        }
        return a.passed > b.passed;
    };

    using EvaluationsType = std::set<Evaluation, decltype(cmp_eval)>;

    class LevelEvaluator {
    public:

        LevelEvaluator(std::initializer_list<Level> init_levels);

        /// return optional score
        std::optional<std::pair<int, bool>> evaluateLevel();

        void setUserFunc(UserFuncType user_func);

        std::shared_ptr<EvaluationsType> getEvaluations();

        int getLevelCount() const;

        std::shared_ptr<int> getCurrentLevel();


    private:
        std::vector<Level> levels;
        std::shared_ptr<int> current_level;
        std::shared_ptr<EvaluationsType> evaluations;
        UserFuncType user_func;
        ScoreCalculator calc;

        bool isCurrentLevelPassed() const;

        void evaluateCurrentLevel();
    };
}