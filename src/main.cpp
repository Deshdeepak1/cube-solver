#include "main.hpp"
#include "model/Cube1dArray.cpp"
#include "model/Cube3dArray.cpp"
#include "solver/BFSSolver.hpp"
#include "solver/DFSSolver.hpp"
#include "solver/IDDFSSolver.hpp"
#include <getopt.h>
#include <ostream>

void print_version() {
  std::cout << PROJECT_NAME << " " << PROJECT_VERSION << std::endl;
}

void print_help() {
  std::cout << "Usage: " << PROJECT_NAME << " [options]\n"
            << "Options:\n"
            << "  -v, --version   Print the project version\n"
            << "  -h, --help      Print this help message\n";
}

int main(int argc, char *argv[]) {
  static struct option long_options[] = {
      {"version", no_argument, 0, 'v'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0},
  };

  char opt;
  int option_index = 0;

  // if (argv[1][0] == '1') {
  //   std::cout << 1 << std::endl;
  //   auto c = Cube1dArray();
  //   c.random_shuffle(5);
  //   DFSSolver<Cube1dArray> s(c);
  //   auto moves = s.solve();
  //   s.cube.print();
  //
  // } else {
  //   std::cout << 3 << std::endl;
  //   auto c = Cube3dArray();
  //   c.random_shuffle(5);
  //   DFSSolver<Cube3dArray> s(c);
  //   // DFSSolver<Cube3dArray> s(c);
  //   auto moves = s.solve();
  //   s.cube.print();
  // }
  // return 0;
  auto c = Cube1dArray();
  // auto c = Cube3dArray();
  c.print();
  c.random_shuffle(7);
  c.print();
  // DFSSolver<Cube1dArray> s(c);
  // BFSSolver<Cube1dArray> s(c);
  IDDFSSolver<Cube1dArray> s(c);
  // DFSSolver<Cube3dArray> s(c);
  // BFSSolver<Cube3dArray> s(c);
  // DFSSolver<Cube3dArray> s(c);
  auto moves = s.solve();
  std::cout << "Solved s.cube: " << s.cube.is_solved() << std::endl;
  for (auto move : moves) {
    c.move(move);
  }
  c.print();
  std::cout << "Solved c: " << c.is_solved() << std::endl;
  while ((opt = getopt_long(argc, argv, "vh", long_options, &option_index)) !=
         -1) {
    switch (opt) {
    case 'h':
      print_help();
      return 0;
    case 'v':
      print_version();
      return 0;
    case '?':
      return 1;
    default:
      break;
    }
  }
  return 0;
}
