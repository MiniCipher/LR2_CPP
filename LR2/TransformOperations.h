#pragma once

#include <cmath>
#include <algorithm>

/**
 * @class TransformOperations
 * @brief Бібліотека тестових операцій для алгоритму transform
 *
 * Містить набір статичних методів, що реалізують різні за складністю
 * операції для тестування продуктивності алгоритмів.
 */
class TransformOperations {
public:
    /**
     * @brief Швидка операція для double - просте арифметичне перетворення
     * @param x Вхідне значення
     * @return Результат обчислення x * 2.5 + 1.0
     */
    static double fast_operation(double x);

    /**
     * @brief Повільна операція для double - комплексні математичні обчислення
     * @param x Вхідне значення
     * @return Результат комбінації тригонометричних, логарифмічних та інших функцій
     */
    static double slow_operation(double x);

    /**
     * @brief Дуже повільна операція - інтенсивні обчислення з багатьма ітераціями
     * @param x Вхідне значення
     * @return Результат багаторазових математичних перетворень
     */
    static double very_slow_operation(double x);

    /**
     * @brief Швидка операція для int - просте лінійне перетворення
     * @param x Вхідне ціле значення
     * @return Результат обчислення x * 3 + 7
     */
    static int fast_int_operation(int x);

    /**
     * @brief Повільна операція для int - імітація складних обчислень
     * @param x Вхідне ціле значення
     * @return Результат багатоітераційних обчислень з модульною арифметикою
     */
    static int slow_int_operation(int x);

    /**
     * @brief Проста операція для тестування коректності
     * @param x Вхідне значення
     * @return Подвоєне вхідне значення
     */
    static double test_operation(double x);

    /**
     * @brief Операція з умовою для демонстрації різних шаблонів виконання
     * @param x Вхідне значення
     * @return Різні результати в залежності від величини x
     */
    static double conditional_operation(double x);
};
