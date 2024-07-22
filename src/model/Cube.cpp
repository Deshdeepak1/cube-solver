#include "Cube.hpp"
#include <vector>

char Cube::get_color_char(Color color) {

  switch (color) {
  case Color::WHITE:
    return 'W';
  case Color::GREEN:
    return 'G';
  case Color::RED:
    return 'R';
  case Color::BLUE:
    return 'B';
  case Color::ORANGE:
    return 'O';
  case Color::YELLOW:
    return 'Y';
  default:
    return '\0';
  }
}

std::string Cube::get_move(Move move) {
  switch (move) {
  case Move::U:
    return "U";
  case Move::UPRIME:
    return "U'";
  case Move::U2:
    return "U2";
  case Move::L:
    return "L";
  case Move::LPRIME:
    return "L'";
  case Move::L2:
    return "L2";
  case Move::F:
    return "F";
  case Move::FPRIME:
    return "F'";
  case Move::F2:
    return "F2";
  case Move::R:
    return "R";
  case Move::RPRIME:
    return "R'";
  case Move::R2:
    return "R2";
  case Move::B:
    return "B";
  case Move::BPRIME:
    return "B'";
  case Move::B2:
    return "B2";
  case Move::D:
    return "D";
  case Move::DPRIME:
    return "D'";
  case Move::D2:
    return "D2";
  default:
    return "";
  }
}

Cube &Cube::move(Move move) {
  switch (move) {
  case Move::U:
    return this->u();
  case Move::UPRIME:
    return this->u_prime();
  case Move::U2:
    return this->u2();
  case Move::L:
    return this->l();
  case Move::LPRIME:
    return this->l_prime();
  case Move::L2:
    return this->l2();
  case Move::F:
    return this->f();
  case Move::FPRIME:
    return this->f_prime();
  case Move::F2:
    return this->f2();
  case Move::R:
    return this->r();
  case Move::RPRIME:
    return this->r_prime();
  case Move::R2:
    return this->r2();
  case Move::B:
    return this->b();
  case Move::BPRIME:
    return this->b_prime();
  case Move::B2:
    return this->b2();
  case Move::D:
    return this->d();
  case Move::DPRIME:
    return this->d_prime();
  case Move::D2:
    return this->d2();
  default:
    return *this;
  }
}

Cube &Cube::invert(Move move) {
  switch (move) {
  case Move::U:
    return this->u_prime();
  case Move::UPRIME:
    return this->u();
  case Move::U2:
    return this->u2();
  case Move::L:
    return this->l_prime();
  case Move::LPRIME:
    return this->l();
  case Move::L2:
    return this->l2();
  case Move::F:
    return this->f_prime();
  case Move::FPRIME:
    return this->f();
  case Move::F2:
    return this->f2();
  case Move::R:
    return this->r_prime();
  case Move::RPRIME:
    return this->r();
  case Move::R2:
    return this->r2();
  case Move::B:
    return this->b_prime();
  case Move::BPRIME:
    return this->b();
  case Move::B2:
    return this->b2();
  case Move::D:
    return this->d_prime();
  case Move::DPRIME:
    return this->d();
  case Move::D2:
    return this->d2();
  default:
    return *this;
  }
}

void Cube::print() const {
  std::cout << "Cube:\n\n";

  unsigned int row, col, i;

  // Printing UP Face
  for (row = 0; row < total_rows; row++) {
    for (i = 0; i < top_down_offset; i++) {
      std::cout << " ";
    }
    for (col = 0; col < total_cols; col++) {
      std::cout << get_color_char(get_color(Face::UP, row, col)) << " ";
    }

    std::cout << "\n";
  }

  std::cout << "\n";

  // Printing Middle Faces
  for (row = 0; row < total_rows; row++) {
    for (const auto &face : middle_faces) {
      for (col = 0; col < total_cols; col++) {
        std::cout << get_color_char(get_color(face, row, col)) << " ";
      }
      std::cout << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\n";

  // Printing DOWN Face
  for (row = 0; row < total_rows; row++) {
    for (i = 0; i < top_down_offset; i++) {
      std::cout << " ";
    }
    for (col = 0; col < total_cols; col++) {
      std::cout << get_color_char(get_color(Face::DOWN, row, col)) << " ";
    }

    std::cout << "\n";
  }

  std::cout << "\n";
}

std::vector<Cube::Move> Cube::random_shuffle(unsigned int times) {
  std::vector<Move> moves;
  srand(time(0));
  for (unsigned int i = 0; i < times; i++) {
    unsigned int move_index = (rand() % total_moves);
    const Move move = static_cast<Move>(move_index);
    moves.push_back(move);
    this->move(move);
  }
  return moves;
}
