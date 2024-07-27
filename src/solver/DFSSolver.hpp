#pragma once

#include "../model/Cube.hpp"
#include "Solver.hpp"

template <typename CubeType>
class DFSSolver : public Solver<CubeType> {
private:
  // std::unordered_map<T, bool> visited;
  // std::unordered_map<T, unsigned int> depths;
  std::vector<Cube::Move> moves;
  unsigned int max_search_depth;

  bool dfs(unsigned int depth) {
    if (cube.is_solved()) return true;
    if (depth > max_search_depth) return false;
    // visited[cube] = true;
    // depths[cube] = depth;

    for (unsigned int i = 0; i < Cube::total_moves; i++) {
      Cube::Move move = Cube::Move(i);
      cube.move(move);
      moves.push_back(move);
      // if (!visited[cube] && dfs(depth + 1)) return true;
      // if ((!visited[cube] || depths[cube] > depth) && dfs(depth + 1))
      //   return true;
      if (dfs(depth + 1)) return true;
      moves.pop_back();
      cube.invert(move);
    }

    return false;
  }

public:
  static const unsigned int MAX_SEARCH_DEPTH = 8;

  CubeType cube;

  DFSSolver(CubeType cube, unsigned int max_search_depth = MAX_SEARCH_DEPTH) {
    this->cube = cube;
    this->max_search_depth = max_search_depth;
  }

  std::vector<Cube::Move> solve() {
    dfs(1);
    return moves;
  }
};
