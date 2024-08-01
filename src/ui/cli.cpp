#include "cli.hpp"

template <typename CubeType>
void CubeCLI::select_solver_solve_cube(CubeType *cube) {
  cube->print();
  auto moves = cube->random_shuffle(random_shuffles);
  cube->print_moves(moves, "Random Shuffle Moves");
  cube->print();
  auto solver =
    create_solver(cube, solver_selected, random_shuffles, corner_db_file_name);
  moves = solver->solve();
  cube->print_moves(moves, "Solution Moves");
  cube->print_moves_cube(moves);
}

void CubeCLI::select_model_solve_cube(Cube *cube) {
  switch (model_selected) {
    case 0: {
      auto concrete_cube = static_cast<Cube1DArray *>(cube);
      select_solver_solve_cube(concrete_cube);
      break;
    }
    case 1: {
      auto concrete_type = static_cast<Cube3DArray *>(cube);
      select_solver_solve_cube(concrete_type);
      break;
    }
    case 2: {
      auto concrete_type = static_cast<CubeBitboard *>(cube);
      select_solver_solve_cube(concrete_type);
      break;
    }
    default:
      throw std::invalid_argument("Invalid model_type");
  }
}

void CubeCLI::run() {
  std::unique_ptr<Cube> cube = create_cube(model_selected);
  std::cout << "Model:- " << get_model(model_selected) << "\n";
  std::cout << "Solver:- " << get_solver(solver_selected) << "\n";
  std::cout << "Random Shuffles:- " << random_shuffles << "\n\n";
  select_model_solve_cube(cube.get());
}
