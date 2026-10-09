#include "ConstGenerator.h"

miit::algebra::ConstGenerator::ConstGenerator(const int val)
    : value(val)
{
}

int miit::algebra::ConstGenerator::generate()
{
    return this->value;
}