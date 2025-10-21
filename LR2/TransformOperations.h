#pragma once

#include <cmath>
#include <algorithm>

class TransformOperations {
public:
    static double fast_operation(double x);

    static double slow_operation(double x);

    static double very_slow_operation(double x);

    static int fast_int_operation(int x);

    static int slow_int_operation(int x);

    static double test_operation(double x);

    static double conditional_operation(double x);
};
