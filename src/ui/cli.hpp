#pragma once

#include "ui.hpp"

class CubeCLI : public UI {
public:
  using UI::UI;
  void run() override;
  template <typename CubeType>
  void handle_cube_operations(CubeType *cube, int solver_type,
                              unsigned int random_shuffles,
                              const std::string &corner_db_file_name);
};
