/*
 * Tensor.cpp
 *
 *  Created on: May 18, 2011
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */

#include <iomanip>
#include <iostream>

#include "tensor.h"

int main(int argc, char * argv[]) {
  Tensor<size_t, 2> t;
  for (size_t x = 0; x < DEFAULT_SIZE; ++x) {
    std::cout << "{" << std::endl;
    for (size_t y = 0; y < DEFAULT_SIZE; ++y) {
      std::cout << "[";
      for (size_t z = 0; z < DEFAULT_SIZE; ++z) {
        std::cout << std::setw(3) << std::right << t[x][y][z];
      }
      std::cout << " ]" << std::endl;
    }
    std::cout << " }";
  }
  std::cout << std::endl;
  return 0;
}
