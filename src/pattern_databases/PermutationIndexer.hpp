#pragma once

#include "bits/stdc++.h"
#include "math.hpp"

template <size_t N, size_t K = N>
class PermutationIndexer {
  // Precomputed table containing the number of ones in the binary
  // representation of each number.  The largest N-bit number is
  // 2^N-1 = (1 << N) - 1.
  std::array<uint32_t, (1 << N) - 1> ones_count_lookup;

  // Precomputed table of factorials (or "n_p_k" if N != K).  They're in
  // reverse order.
  std::array<uint32_t, K> factorials;

public:
  /**
   * Popluate factorials and ones-count tables.
   */
  PermutationIndexer() {
    for (uint32_t i = 0; i < (1 << N) - 1; ++i) {
      std::bitset<N> bits(i);
      this->ones_count_lookup[i] = bits.count();
    }

    for (uint32_t i = 0; i < K; ++i)
      this->factorials[i] = n_p_k(N - 1 - i, K - 1 - i);
  }

  /**
   * Calculate the lexicographic rank (the index) of a permutation in O(n)
   * complexity.
   */
  uint32_t rank(const std::array<uint8_t, K> &perm) const {
    // This will hold the Lehmer code (in a factorial number system).
    std::array<uint32_t, K> lehmer;

    // Set of "seen" digits in the permutation.
    std::bitset<N> seen;

    // The first digit of the Lehmer code is always the first digit of
    // the permutation.
    lehmer[0] = perm[0];

    // Mark the digit as seen (bitset uses right-to-left indexing).
    seen[N - 1 - perm[0]] = 1;

    for (uint32_t i = 1; i < K; ++i) {
      seen[N - 1 - perm[i]] = 1;

      // The number of "seen" digits to the left of this digit is the
      // count of ones left of this digit.
      uint32_t numOnes =
          this->ones_count_lookup[seen.to_ulong() >> (N - perm[i])];

      lehmer[i] = perm[i] - numOnes;
    }

    // Convert the Lehmer code to base-10.
    uint32_t index = 0;

    for (uint32_t i = 0; i < K; ++i)
      index += lehmer[i] * this->factorials[i];

    return index;
  }
};
