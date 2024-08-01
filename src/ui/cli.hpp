#pragma once

#include "ui.hpp"

class CubeCLI : public UI {
  void select_model_solve_cube(Cube *cube);

  template <typename CubeType>
  void select_solver_solve_cube(CubeType *cube);

 public:
  using UI::UI;
  void run() override;
};
