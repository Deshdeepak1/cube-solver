#include "cli.hpp"
#include "model/CubeFactory.hpp"
#include "solver/SolverFactory.hpp"

std::string get_model(int model_type) {
  switch (model_type) {
  case 1:
    return "1DArray";
  case 2:
    return "3DArray";
  case 3:
    return "Bitboard";
  default:
    throw std::invalid_argument("Invalid model_type");
  }
}

std::string get_solver(int solver_type) {
  switch (solver_type) {
  case 1:
    return "BFS";
  case 2:
    return "DFS";
  case 3:
    return "IDDFS";
  case 4:
    return "IDAStar";
  default:
    throw std::invalid_argument("Invalid solver_type");
  }
}

template <typename CubeType>
void handle_cube_operations(CubeType *cube, int solver_type,
                            unsigned int random_shuffles,
                            const std::string &corner_db_file_name) {
  cube->print();
  auto moves = cube->random_shuffle(random_shuffles);
  cube->print_moves(moves, "Random Shuffle Moves");
  cube->print();
  auto solver =
      create_solver(cube, solver_type, random_shuffles, corner_db_file_name);
  moves = solver->solve();
  cube->print_moves(moves, "Solution Moves");
  cube->print_moves_cube(moves);
}

void solve_cube(const int model_type, const int solver_type,
                const unsigned int random_shuffles,
                const std::string &corner_db_file_name) {

  std::unique_ptr<Cube> cube = create_cube(model_type);
  std::cout << "Model:- " << get_model(model_type) << "\n";
  std::cout << "Solver:- " << get_solver(solver_type) << "\n";
  std::cout << "Random Shuffles:- " << random_shuffles << "\n\n";

  switch (model_type) {
  case 1: {
    auto concrete_cube = static_cast<Cube1DArray *>(cube.get());
    handle_cube_operations(concrete_cube, solver_type, random_shuffles,
                           corner_db_file_name);
    break;
  }
  case 2: {
    auto concrete_type = static_cast<Cube3DArray *>(cube.get());
    handle_cube_operations(concrete_type, solver_type, random_shuffles,
                           corner_db_file_name);
    break;
  }
  case 3: {
    auto concrete_type = static_cast<CubeBitboard *>(cube.get());
    handle_cube_operations(concrete_type, solver_type, random_shuffles,
                           corner_db_file_name);
    break;
  }
  default:
    throw std::invalid_argument("Invalid model_type");
  }
}
