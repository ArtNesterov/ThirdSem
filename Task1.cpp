#include "Task1.h"

miit::algebra::Task1::Task1(const size_t r, const size_t c, Generator& gen) 
    : Exercise(r, c, gen)
{
}

void miit::algebra::Task1::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    for (size_t j = 0; j < c; ++j)
    {
        int max_val = matrix[0][j];

        for (size_t i = 1; i < r; ++i)
        {
            if (matrix[i][j] > max_val)
            {
                max_val = matrix[i][j];
            }
        }

       
        for (size_t i = 0; i < r; ++i)
        {
            if (matrix[i][j] == max_val)
            {
                matrix[i][j] = 0;
            }
        }
    }
}