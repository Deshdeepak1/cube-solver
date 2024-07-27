#pragma once

#include "Cube1DArray.cpp"
#include "Cube3DArray.cpp"
#include "CubeBitboard.cpp"

std::unique_ptr<Cube> create_cube(int model_type);
