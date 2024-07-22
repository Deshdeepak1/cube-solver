#pragma once

#include <bits/stdc++.h>
#include <vector>

class Cube {
public:
  static const unsigned int total_moves = 18;
  static const unsigned int total_faces = 6;
  static const unsigned int total_rows = 3;
  static const unsigned int total_cols = 3;
  static const unsigned int top_down_offset = 7;

  enum class Color : unsigned int {
    WHITE,
    GREEN,
    RED,
    BLUE,
    ORANGE,
    YELLOW,
  };

  enum class Face : unsigned int {
    UP,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN,
  };

  static constexpr Face middle_faces[4] = {
      Face::LEFT,
      Face::FRONT,
      Face::RIGHT,
      Face::BACK,
  };

  // clang-format off
  enum class Move {
    U, UPRIME, U2,
    L, LPRIME, L2,
    F, FPRIME, F2,
    R, RPRIME, R2,
    B, BPRIME, B2,
    D, DPRIME, D2,
  };
  // clang-format on

  static char get_color_char(Color color);
  static std::string get_move(Move move);

  virtual Color get_color(Face face, unsigned int row,
                          unsigned int col) const = 0;

  virtual bool is_solved() const = 0;

  void print() const;

  std::vector<Move> random_shuffle(unsigned int times);

  Cube &move(Move move);

  Cube &invert(Move move);

  virtual Cube &u() = 0;
  virtual Cube &u_prime() = 0;
  virtual Cube &u2() = 0;

  virtual Cube &l() = 0;
  virtual Cube &l_prime() = 0;
  virtual Cube &l2() = 0;

  virtual Cube &f() = 0;
  virtual Cube &f_prime() = 0;
  virtual Cube &f2() = 0;

  virtual Cube &r() = 0;
  virtual Cube &r_prime() = 0;
  virtual Cube &r2() = 0;

  virtual Cube &b() = 0;
  virtual Cube &b_prime() = 0;
  virtual Cube &b2() = 0;

  virtual Cube &d() = 0;
  virtual Cube &d_prime() = 0;
  virtual Cube &d2() = 0;
};
