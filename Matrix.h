#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <stdexcept>
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
        Matrix(const size_t r, const size_t c)
            : rows(r), cols(c), data(r, std::vector<T>(c)) {
        }

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
        Matrix(Matrix&&) noexcept = default;

        /**
         * @brief Оператор присваивания копированием
         */
        Matrix& operator=(const Matrix&) = default;

        /**
         * @brief Оператор присваивания перемещением
         */
        Matrix& operator=(Matrix&&) noexcept = default;

        std::vector<T>& operator[](const size_t r)
        {
            if (r >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }


        /**
         * @brief Оператор индексации строки (константный)
         * @param r Индекс строки
         * @return Константная ссылка на вектор строки
         */
        const std::vector<T>& operator[](const size_t r) const
        {
            if (r >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }

        /**
         * @brief Дополнительный оператор доступа по координатам (r, c)
         */
        T& operator()(const size_t r, const size_t c)
        {
            if (r >= rows || c >= cols) {
                throw std::out_of_range("Индекс выходит за границы матрицы!");
            }
            return data[r][c];
        }
        const T& operator()(const size_t r, const size_t c) const
        {
            if (r >= rows || c >= cols) {
                throw std::out_of_range("Индекс выходит за границы матрицы!");
            }
            return data[r][c];
        }

        /**
         * @brief Получить количество строк матрицы
         */
        size_t getRows() const { return rows; }

        /**
         * @brief Получить количество столбцов матрицы
         */
        size_t getCols() const { return cols; }

        /**
         * @brief Заполнение матрицы с использованием ссылки на генератор
         */
        void fill(Generator& generator)
        {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Заполнение матрицы с использованием указателя на генератор
         */
        void fill(const std::shared_ptr<Generator>& generator)
        {
            if (generator) {
                this->fill(*generator);
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
            if (index > rows) {
                throw std::out_of_range("Индекс вставки выходит за границы матрицы");
            }
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
            if (index >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы");
            }
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

        /**
        * @brief Переопределение оператора сдвига вправо (ввод матрицы из потока)
        * @param in Поток ввода
        * @param matrix Матрица для ывода
        */
        friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
        {
            for (size_t i = 0; i < matrix.rows; ++i) {
                for (size_t j = 0; j < matrix.cols; ++j) {
                    is >> matrix.data[i][j];
                }
            }
            return is;
        }

    };
}