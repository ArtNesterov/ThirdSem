#include "Task2.h"
#include <cmath>
#include <vector>

miit::algebra::Task2::Task2(const size_t r, const size_t c, const std::shared_ptr<Generator>& gen)
    : Exercise(r, c, gen) 
{
}

void miit::algebra::Task2::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();
    if (r == 0 || c == 0) return;
    

    int max_abs = std::abs(matrix[0][0]);
    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            int current_abs = std::abs(matrix[i][j]);
            if (current_abs > max_abs)
            {
                max_abs = current_abs;
            }
        }
    }

    const std::vector<int> first_row = matrix.getRow(0);

    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        bool has_max = false;
        for (size_t j = 0; j < c; ++j)
        {
            if (std::abs(matrix[i][j]) == max_abs)
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