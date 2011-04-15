/*
 * Feap.cpp
 *
 *  Created on: Dec 20, 2010
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */
#include <iostream>
#include <cstdlib>
#include "Feap.h"

int main(int argc, char** argv) {
	Feap<int> f;
	while (--argc) { f.insert(atoi(argv[argc])); }
	while (!f.empty()) { std::cout << f.find_min() << " "; f.delete_min(); }
	std::cout << std::endl;
	return 0;
}
