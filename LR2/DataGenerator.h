#pragma once

#include <vector>
#include <random>

/**
 * @class DataGenerator
 * @brief Клас для генерації тестових даних різних типів та розмірів
 *
 * Використовує Mersenne Twister (mt19937) для якісної генерації
 * випадкових чисел з можливістю повторюваності.
 */
class DataGenerator {
private:
    std::random_device rd;  ///< Апаратний генератор для seed
    std::mt19937 gen;       ///< Основний генератор Mersenne Twister

public:
    /**
     * @brief Конструктор ініціалізує генератор випадкових чисел
     */
    DataGenerator();

    /**
     * @brief Генерує вектор випадкових чисел типу double
     * @param size Розмір вектора, що генерується
     * @param min Мінімальне значення (за замовчуванням 0.0)
     * @param max Максимальне значення (за замовчуванням 1000.0)
     * @return Вектор випадкових чисел у вказаному діапазоні
     */
    std::vector<double> generate_doubles(size_t size, double min = 0.0, double max = 1000.0);

    /**
     * @brief Генерує вектор випадкових чисел типу int
     * @param size Розмір вектора, що генерується
     * @param min Мінімальне значення (за замовчуванням 0)
     * @param max Максимальне значення (за замовчуванням 1000)
     * @return Вектор випадкових цілих чисел у вказаному діапазоні
     */
    std::vector<int> generate_integers(size_t size, int min = 0, int max = 1000);

    /**
     * @brief Генерує послідовність чисел для тестування коректності
     * @param size Розмір вектора
     * @param start Початкове значення (за замовчуванням 0.0)
     * @param step Крок послідовності (за замовчуванням 1.0)
     * @return Вектор послідовних чисел
     */
    std::vector<double> generate_sequential_doubles(size_t size, double start = 0.0, double step = 1.0);

    /**
     * @brief Отримує посилання на внутрішній генератор
     * @return Посилання на генератор mt19937
     *
     * Дозволяє використовувати той самий генератор для спеціалізованих потреб
     */
    std::mt19937& get_generator();
};

