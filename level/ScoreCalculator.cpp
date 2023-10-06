#include <iostream>
#include "ScoreCalculator.h"

using namespace gj;

void ScoreCalculator::Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

DurationType ScoreCalculator::Timer::stop() {
    auto stop_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<DurationType>(stop_time - start_time);
}

ScoreCalculator::ScoreCalculator() : num_of_tries(0), max_score(100), min_score(10) {
    timer.start();
}

int ScoreCalculator::calculate_score() {
    auto duration = timer.stop();
    int units = duration.count() / 10;
    int score = max_score - ((units * 5) + ((num_of_tries - 1) * 10));
    std::cout << num_of_tries << "\n";
    num_of_tries = 0;
    timer.start();
    return score < min_score ? min_score : score;
}


