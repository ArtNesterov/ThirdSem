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
        Exercise(const size_t r, const size_t c, const std::shared_ptr<Generator> gen)
            : matrix(r, c), generator(gen)
        {
            matrix.fill(generator);
        }

        /**
         * @brief Конструктор со ссылкой на генератор (поддерживает оба варианта передачи)
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Ссылка на генератор
         */
        Exercise(const size_t r, const size_t c, Generator& gen)
            : matrix(r, c), generator(nullptr)
        {
            matrix.fill(gen);
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