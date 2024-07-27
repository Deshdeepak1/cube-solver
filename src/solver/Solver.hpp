#pragma once

#include "../model/Cube.hpp"
#include <bits/stdc++.h>

template <typename CubeType>
class Solver {
public:
  virtual ~Solver() = default;
  virtual std::vector<Cube::Move> solve() = 0;
};
