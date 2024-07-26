#pragma once

#include <bits/stdc++.h>
#include <vector>

class NibbleArray {
private:
  size_t size;
  std::vector<uint8_t> arr;

public:
  NibbleArray(const size_t size, const uint8_t val = 0xFF);

  uint8_t get(const size_t pos) const;

  void set(const size_t pos, const uint8_t val);

  unsigned char *data();

  const unsigned char *data() const;

  size_t storage_size() const;

  void inflate(std::vector<uint8_t> &dest) const;

  void reset(const uint8_t val = 0xFF);
};
