#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс для реализации второй части задания 
     */
    class Task2 : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task2
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Умный указатель на генератор
         */
        Task2(size_t r, size_t c, std::shared_ptr<Generator> gen);

        /**
         * @brief Выполняет вставку первой строки после всех строк содержащих максимальный по модулю элемент
         */
        void solve() override;
    };
}