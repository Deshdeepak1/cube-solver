#include "CornerPatternDatabase.hpp"

CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(100179840) {}

CornerPatternDatabase::CornerPatternDatabase(uint8_t init_val)
    : PatternDatabase(100179840, init_val) {}

uint32_t CornerPatternDatabase::get_database_index(const Cube &cube) const {

  std::array<uint8_t, 8> corner_prem = {
      cube.get_corner_index(0), cube.get_corner_index(1),
      cube.get_corner_index(2), cube.get_corner_index(3),
      cube.get_corner_index(4), cube.get_corner_index(5),
      cube.get_corner_index(6), cube.get_corner_index(7),
  };

  uint32_t rank = this->perm_indexer.rank(corner_prem);

  std::array<uint8_t, 7> corner_orientations = {
      cube.get_corner_orientation(0), cube.get_corner_orientation(1),
      cube.get_corner_orientation(2), cube.get_corner_orientation(3),
      cube.get_corner_orientation(4), cube.get_corner_orientation(5),
      cube.get_corner_orientation(6),
  };

  uint32_t orientation_num =
      corner_orientations[0] * 729 + corner_orientations[1] * 243 +
      corner_orientations[2] * 81 + corner_orientations[3] * 27 +
      corner_orientations[4] * 9 + corner_orientations[5] * 3 +
      corner_orientations[6];

  return (rank * 2187) + orientation_num;
}
