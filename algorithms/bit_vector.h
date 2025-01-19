// Copyright (c) 2025 Elric Neumann. All rights reserved. MIT license.
//
// bit_vector.h - v1.0 - Bit Vector Library
//
// A single-file header-only library for bit vector operations.
//
// USAGE:
//  #define BIT_VECTOR_IMPL
//  #include "bit_vector.h"
//
// NOTES:
//  - Uses C++11 features
//  - No external dependencies
//  - Define BIT_VECTOR_IMPL in exactly one source file

#ifndef BIT_VECTOR_H_INCL
#define BIT_VECTOR_H_INCL

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

class bit_vector {
 private:
  std::vector<unsigned char> data;
  size_t num_bits;
  static const size_t BITS_PER_BYTE = 8;

 public:
  /**
   * Constructs a bit vector of the specified size.
   * All bits are initialized to 0.
   * @param size Number of bits to store
   */
  bit_vector(size_t size = 0);

  /**
   * Sets the bit at the specified position to 1.
   * @param pos Position of the bit to set
   * @throws std::out_of_range if pos >= size
   */
  void set(size_t pos);

  /**
   * Sets the bit at the specified position to 0.
   * @param pos Position of the bit to clear
   * @throws std::out_of_range if pos >= size
   */
  void clear(size_t pos);

  /**
   * Toggles (flips) the bit at the specified position.
   * @param pos Position of the bit to toggle
   * @throws std::out_of_range if pos >= size
   */
  void toggle(size_t pos);

  /**
   * Tests if the bit at the specified position is set.
   * @param pos Position of the bit to test
   * @return true if the bit is set, false otherwise
   * @throws std::out_of_range if pos >= size
   */
  bool test(size_t pos) const;

  /**
   * Returns the size of the bit vector in bits.
   * @return Number of bits in the vector
   */
  size_t size() const;

  /**
   * Counts the number of bits that are set to 1.
   * @return Number of set bits
   */
  size_t count() const;

  /**
   * Converts the bit vector to a string of 1's and 0's.
   * @return String representation of the bit vector
   */
  std::string to_string() const;
};

#endif  // BIT_VECTOR_H_INCL

#ifdef BIT_VECTOR_IMPL

bit_vector::bit_vector(size_t size) : num_bits(size) {
  data.resize((size + BITS_PER_BYTE - 1) / BITS_PER_BYTE, 0);
}

void bit_vector::set(size_t pos) {
  if (pos >= num_bits) {
    throw std::out_of_range("position out of range");
  }

  data[pos / BITS_PER_BYTE] |= (1 << (pos % BITS_PER_BYTE));
}

void bit_vector::clear(size_t pos) {
  if (pos >= num_bits) {
    throw std::out_of_range("position out of range");
  }

  data[pos / BITS_PER_BYTE] &= ~(1 << (pos % BITS_PER_BYTE));
}

void bit_vector::toggle(size_t pos) {
  if (pos >= num_bits) {
    throw std::out_of_range("position out of range");
  }

  data[pos / BITS_PER_BYTE] ^= (1 << (pos % BITS_PER_BYTE));
}

bool bit_vector::test(size_t pos) const {
  if (pos >= num_bits) {
    throw std::out_of_range("position out of range");
  }

  return (data[pos / BITS_PER_BYTE] & (1 << (pos % BITS_PER_BYTE))) != 0;
}

size_t bit_vector::size() const { return num_bits; }

size_t bit_vector::count() const {
  size_t count = 0;

  for (size_t i = 0; i < num_bits; ++i) {
    if (test(i)) {
      ++count;
    }
  }

  return count;
}

std::string bit_vector::to_string() const {
  std::string out;
  out.reserve(num_bits);

  for (size_t i = 0; i < num_bits; ++i) {
    out += test(i) ? '1' : '0';
  }

  return out;
}

#endif  // BIT_VECTOR_IMPL
