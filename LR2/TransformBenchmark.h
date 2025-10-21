#pragma once

#include "BenchmarkTimer.h"
#include "TransformOperations.h"
#include <vector>
#include <future>
#include <thread>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <execution>

class TransformBenchmark {
private:
    BenchmarkTimer timer;
    void print_result_line(const std::string& name, double time, double speedup = 1.0);

public:
    template<typename T, typename Func>
    void test_standard_transform(const std::vector<T>& input, std::vector<T>& output,
        Func operation, const std::string& test_name);

    template<typename T, typename Func>
    void custom_parallel_transform(const std::vector<T>& input, std::vector<T>& output,
        Func operation, size_t K);

    template<typename T, typename Func>
    std::vector<std::pair<size_t, double>> measure_k_performance(
        const std::vector<T>& input, std::vector<T>& output, Func operation, size_t max_k);

    template<typename T, typename Func>
    bool verify_correctness(const std::vector<T>& input, Func operation);
};

#include "TransformBenchmark.hpp"