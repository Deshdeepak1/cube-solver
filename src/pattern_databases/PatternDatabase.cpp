#include "PatternDatabase.hpp"
#include <ios>
#include <stdexcept>
#include <vector>

PatternDatabase::PatternDatabase(const size_t size)
    : database(size, 0xFF), size(size), num_items(0) {}

PatternDatabase::PatternDatabase(const size_t size, uint8_t init_val)
    : database(size, init_val), size(size), num_items(0) {}

bool PatternDatabase::set_num_moves(const uint32_t ind, uint8_t num_moves) {
  uint8_t old_moves = this->get_num_moves(ind);

  if (old_moves == 0xF) {
    ++this->num_items;
  }

  if (old_moves > num_moves) {
    this->database.set(ind, num_moves);
    return true;
  }

  return false;
}

bool PatternDatabase::set_num_moves(const Cube &cube, const uint8_t num_moves) {
  return this->set_num_moves(this->get_database_index(cube), num_moves);
}

uint8_t PatternDatabase::get_num_moves(const uint32_t ind) const {
  return this->database.get(ind);
}

uint8_t PatternDatabase::get_num_moves(const Cube &cube) const {
  return this->get_num_moves(this->get_database_index(cube));
}

size_t PatternDatabase::get_size() const { return this->size; }

size_t PatternDatabase::get_num_items() const { return this->num_items; }

bool PatternDatabase::is_full() const { return this->num_items == this->size; }

void PatternDatabase::to_file(const std::string &file_path) const {
  std::ofstream writer(file_path,
                       std::ios::out | std::ios::binary | std::ios::trunc);

  if (!writer.is_open()) {
    throw std::runtime_error("Failed to open the file to write");
  }

  writer.write(reinterpret_cast<const char *>(this->database.data()),
               this->database.storage_size());

  writer.close();
}

bool PatternDatabase::from_file(const std::string &file_path) {
  std::ifstream reader(file_path, std::ios::in | std::ios::ate);

  if (!reader.is_open()) {
    return false;
  }

  size_t file_size = reader.tellg();

  if (file_size != this->database.storage_size()) {
    reader.close();
    throw std::runtime_error("Database corrup! Failed to open Reader");
  }

  reader.seekg(0, std::ios::beg);

  reader.read(reinterpret_cast<char *>(this->database.data()),
              this->database.storage_size());
  reader.close();
  this->num_items = this->size;
  return true;
}

std::vector<uint8_t> PatternDatabase::inflate() const {
  std::vector<uint8_t> inflated;
  this->database.inflate(inflated);
  return inflated;
}

void PatternDatabase::reset() {
  if (this->num_items != 0) {
    this->database.reset(0xFF);
    this->num_items = 0;
  }
}
