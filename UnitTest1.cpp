#include "CppUnitTest.h"
#include <vector>
#include <memory>
#include <sstream>
#include <stdexcept>
#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "RandomGenerator.h"  
#include "IStreamGenerator.h"     
#include "ConstGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;
namespace Tests
{
    TEST_CLASS(MatrixTests)
    {
    public:
        /**
         * @brief Проверка конструктора по умолчанию
         */
        TEST_METHOD(DefaultConstructor_Test)
        {
            Matrix<int> m;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
            Assert::AreEqual(static_cast<size_t>(0), m.getCols());
        }
        /**
         * @brief Проверка конструктора с параметрами
         */
        TEST_METHOD(ParameterizedConstructor_Test)
        {
            Matrix<int> m(2, 3);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(3), m.getCols());
        }
        /**
         * @brief Проверка конструктора копирования
         */
        TEST_METHOD(CopyConstructor_Test)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 10;
            original[1][1] = 20;
            Matrix<int> copy(original);
            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original.getCols(), copy.getCols());
            Assert::AreEqual(10, copy[0][0]);
            Assert::AreEqual(20, copy[1][1]);
        }

        /**
         * @brief Проверка конструктора перемещения
         */
        TEST_METHOD(MoveConstructor_Test)
        {
            Matrix<int> original(2, 2);
            original[0][1] = 42;
            Matrix<int> moved(std::move(original));
            Assert::AreEqual(static_cast<size_t>(2), moved.getRows());
            Assert::AreEqual(static_cast<size_t>(2), moved.getCols());
            Assert::AreEqual(42, moved[0][1]);
        }
        /**
         * @brief Проверка оператора присваивания копированием
         */
        TEST_METHOD(CopyAssignment_Test)
        {
            Matrix<int> m1(2, 2);
            m1[0][0] = 7;
            Matrix<int> m2;
            m2 = m1;
            Assert::AreEqual(static_cast<size_t>(2), m2.getRows());
            Assert::AreEqual(7, m2[0][0]);
            m2[0][0] = 100;
            Assert::AreEqual(7, m1[0][0]);
        }
        /**
         * @brief Проверка оператора присваивания перемещением
         */
        TEST_METHOD(MoveAssignment_Test)
        {
            Matrix<int> m1(2, 2);
            m1[1][0] = 15;
            Matrix<int> m2;
            m2 = std::move(m1);
            Assert::AreEqual(static_cast<size_t>(2), m2.getRows());
            Assert::AreEqual(15, m2[1][0]);
        }
        /**
         * @brief Проверка оператора индексации operator[][] (неконстантный и константный)
         */
        TEST_METHOD(SubscriptOperator_Test)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 1;
            m[0][1] = 2;
            m[1][0] = 3;
            m[1][1] = 4;
            Assert::AreEqual(1, m[0][0]);
            Assert::AreEqual(2, m[0][1]);
            Assert::AreEqual(3, m[1][0]);
            Assert::AreEqual(4, m[1][1]);
        }
        /**
         * @brief Проверка исключения при выходе за границы в operator[]
         */
        TEST_METHOD(SubscriptOperator_OutOfRange_Test)
        {
            Matrix<int> m(2, 2);
            Assert::ExpectException<std::out_of_range>([&]() {
                m[2][0] = 10; 
                });
        }
        /**
         * @brief Проверка оператора operator()(r, c)
         */
        TEST_METHOD(CallOperator_Test)
        {
            Matrix<int> m(2, 2);
            m(0, 1) = 55;
            Assert::AreEqual(55, m(0, 1));
            const Matrix<int>& cm = m;
            Assert::AreEqual(55, cm(0, 1));
            Assert::ExpectException<std::out_of_range>([&]() {
                m(5, 5);
                });
        }
        /**
         * @brief Проверка метода fill() с использованием генератора
         */
        TEST_METHOD(Fill_Test)
        {
            Matrix<int> m(2, 3);
            ConstGenerator gen(7);
            m.fill(gen);
            for (size_t i = 0; i < m.getRows(); ++i) {
                for (size_t j = 0; j < m.getCols(); ++j) {
                    Assert::AreEqual(7, m[i][j]);
                }
            }
        }
        /**
         * @brief Проверка преобразования в строку toString()
         */
        TEST_METHOD(ToString_Test)
        {
            Matrix<int> m(1, 2);
            m[0][0] = 5;
            m[0][1] = 9;
            std::string str = m.toString();
            // Ожидается строка вида "5\t9\t\n"
            Assert::IsTrue(str.find("5") != std::string::npos);
            Assert::IsTrue(str.find("9") != std::string::npos);
        }
        /**
         * @brief Проверка оператора сдвига влево operator<< (вывод в поток)
         */
        TEST_METHOD(StreamOutput_Test)
        {
            Matrix<int> m(1, 2);
            m[0][0] = 3;
            m[0][1] = 7;
            std::ostringstream oss;
            oss << m;
            Assert::AreEqual(m.toString(), oss.str());
        }
        /**
         * @brief Проверка оператора сдвига вправо operator>> (ввод из потока)
         */
        TEST_METHOD(StreamInput_Test)
        {
            Matrix<int> m(2, 2);
            std::istringstream iss("10 20 30 40");
            iss >> m;
            Assert::AreEqual(10, m[0][0]);
            Assert::AreEqual(20, m[0][1]);
            Assert::AreEqual(30, m[1][0]);
            Assert::AreEqual(40, m[1][1]);
        }
        /**
         * @brief Проверка получения копии строки getRow()
         */
        TEST_METHOD(GetRow_Test)
        {
            Matrix<int> m(2, 2);
            m[1][0] = 8;
            m[1][1] = 9;
            std::vector<int> row = m.getRow(1);
            Assert::AreEqual(static_cast<size_t>(2), row.size());
            Assert::AreEqual(8, row[0]);
            Assert::AreEqual(9, row[1]);
            Assert::ExpectException<std::out_of_range>([&]() {
                m.getRow(5);
                });
        }
        /**
         * @brief Проверка вставки новой строки
         */
        TEST_METHOD(InsertRow_Test)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 1; m[0][1] = 2;
            m[1][0] = 3; m[1][1] = 4;
            std::vector<int> newRow = { 5, 6 };
            m.insertRow(1, newRow);
            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(1, m[0][0]);
            Assert::AreEqual(5, m[1][0]);
            Assert::AreEqual(6, m[1][1]);
            Assert::AreEqual(3, m[2][0]);
            Assert::ExpectException<std::out_of_range>([&]() {
                m.insertRow(10, newRow);
                });
        }
    };
    TEST_CLASS(TasksTests)
    {
    public:
        /**
         * @brief Проверка замены максимума в каждом столбце нулем 
         */
        TEST_METHOD(Task1_Logic_Test)
        {
            std::istringstream input("1 4 3 2");
            auto gen = std::make_shared<IStreamGenerator>(input);
            Task1 task(2, 2, gen);
            task.solve();
            Matrix<int> res = task.getMatrix();
            Assert::AreEqual(1, res[0][0]);
            Assert::AreEqual(0, res[0][1]);
            Assert::AreEqual(0, res[1][0]);
            Assert::AreEqual(2, res[1][1]);
        }
        /**
         * @brief Проверка вставки первой строки после строки с max элементом по модулю
         */
        TEST_METHOD(Task2_Logic_Test)
        {
            std::istringstream input("1 2 -5 4");
            auto gen = std::make_shared<IStreamGenerator>(input);
            Task2 task(2, 2, gen);
            task.solve();
            Matrix<int> res = task.getMatrix();
            Assert::AreEqual(static_cast<size_t>(3), res.getRows());
            Assert::AreEqual(1, res[0][0]);
            Assert::AreEqual(2, res[0][1]);
            Assert::AreEqual(-5, res[1][0]);
            Assert::AreEqual(4, res[1][1]);
            Assert::AreEqual(1, res[2][0]);
            Assert::AreEqual(2, res[2][1]);
        }
    };
    TEST_CLASS(GeneratorTests)
    {
    public:
        /**
         * @brief Проверка чтения из потока IStreamGenerator
         */
        TEST_METHOD(IStreamGenerator_Test)
        {
            std::istringstream ss("42 15 -7");
            IStreamGenerator gen(ss);
            Assert::AreEqual(42, gen.generate());
            Assert::AreEqual(15, gen.generate());
            Assert::AreEqual(-7, gen.generate());
        }
        /**
         * @brief Проверка диапазона RandomGenerator
         */
        TEST_METHOD(RandomGenerator_Test)
        {
            RandomGenerator gen(10, 20);
            int val = gen.generate();
            Assert::IsTrue(val >= 10 && val <= 20);
        }
        /**
         * @brief Проверка генератора константами ConstGenerator
         */
        TEST_METHOD(ConstGenerator_Test)
        {
            ConstGenerator gen(99);
            Assert::AreEqual(99, gen.generate());
            Assert::AreEqual(99, gen.generate());
            ConstGenerator zeroGen(0);
            Assert::AreEqual(0, zeroGen.generate());
        }
    };
}