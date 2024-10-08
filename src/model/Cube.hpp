#pragma once

#include <bits/stdc++.h>

class Cube {
 public:
  static const int total_moves = 18;
  static const int total_squares = 54;
  static const int total_face_squares = 9;
  static const int total_faces = 6;
  static const int total_rows = 3;
  static const int total_cols = 3;
  static const int top_down_offset = 7;

  enum class Color : int {
    WHITE,
    GREEN,
    RED,
    BLUE,
    ORANGE,
    YELLOW,
  };

  enum class Face : int {
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
  static void print_moves(const std::vector<Move> &moves,
                          const std::string &text = "Moves");

  virtual Color get_color(Face face, int row, int col) const = 0;

  virtual bool is_solved() const = 0;

  virtual std::unique_ptr<Cube> clone() const = 0;

  bool operator==(const Cube &other) const;

  void print() const;
  void print_moves_cube(const std::vector<Move> &moves);

  std::vector<Move> random_shuffle(int times);

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

  std::string get_corner_color_string(uint8_t ind) const;

  uint8_t get_corner_index(uint8_t ind) const;

  uint8_t get_corner_orientation(uint8_t ind) const;
};
