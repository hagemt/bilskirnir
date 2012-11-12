/*
 * Tensor.cpp
 *
 *  Created on: May 18, 2011
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */

#include <complex>
#include <iomanip>
#include <iostream>

template<typename T> std::ostream &
print(const T& t, size_t width = 0)
{
  if (width > 0) {
    std::cout << std::setw(width);
  }
  return std::cout << std::right << t;
}

#include "tensor.h"

#define I std::complex<double>(0, 1)
#define N 7

int
main(void)
{
  Tensor<std::complex<double>, 2> t(N, I);
  for (size_t x = 0; x < N; ++x) {
    print("rows {") << std::endl;
    for (size_t y = 0; y < N; ++y) {
      print("[", N);
      for (size_t z = 0; z < N; ++z) {
        print(t[x][y][z], N);
      }
      print("]", N) << std::endl;
    }
    print("}") << std::endl;
  }
  return 0;
}
