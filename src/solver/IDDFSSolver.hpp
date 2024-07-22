#pragma once

#include "../model/Cube.hpp"
#include "./DFSSolver.hpp"

template <typename T>
class IDDFSSolver {
private:
  std::vector<Cube::Move> moves;
  unsigned int max_search_depth;

public:
  static const unsigned int MAX_SEARCH_DEPTH = 8;

  T cube;

  IDDFSSolver(T cube, unsigned int max_search_depth = MAX_SEARCH_DEPTH) {
    this->cube = cube;
    this->max_search_depth = max_search_depth;
  }

  std::vector<Cube::Move> solve() {
    for (unsigned int i = 1; i <= max_search_depth; i++) {
      DFSSolver<T> dfsSolver(cube, i);
      moves = dfsSolver.solve();
      if (dfsSolver.cube.is_solved()) {
        cube = dfsSolver.cube;
        break;
      }
    }
    return moves;
  }
};
