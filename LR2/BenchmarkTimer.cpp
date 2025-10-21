#include "BenchmarkTimer.h"

void BenchmarkTimer::start() {
    start_time = std::chrono::high_resolution_clock::now();
    is_running = true;
}

double BenchmarkTimer::stop() {
    if (!is_running) {
        return 0.0;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end_time - start_time);
    is_running = false;
    return duration.count();
}

bool BenchmarkTimer::running() const {
    return is_running;
}