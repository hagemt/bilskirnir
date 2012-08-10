//============================================================================
// Name        : Horton.cpp
// Author      : Tor E Hagemann
// Version     : 0.1
// Copyright   : This code is in the public domain.
// Description : A simple Conway's Game of Life emulator.
//============================================================================

#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_set>
#endif /* C++11 */

#define LIMIT (0x100L)
typedef unsigned long Word;
#define WORD_SIZE (sizeof(Word) << 3)
typedef std::vector<std::vector<bool> > World;
#define WORLD_SIZE WORD_SIZE

std::ostream& operator<<(std::ostream& out, const World& w) {
	for (World::size_type i = 0; i < w.size(); ++i) {
		for (World::size_type j = 0; j < w[i].size(); ++j) {
      out << ((w[i][j]) ? 'X' : ' ');
    }
		out << std::endl;
	}
	return out;
}

World& operator>>(std::istream& in, World& w) {
	char buffer[WORLD_SIZE];
  std::vector<bool> row;
  row.reserve(WORLD_SIZE);
  /* Each character of the file represents a cell */
	while (in.getline(buffer, WORLD_SIZE)) {
		for (char *c = buffer; *c; ++c) {
      /* Skip comment lines */
			if (*c == '!') { break; }
			row.push_back((*c == 'O'));
		}
		if (!row.empty()) {
      w.push_back(row);
    }
    row.clear();
	}
	return w;
}

int main(int argc, char** argv) {
	World world;
  std::ifstream input;

	while (--argc) {
		input.open(argv[argc]);
    if (input) {
      std::cout << (input >> world) << std::endl;
      input.close();
    } else {
      std::cerr << "[ERROR] cannot open: " << argv[argc] << std::endl;
    }
    world.clear();
	}

  #if __cplusplus > 199711L
  std::unordered_set<Word> history;
  #endif /* C++11 */

  std::cout << "Testing first " << LIMIT << " strings..." << std::endl;
	for (Word w = 0; w < LIMIT; ++w) {
    std::bitset<WORD_SIZE> line(w);
    std::cout << std::string(WORD_SIZE + 8, '-') << std::endl;
    std::cout << "BEGIN:\t" << line.to_string() << std::endl;;
		for (size_t i = 1; line.any() ^ line.all(); ++i) {
			for (size_t j = 1; j + 1 < line.size(); ++j) {
				line[j] = (line[j - 1] ^ line[j + 1]);
			}
      std::cout << "\rTEST:\t" << line.flip().to_string();
      #if __cplusplus > 199711L
      if (!history.insert(line.to_ulong()).second) {
        std::cout << "\rCYCLE:\t" << "PATTERN REPEATED AFTER " << i << " ITERATION(S)" << std::endl;
        history.clear();
        break;
      }
      #else
      if (i > LIMIT) { break; }
      #endif /* C++11 */
		}
    std::cout << "\rFINAL:\t" << line.to_string() << std::endl;
	}
  std::cout << std::string(WORD_SIZE + 8, '-') << std::endl;
  std::cout << "Finished performing " << LIMIT << " tests." << std::endl;
	return 0;
}
