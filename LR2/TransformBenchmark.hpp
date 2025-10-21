#pragma once

#include "TransformBenchmark.h"
#include <algorithm>
#include <execution>
#include <future>
#include <thread>
#include <iostream>
#include <iomanip>

inline void TransformBenchmark::print_result_line(const std::string& name, double time, double speedup) {
    std::cout << std::setw(20) << std::left << name
        << std::setw(12) << std::right << std::fixed << std::setprecision(3) << time << " ms"
        << std::setw(10) << std::right << std::setprecision(2) << speedup << "x" << std::endl;
}

template<typename T, typename Func>
void TransformBenchmark::test_standard_transform(const std::vector<T>& input, std::vector<T>& output,
    Func operation, const std::string& test_name) {
    std::cout << "\n=== " << test_name << " (size: " << input.size() << ") ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    output.resize(input.size());
    double seq_time, par_time, par_unseq_time;

    // Sequenced policy
    timer.start();
    std::transform(std::execution::seq, input.begin(), input.end(), output.begin(), operation);
    seq_time = timer.stop();

    // Parallel policy
    timer.start();
    std::transform(std::execution::par, input.begin(), input.end(), output.begin(), operation);
    par_time = timer.stop();

    // Parallel unsequenced policy
    par_unseq_time = -1.0;
    try {
        timer.start();
        std::transform(std::execution::par_unseq, input.begin(), input.end(), output.begin(), operation);
        par_unseq_time = timer.stop();
    }
    catch (const std::exception& e) {
        std::cout << "WARNING: par_unseq not supported: " << e.what() << std::endl;
    }

    print_result_line("Sequenced", seq_time, 1.0);
    print_result_line("Parallel", par_time, seq_time / par_time);

    if (par_unseq_time >= 0) {
        print_result_line("Parallel Unseq", par_unseq_time, seq_time / par_unseq_time);
    }

    double best_time = std::min(par_time, par_unseq_time > 0 ? par_unseq_time : par_time);
    std::cout << "Best speedup: " << std::fixed << std::setprecision(2)
        << seq_time / best_time << "x" << std::endl;
}

template<typename T, typename Func>
void TransformBenchmark::custom_parallel_transform(const std::vector<T>& input, std::vector<T>& output,
    Func operation, size_t K) {
    if (input.empty()) {
        output.clear();
        return;
    }

    output.resize(input.size());
    std::vector<std::future<void>> futures;
    size_t chunk_size = input.size() / K;

    for (size_t i = 0; i < K; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == K - 1) ? input.size() : (i + 1) * chunk_size;

        futures.push_back(std::async(std::launch::async,
            [&input, &output, operation, start, end]() {
                std::transform(input.begin() + start, input.begin() + end,
                    output.begin() + start, operation);
            }));
    }

    for (auto& future : futures) {
        future.get();
    }
}

template<typename T, typename Func>
std::vector<std::pair<size_t, double>> TransformBenchmark::measure_k_performance(
    const std::vector<T>& input, std::vector<T>& output, Func operation, size_t max_k) {

    std::vector<std::pair<size_t, double>> results;

    for (size_t k = 1; k <= max_k; ++k) {
        timer.start();
        custom_parallel_transform(input, output, operation, k);
        double time = timer.stop();
        results.emplace_back(k, time);
    }

    return results;
}

template<typename T, typename Func>
bool TransformBenchmark::verify_correctness(const std::vector<T>& input, Func operation) {
    std::vector<T> seq_output(input.size());
    std::vector<T> par_output(input.size());
    std::vector<T> custom_output(input.size());

    // Sequential version
    std::transform(std::execution::seq, input.begin(), input.end(), seq_output.begin(), operation);

    // Parallel version
    std::transform(std::execution::par, input.begin(), input.end(), par_output.begin(), operation);

    // Custom parallel version
    custom_parallel_transform(input, custom_output, operation, std::thread::hardware_concurrency());

    // Compare results
    bool par_correct = true;
    bool custom_correct = true;

    for (size_t i = 0; i < input.size(); ++i) {
        if (seq_output[i] != par_output[i]) {
            par_correct = false;
            break;
        }
    }

    for (size_t i = 0; i < input.size(); ++i) {
        if (seq_output[i] != custom_output[i]) {
            custom_correct = false;
            break;
        }
    }

    std::cout << "\n=== CORRECTNESS VERIFICATION (size: " << input.size() << ") ===" << std::endl;
    std::cout << "Standard parallel: " << (par_correct ? "CORRECT" : "INCORRECT") << std::endl;
    std::cout << "Custom parallel: " << (custom_correct ? "CORRECT" : "INCORRECT") << std::endl;

    return par_correct && custom_correct;
}