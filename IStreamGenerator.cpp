#include "IStreamGenerator.h"

miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in{ in }
{
}

int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    this->in >> value;
    return value;
}