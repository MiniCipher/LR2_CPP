#pragma once

#include <vector>
#include <random>

/*Клас для генерації тестових даних різних типів та розмірів*/
class DataGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    DataGenerator();

    std::vector<double> generate_doubles(size_t size, double min = 0.0, double max = 1000.0);

    std::vector<int> generate_integers(size_t size, int min = 0, int max = 1000);

    std::vector<double> generate_sequential_doubles(size_t size, double start = 0.0, double step = 1.0);

    std::mt19937& get_generator();
};

