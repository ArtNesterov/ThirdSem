#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс матрицы
     * @param T Тип элементов матрицы
     */
    template <typename T>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> data;
        size_t rows;
        size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию
         */
        Matrix() : rows(0), cols(0) {}

        /**
         * @brief Конструктор с параметрами
         * @param r Количество строк
         * @param c Количество столбцов
         */
        Matrix(const size_t r,const size_t c) : rows(r), cols(c), data(r, std::vector<T>(c)) {}

        /**
         * @brief Деструктор по умолчанию
         */
        ~Matrix() = default;

        /**
         * @brief Конструктор копирования
         */
        Matrix(const Matrix&) = default;

        /**
         * @brief Конструктор перемещения
         */
        Matrix(Matrix&&) = default;

        /**
         * @brief Оператор присваивания копированием
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(const Matrix&) = default;

        /**
         * @brief Оператор присваивания перемещением
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(Matrix&&) = default;

        /**
         * @brief Оператор доступа к элементу матрицы по индексу 
         * @param r Индекс строки
         * @param c Индекс столбца
         * @return Ссылка на элемент матрицы
         */
        T& operator[](size_t r, size_t c) { return data[r][c]; 
        {
            if (r >= rows || c >= cols) {
                throw std::out_of_range("Индекс выходит за границы матрицы!");
            }
            return data[r][c];
        }

        /**
         * @brief Оператор доступа к элементу матрицы по индексу 
         * @param r Индекс строки
         * @param c Индекс столбца
         * @return Константная ссылка на элемент матрицы
         */
        const T& operator[](size_t r, size_t c) const {
            if (r >= rows || c >= cols) {
                throw std::out_of_range("Индекс выходит за границы матрицы!");
            }
            return data[r][c];
        }

        /**
         * @brief Получить количество строк матрицы
         * @return Количество строк
         */
        size_t getRows() const { return rows; }

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        size_t getCols() const { return cols; }


        /**
         * @brief Метод заполнения матрицы с использованием переданного генератора
         */
        void fill(const std::shared_ptr<Generator>& generator)
        {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = static_cast<T>(generator->generate());
                }
            }
        }


        /**
         * @brief Метод вывода содержимого матрицы в строку
         * @return Строковое представление матрицы
         */
        std::string toString() const
        {
            std::ostringstream oss;
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    oss << data[i][j] << "\t";
                }
                oss << "\n";
            }
            return oss.str();
        }

        /**
         * @brief Вставка новой строки в матрицу по указанному индексу
         * @param index Индекс, по которому будет вставлена новая строка
         * @param row Вектор элементов новой строки
         */
        void insertRow(const size_t index, const std::vector<T>& row)
        {
            data.insert(data.begin() + index, row);
            rows++;
        }

        /**
         * @brief Получение копии указанной строки матрицы
         * @param index Индекс строки
         * @return Вектор элементов запрошенной строки
         */
        std::vector<T> getRow(const size_t index) const
        {
            return data[index];
        }

        /**
         * @brief Переопределение оператора сдвига влево для вывода матрицы в поток
         * @param os Поток вывода
         * @param matrix Матрица для вывода
         * @return Ссылка на поток вывода
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
        {
            os << matrix.toString();
            return os;
        }
    };
}
