#include "TransformOperations.h"

double TransformOperations::fast_operation(double x) {
    return x * 2.5 + 1.0;
}

double TransformOperations::slow_operation(double x) {
    double result = std::sin(x) * std::cos(x);
    result += std::log(std::abs(x) + 1.0);
    result += std::sqrt(std::abs(x));
    result += std::atan(x);
    result += std::exp(std::sin(x) * 0.1);
    return result;
}

double TransformOperations::very_slow_operation(double x) {
    double result = 0.0;
    for (int i = 0; i < 500; ++i) {
        result += std::sin(x + i) * std::cos(x - i);
        result = std::sqrt(std::abs(result) + 1.0);
    }
    return result;
}

int TransformOperations::fast_int_operation(int x) {
    return x * 3 + 7;
}

int TransformOperations::slow_int_operation(int x) {
    int result = 0;
    for (int i = 0; i < 1000; ++i) {
        result += (x * i) % 13;
        result = std::abs(result) % 1000;
    }
    return result;
}

double TransformOperations::test_operation(double x) {
    return x * 2.0;
}

double TransformOperations::conditional_operation(double x) {
    if (x > 500.0) {
        return std::sin(x) * std::cos(x);
    }
    else {
        return x * 1.5;
    }
}