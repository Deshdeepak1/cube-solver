#pragma once

#include <bits/stdc++.h>

enum class SOLVER {
  BFS,
  DFS,
  IDDFS,
  IDAStar,
  LAST,
};

inline std::string get_solver(int solver_type) {
  switch (solver_type) {
    case 0:
      return "BFS";
    case 1:
      return "DFS";
    case 2:
      return "IDDFS";
    case 3:
      return "IDAStar";
    default:
      throw std::invalid_argument("Invalid solver_type");
  }
}
