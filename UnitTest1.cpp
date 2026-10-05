#include "CppUnitTest.h"
#include <vector>
#include <memory>
#include <sstream>
#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace Tests
{
    class ConstTestGenerator : public Generator
    {
    private:
        int value;
    public:
        ConstTestGenerator(const int val) : value(val) {}
        int generate() override { return value; }
    };

    /**
     * @brief Вспомогательный генератор для теста метода fill
     */
    class ConstTestGenerator : public miit::algebra::Generator
    {
    private:
        int value;
    public:
        ConstTestGenerator(const int val) : value(val) {}
        int generate() override { return value; }
    };


    TEST_CLASS(MatrixTests)
    {
    public:
     /**
     * @brief Проверка конструкторов и базовых геттеров
     */
        TEST_METHOD(TestConstructorsAndGetters)
        {
            // Конструктор по умолчанию
            miit::algebra::Matrix<int> m1;
            Assert::AreEqual(static_cast<size_t>(0), m1.getRows());
            Assert::AreEqual(static_cast<size_t>(0), m1.getCols());

            // Конструктор с параметрами
            miit::algebra::Matrix<int> m2(3, 4);
            Assert::AreEqual(static_cast<size_t>(3), m2.getRows());
            Assert::AreEqual(static_cast<size_t>(4), m2.getCols());
        }

     /**
     * @brief Проверка оператора индексации
     */
        TEST_METHOD(TestIndexOperator)
        {
            miit::algebra::Matrix<int> m(2, 2);
            m[0, 0] = 10;
            m[1, 1] = 20;

            Assert::AreEqual(10, m[0, 0]);
            Assert::AreEqual(20, m[1, 1]);
        }


     /**
     * @brief Проверка выброса исключения при выходе за границы диапазона
     */
        TEST_METHOD(TestIndexOutOfRangeThrow)
        {
            miit::algebra::Matrix<int> m(2, 2);

            auto badAccess = [&m]() {
                m[5, 0] = 99; // Обращение к несуществующей 5-й строке
                };

            Assert::ExpectException<std::out_of_range>(badAccess);
        }

     /**
     * @brief Проверка метода fill через генератор
     */
        TEST_METHOD(TestFillMethod)
        {
            miit::algebra::Matrix<int> m(2, 3);
            auto gen = std::make_shared<ConstTestGenerator>(7);

            m.fill(gen);

            for (size_t i = 0; i < m.getRows(); ++i) {
                for (size_t j = 0; j < m.getCols(); ++j) {
                    Assert::AreEqual(7, m[i, j]);
                }
            }
        }

     /**
     * @brief Проверка методов работы со строками (getRow и insertRow)
     */
        TEST_METHOD(TestRowOperations)
        {
            miit::algebra::Matrix<int> m(2, 2);
            m[0, 0] = 1; m[0, 1] = 2;
            m[1, 0] = 3; m[1, 1] = 4;

            // Проверка getRow
            std::vector<int> row0 = m.getRow(0);
            Assert::AreEqual(1, row0[0]);
            Assert::AreEqual(2, row0[1]);

            // Проверка insertRow
            std::vector<int> newRow = { 8, 9 };
            m.insertRow(1, newRow);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(8, m[1, 0]);  // Новая вставленная строка
            Assert::AreEqual(9, m[1, 1]);
            Assert::AreEqual(3, m[2, 0]);  // Бывшая строка 1 сместилась вниз
        }

     /**
     * @brief Проверка метода toString() и потокового вывода
     */
        TEST_METHOD(TestStringRepresentation)
        {
            miit::algebra::Matrix<int> m(1, 2);
            m[0, 0] = 5;
            m[0, 1] = 10;

            std::string expected = "5\t10\t\n";

            Assert::AreEqual(expected, m.toString());

            std::ostringstream ss;
            ss << m;
            Assert::AreEqual(expected, ss.str());
        }

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
         * @brief Проверка конструктора с параметрами и доступа к элементам
         */
        TEST_METHOD(ParameterizedConstructorAndAccess_Test)
        {
            Matrix<int> m(2, 3);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(3), m.getCols());

            m(1, 2) = 5;
            Assert::AreEqual(5, m(1, 2));
        }

        /**
         * @brief Проверка вставки новой строки
         */
        TEST_METHOD(InsertRow_Test)
        {
            Matrix<int> m(2, 2);
            m(0, 0) = 1; m(0, 1) = 2;
            m(1, 0) = 3; m(1, 1) = 4;

            std::vector<int> newRow = { 5, 6 };
            m.insertRow(1, newRow);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(1, m(0, 0));
            Assert::AreEqual(5, m(1, 0)); 
            Assert::AreEqual(6, m(1, 1));
            Assert::AreEqual(3, m(2, 0)); 
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

            Assert::AreEqual(1, res(0, 0));
            Assert::AreEqual(0, res(0, 1));
            Assert::AreEqual(0, res(1, 0));
            Assert::AreEqual(2, res(1, 1));
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
            Assert::AreEqual(1, res(0, 0));
            Assert::AreEqual(2, res(0, 1));
            Assert::AreEqual(-5, res(1, 0));
            Assert::AreEqual(4, res(1, 1));
            Assert::AreEqual(1, res(2, 0));
            Assert::AreEqual(2, res(2, 1));
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

    };

}

