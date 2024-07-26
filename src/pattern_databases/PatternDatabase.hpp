#pragma once

#include "../model/Cube.hpp"
#include "NibbleArray.hpp"

class PatternDatabase {

private:
  NibbleArray database;
  size_t size;
  size_t num_items;

  PatternDatabase();

public:
  PatternDatabase(const size_t size);

  PatternDatabase(const size_t size, uint8_t init_val);

  virtual uint32_t get_database_index(const Cube &cube) const = 0;

  virtual bool set_num_moves(const Cube &cube, const uint8_t num_moves);

  virtual bool set_num_moves(const uint32_t ind, const uint8_t num_moves);

  virtual uint8_t get_num_moves(const Cube &cube) const;

  virtual uint8_t get_num_moves(const uint32_t ind) const;

  virtual size_t get_size() const;

  virtual size_t get_num_items() const;

  virtual bool is_full() const;

  virtual void to_file(const std::string &file_path) const;

  virtual bool from_file(const std::string &file_path);

  virtual std::vector<uint8_t> inflate() const;

  virtual void reset();
};
