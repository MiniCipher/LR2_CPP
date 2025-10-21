#pragma once

#include "DataGenerator.h"
#include "TransformBenchmark.h"
#include "TransformOperations.h"
#include <vector>
#include <iostream>

class ExperimentRunner {
private:
    DataGenerator generator;
    TransformBenchmark benchmark;

    void print_k_results_table(const std::vector<std::pair<size_t, double>>& results,
        double sequential_time);

    void analyze_k_performance(const std::vector<std::pair<size_t, double>>& results,
        double sequential_time);

    size_t calculate_max_k(size_t data_size);

public:
    void run_k_experiment(const std::string& experiment_name);

    void run_comprehensive_test(const std::string& test_name);

    void run_optimization_comparison();

    void run_all_experiments();
};