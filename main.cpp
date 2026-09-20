#include <iostream>
#include <memory>
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

/**
 * @brief точка входа в программу
 * @return 0, если программа завершена корректно
 */
int main()
{
    size_t rows, cols;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    std::cout << "Выберите способ заполнения:\n1 - Случайными числами\n2 - Вручную\n";
    int choice;
    std::cin >> choice;

    std::shared_ptr<Generator> generator;

    if (choice == 1) {
        int min, max;
        std::cout << "Введите начало диапазона: ";
        std::cin >> min;
        std::cout << "Введите конец диапазона: ";
        std::cin >> max;
        generator = std::make_shared<RandomGenerator>(min, max);
    }
    else {
        std::cout << "Введите элементы матрицы:\n";
        generator = std::make_shared<IStreamGenerator>(std::cin);
    }

    std::cout << "\n ЗАДАЧА 1 \n";
    Task1 task1(rows, cols, generator);
    std::cout << "Исходная матрица:\n" << task1.getMatrix();
    task1.solve();
    std::cout << "Результат задачи 1 (Заменить максимальный элемент столбца нулем):\n" << task1.getMatrix();



    std::cout << "\n ЗАДАЧА 2 \n";
    if (choice == 2) {
        std::cout << "Введите элементы матрицы еще раз для задачи 2:\n";
    }

    Task2 task2(rows, cols, generator);
    std::cout << "Исходная матрица:\n" << task2.getMatrix();
    task2.solve();
    std::cout << "Результат задачи 2 (Вставить первую строку после строки с max модулем):\n" << task2.getMatrix();

    return 0;
}