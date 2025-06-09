#include "engine/utils/PrintMatrix.hpp"
#include <iostream>

void PrintMatrix(const Matrix &m)
{
  std::cout << "[[" << m.m0 << ", " << m.m4 << ", " << m.m8 << ", " << m.m12
            << "],\n"
            << " [" << m.m1 << ", " << m.m5 << ", " << m.m9 << ", " << m.m13
            << "],\n"
            << " [" << m.m2 << ", " << m.m6 << ", " << m.m10 << ", " << m.m14
            << "],\n"
            << " [" << m.m3 << ", " << m.m7 << ", " << m.m11 << ", " << m.m15
            << "]]\n";
}
