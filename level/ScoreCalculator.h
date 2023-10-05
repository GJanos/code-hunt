#pragma once

#include <chrono>

namespace gj {
    using TimeType = std::chrono::high_resolution_clock::time_point;
    using DurationType = std::chrono::duration<double>;

    struct ScoreCalculator {

        struct Timer {
            TimeType start_time;
            void start();
            DurationType stop();
        };

        Timer timer;
        int num_of_tries;
        int max_score;
        int min_score;

        ScoreCalculator();

        int calculate_score();
    };
}


