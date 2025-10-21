#pragma once

#include <chrono>

/*Клас для точного вимірювання часу виконання алгоритмів*/

class BenchmarkTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    bool is_running = false;

public:

    void start();

    double stop();

    bool running() const;
};

