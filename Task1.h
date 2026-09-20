#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс для реализации первого задания
     */
    class Task1 : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task1
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Указатель на генератор
         */
        Task1(size_t r, size_t c, std::shared_ptr<Generator> gen);

        /**
         * @brief Выполняет замену максимального элемента каждого столбца нулем
         */
        void solve() override;
    };
}