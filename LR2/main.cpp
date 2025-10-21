#include "ExperimentRunner.h"
#include <iostream>

int main() {
    try {
        ExperimentRunner runner;

        std::cout << "=== TRANSFORM ALGORITHM PERFORMANCE ANALYSIS ===" << std::endl;
        std::cout << "C++ Standard: C++20" << std::endl;
        std::cout << "Build: RELEASE" << std::endl;

        // Запуск всіх експериментів
        runner.run_all_experiments();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}