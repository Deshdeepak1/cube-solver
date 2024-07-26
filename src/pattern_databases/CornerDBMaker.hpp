#pragma once

#include "CornerPatternDatabase.hpp"

class CornerDBMaker {
private:
  std::string file_name;
  CornerPatternDatabase corner_db;

public:
  CornerDBMaker(std::string file_name);
  CornerDBMaker(std::string file_name, uint8_t init_val);

  bool bfs_and_store();
};
