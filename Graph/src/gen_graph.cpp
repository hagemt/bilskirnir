#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

int
main(int argc, char ** argv)
{
  /* Accept only two arguments */
  if (argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " graph_file N" << std::endl;
    return EXIT_FAILURE;
  }

  /* Specify an output file */
  std::ofstream graph_file(argv[1]);
  if (!graph_file) {
    std::cerr << "ERROR: cannot write to '" << argv[1] << "'" << std::endl;
    return EXIT_FAILURE;
  }

  /* Parse the vertex number */
  char * residue;
  long n = 0, count = 0;
  n = strtol(argv[2], &residue, 10);
  if (n < 1 || *residue != '\0') {
    std::cerr << "ERROR: invalid N '" << argv[2] << "'" << std::endl;
    return EXIT_FAILURE;
  }

  /* Generate a graph of n possible vertices (0.5 chance of each edge) */
  std::cout << "INFO: generating graph_file '" << argv[1]
            << "' (N=" << argv[2] << ")" << std::endl;
  srand(static_cast<unsigned int>(time(NULL)));
  for (long i = 1; i <= n; ++i) {
    for (long j = i + 1; j <= n; ++j) {
      if (rand() % 2) {
        graph_file << i << ";" << j << ";" << ++count << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}

