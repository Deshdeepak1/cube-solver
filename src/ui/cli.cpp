#include "cli.hpp"

template <typename CubeType>
void CubeCLI::handle_cube_operations(CubeType *cube, int solver_type,
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

void CubeCLI::run() {
  std::unique_ptr<Cube> cube = create_cube(model_selected);
  std::cout << "Model:- " << get_model(model_selected) << "\n";
  std::cout << "Solver:- " << get_solver(solver_selected) << "\n";
  std::cout << "Random Shuffles:- " << random_shuffles << "\n\n";
  switch (model_selected) {
    case 0: {
      auto concrete_cube = static_cast<Cube1DArray *>(cube.get());
      handle_cube_operations(concrete_cube, solver_selected, random_shuffles,
                             corner_db_file_name);
      break;
    }
    case 1: {
      auto concrete_type = static_cast<Cube3DArray *>(cube.get());
      handle_cube_operations(concrete_type, solver_selected, random_shuffles,
                             corner_db_file_name);
      break;
    }
    case 2: {
      auto concrete_type = static_cast<CubeBitboard *>(cube.get());
      handle_cube_operations(concrete_type, solver_selected, random_shuffles,
                             corner_db_file_name);
      break;
    }
    default:
      throw std::invalid_argument("Invalid model_selected");
  }
}
