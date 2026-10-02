#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    class RandomGenerator : public Generator
    {
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 generator;
    public:
        RandomGenerator(const int min, const int max);
        int generate() override;
    };
}