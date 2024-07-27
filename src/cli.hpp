#pragma once
#include "model/CubeFactory.hpp"
#include "solver/SolverFactory.hpp"

void solve_cube(const int model_type, const int solver_type,
                const unsigned int random_shuffles,
                const std::string &corner_db_file_name);
