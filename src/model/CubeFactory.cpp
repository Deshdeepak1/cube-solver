#include "CubeFactory.hpp"

std::unique_ptr<Cube> create_cube(int model_type) {
  switch (model_type) {
  case 1:
    return std::make_unique<Cube1DArray>();
  case 2:
    return std::make_unique<Cube3DArray>();
  case 3:
    return std::make_unique<CubeBitboard>();
  default:
    throw std::invalid_argument("Invalid model_type");
  }
}
