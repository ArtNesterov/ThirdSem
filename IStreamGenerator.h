#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;
    public:
        IStreamGenerator(std::istream& in = std::cin);
        int generate() override;
    };
}