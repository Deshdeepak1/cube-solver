#include "main.hpp"
#include "model/Cube1dArray.cpp"
#include "model/Cube3dArray.cpp"
#include <bits/stdc++.h>
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

  auto c = Cube1dArray();
  c.print();
  c.l();
  c.print();
  c.r_prime();
  c.print();
  std::cout << c.is_solved() << std::endl;
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
