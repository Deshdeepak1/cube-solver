#include "math.hpp"

uint32_t factorial(uint32_t n) { return n <= 1 ? 1 : n * factorial(n - 1); }

uint32_t n_p_k(uint32_t n, uint32_t k) {
  return factorial(n) / factorial(n - k);
}

uint32_t n_c_k(uint32_t n, uint32_t k) {
  return (n < k) ? 0 : factorial(n) / (factorial(n - k) * factorial(k));
}
