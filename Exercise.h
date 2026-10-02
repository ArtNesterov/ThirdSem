#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <memory>

namespace miit::algebra
{
    /**
     * @brief Базовый абстрактный класс для заданий
     * Агрегирует класс Matrix и Generator для инициализации и обработки данных
     */
    class Exercise
    {
    protected:
        Matrix<int> matrix;
        std::shared_ptr<Generator> generator;
    public:
        /**
         * @brief Конструктор класса Exercise. Заполняет матрицу с помощью переданного генератора
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Указатель на объект генератора (Random или IStream)
         */
        Exercise(size_t r, size_t c, std::shared_ptr<Generator> gen) : matrix(r, c), generator(gen)
        {
            for (size_t i = 0; i < r; ++i) {
                for (size_t j = 0; j < c; ++j) {
                    matrix(i, j) = generator->generate();
                }
            }
        }

        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Exercise() = default;

        /**
         * @brief Виртуальный метод выполнения задания
         */
        virtual void solve() = 0;

        /**
         * @brief Получить текущее состояние матрицы
         * @return Копия объекта матрицы
         */
        Matrix<int> getMatrix() const { return matrix; }
    };
}