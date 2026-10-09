#pragma once
#include "Generator.h"

namespace miit::algebra
{
    class ConstGenerator : public Generator
    {
    private:
        int value;

    public:
        ConstGenerator(const int val = 0);
        int generate() override;
    };
}