#include "ExperimentRunner.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <fstream>

void ExperimentRunner::print_k_results_table(const std::vector<std::pair<size_t, double>>& results,
    double sequential_time) {
    std::cout << std::setw(6) << "K" << std::setw(15) << "Time (ms)" << std::setw(15) << "Speedup" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (const auto& [k, time] : results) {
        double speedup = sequential_time / time;
        std::cout << std::setw(6) << k << std::setw(15) << std::fixed << std::setprecision(3)
            << time << std::setw(15) << std::setprecision(2) << speedup << "x" << std::endl;
    }
}

void ExperimentRunner::analyze_k_performance(const std::vector<std::pair<size_t, double>>& results,
    double sequential_time) {
    auto best_result = *std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    std::cout << std::string(40, '=') << std::endl;
    std::cout << "BEST RESULT:" << std::endl;
    std::cout << "K = " << best_result.first << ", time = " << best_result.second << " ms" << std::endl;
    std::cout << "Speedup: " << std::fixed << std::setprecision(2)
        << sequential_time / best_result.second << "x" << std::endl;
    std::cout << "K/threads ratio: "
        << std::fixed << std::setprecision(2)
        << static_cast<double>(best_result.first) / std::thread::hardware_concurrency()
        << std::endl;
}

size_t ExperimentRunner::calculate_max_k(size_t data_size) {
    unsigned int hardware_threads = std::thread::hardware_concurrency();
    size_t suggested_k = static_cast<size_t>(hardware_threads) * 4;
    size_t max_k = (suggested_k < data_size) ? suggested_k : data_size;
    return std::max(max_k, size_t(1));
}

void ExperimentRunner::run_data_size_comparison() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DATA SIZE COMPARISON" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::vector<size_t> sizes = { 1000, 10000, 100000, 500000, 1000000 };

    for (size_t size : sizes) {
        std::cout << "\n*** Data Size: " << size << " ***" << std::endl;

        auto data = generator.generate_doubles(size);
        std::vector<double> output;

        benchmark.test_standard_transform(data, output,
            TransformOperations::fast_operation, "Fast Operation");

        benchmark.test_standard_transform(data, output,
            TransformOperations::slow_operation, "Slow Operation");
    }
}

void ExperimentRunner::run_k_experiment(const std::string& experiment_name) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "K EXPERIMENT: " << experiment_name << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::vector<size_t> sizes = { 100000, 1000000 };

    for (size_t size : sizes) {
        std::cout << "\n--- Data Size: " << size << " ---" << std::endl;
        std::cout << "Hardware threads: " << std::thread::hardware_concurrency() << std::endl;

        auto data = generator.generate_doubles(size);
        std::vector<double> output;

        size_t max_k = calculate_max_k(size);
        std::cout << "Testing K from 1 to " << max_k << std::endl;

        auto slow_op = [](double x) {
            return std::sin(x) * std::cos(x) + std::log(std::abs(x) + 1.0);
            };

        auto results = benchmark.measure_k_performance(data, output, slow_op, max_k);
        double sequential_time = results[0].second;

        print_k_results_table(results, sequential_time);
        analyze_k_performance(results, sequential_time);
    }
}

void ExperimentRunner::run_comprehensive_test(const std::string& test_name) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "COMPREHENSIVE TEST: " << test_name << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    size_t size = 500000;
    std::cout << "\n*** Testing data size: " << size << " ***" << std::endl;

    auto double_data = generator.generate_doubles(size);
    std::vector<double> double_output;

    benchmark.test_standard_transform(double_data, double_output,
        TransformOperations::fast_operation, "Double Fast Operation");

    benchmark.test_standard_transform(double_data, double_output,
        TransformOperations::slow_operation, "Double Slow Operation");

    benchmark.verify_correctness(double_data, TransformOperations::fast_operation);
}

void ExperimentRunner::run_optimization_comparison() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "OPTIMIZATION LEVEL COMPARISON" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << "Note: This test should be compiled with different optimization flags:" << std::endl;
    std::cout << "- O0 (no optimization)" << std::endl;
    std::cout << "- O2 (standard optimization)" << std::endl;
    std::cout << "- O3 (maximum optimization)" << std::endl;

    std::cout << "\nDemonstrating optimization impact on different data sizes:" << std::endl;

    auto small_data = generator.generate_doubles(1000);
    std::vector<double> small_output;
    std::cout << "\n--- Small Data (1000 elements) ---" << std::endl;
    benchmark.test_standard_transform(small_data, small_output,
        TransformOperations::fast_operation, "Fast Operation");

    auto large_data = generator.generate_doubles(1000000);
    std::vector<double> large_output;
    std::cout << "\n--- Large Data (1,000,000 elements) ---" << std::endl;
    benchmark.test_standard_transform(large_data, large_output,
        TransformOperations::slow_operation, "Slow Operation");
}

void ExperimentRunner::run_all_experiments() {
    std::cout << "TRANSFORM ALGORITHM PERFORMANCE ANALYSIS" << std::endl;
    std::cout << "Compiler: MSVC | Standard: C++20" << std::endl;
    std::cout << "Hardware threads: " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "Build: RELEASE" << std::endl;

    run_data_size_comparison();
    run_comprehensive_test("Standard Policies Comparison");
    run_k_experiment("Parallel Thread Count Optimization");
    run_optimization_comparison();

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "ALL EXPERIMENTS COMPLETED SUCCESSFULLY" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

}