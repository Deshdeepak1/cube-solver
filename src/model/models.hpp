#pragma once

#include <bits/stdc++.h>

enum class MODEL {
  Cube1DArray,
  Cube3DArray,
  CubeBitboard,
  LAST,
};

inline std::string get_model(int model_type) {
  switch (model_type) {
    case 0:
      return "1DArray";
    case 1:
      return "3DArray";
    case 2:
      return "Bitboard";
    default:
      throw std::invalid_argument("Invalid model_type");
  }
}
