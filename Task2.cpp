#include "Task2.h"
#include <cmath>
#include <vector>

miit::algebra::Task2::Task2(size_t r, size_t c, std::shared_ptr<Generator> gen)
    : Exercise(r, c, gen) 
{
}

void miit::algebra::Task2::solve()
{
    if (matrix.getRows() == 0) return;

    size_t r = matrix.getRows();
    size_t c = matrix.getCols();
    int max_abs = std::abs(matrix(0, 0));

    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j) 
        {
            int current_abs = std::abs(matrix(i, j));
            if (current_abs > max_abs) 
            {
                max_abs = current_abs;
            }
        }
    }

    std::vector<int> first_row = matrix.getRow(0);

    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        bool has_max = false;
        for (size_t j = 0; j < c; ++j)
        {
            if (std::abs(matrix(i, j)) == max_abs)
            {
                has_max = true;
                break;
            }
        }

        if (has_max)
        {
            matrix.insertRow(i + 1, first_row);
            i++; 
        }
    }
}