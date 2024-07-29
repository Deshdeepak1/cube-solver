#pragma once

#include <bits/stdc++.h>

#include "../model/CubeFactory.hpp"
#include "../model/models.hpp"
#include "../solver/SolverFactory.hpp"
#include "../solver/solvers.hpp"

class UI {
 protected:
  int model_selected;
  int solver_selected;
  int random_shuffles;
  std::string corner_db_file_name;

 public:
  UI(const int model_type, const int solver_type,
     const unsigned int random_shuffles, const std::string &corner_db_file_name)
      : model_selected(model_type - 1),
        solver_selected(solver_type - 1),
        random_shuffles(random_shuffles),
        corner_db_file_name(corner_db_file_name){};

  virtual void run() = 0;
};
