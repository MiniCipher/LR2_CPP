#include "DataGenerator.h"
#include <algorithm>

DataGenerator::DataGenerator() : gen(rd()) {
}

std::vector<double> DataGenerator::generate_doubles(size_t size, double min, double max) {
    std::vector<double> data(size);
    std::uniform_real_distribution<double> dist(min, max);

    std::generate(data.begin(), data.end(), [&]() {
        return dist(gen);
        });

    return data;
}

std::vector<int> DataGenerator::generate_integers(size_t size, int min, int max) {
    std::vector<int> data(size);
    std::uniform_int_distribution<int> dist(min, max);

    std::generate(data.begin(), data.end(), [&]() {
        return dist(gen);
        });

    return data;
}

std::vector<double> DataGenerator::generate_sequential_doubles(size_t size, double start, double step) {
    std::vector<double> data(size);
    double value = start;

    std::generate(data.begin(), data.end(), [&]() {
        double current = value;
        value += step;
        return current;
        });

    return data;
}

std::mt19937& DataGenerator::get_generator() {
    return gen;
}