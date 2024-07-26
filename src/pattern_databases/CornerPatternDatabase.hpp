#pragma once

#include "../model/Cube.hpp"
#include "PatternDatabase.hpp"
#include "PermutationIndexer.hpp"

class CornerPatternDatabase : public PatternDatabase {

private:
  PermutationIndexer<8> perm_indexer;

public:
  CornerPatternDatabase();
  CornerPatternDatabase(uint8_t init_val);
  uint32_t get_database_index(const Cube &cube) const;
};
