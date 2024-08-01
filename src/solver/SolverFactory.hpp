#pragma once

#include "BFSSolver.hpp"
#include "DFSSolver.hpp"
#include "IDAStarSolver.hpp"
#include "IDDFSSolver.hpp"
#include "Solver.hpp"

template <typename CubeType>
std::unique_ptr<Solver<CubeType>> create_solver(
  CubeType *cube, const int solver_type, const int random_shuffles,
  const std::string &corner_db_file_name) {
  switch (solver_type) {
    case 0:
      return std::make_unique<BFSSolver<CubeType>>(*cube);
    case 1:
      return std::make_unique<DFSSolver<CubeType>>(*cube, random_shuffles);
    case 2:
      return std::make_unique<IDDFSSolver<CubeType>>(*cube, random_shuffles);
    case 3:
      return std::make_unique<IDAStarSolver<CubeType>>(*cube,
                                                       corner_db_file_name);
    default:
      throw std::invalid_argument("Invalid solver_type");
  }
}
