#include "Cube.hpp"

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
    throw std::invalid_argument("Color Not Found");
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
    throw std::invalid_argument("Move Not Found");
  }
}

void Cube::print_moves(const std::vector<Move> &moves,
                       const std::string &text) {
  std::cout << text << ":- ";
  for (auto move : moves) {
    std::cout << get_move(move) << " ";
  }
  std::cout << "\n\n";
}
void Cube::print_moves_cube(const std::vector<Move> &moves) {
  for (auto move : moves) {
    std::cout << "->" << get_move(move) << "->" << "\n";
    this->move(move);
    print();
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
    throw std::invalid_argument("Move Not Found");
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
    throw std::invalid_argument("Move Not Found");
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

std::string Cube::get_corner_color_string(uint8_t ind) const {
  std::string str = "";

  switch (ind) {
  case 0:
    str += get_color_char(get_color(Face::UP, 2, 2));
    str += get_color_char(get_color(Face::FRONT, 0, 2));
    str += get_color_char(get_color(Face::RIGHT, 0, 0));
    break;
  case 1:
    str += get_color_char(get_color(Face::UP, 2, 0));
    str += get_color_char(get_color(Face::FRONT, 0, 0));
    str += get_color_char(get_color(Face::LEFT, 0, 2));
    break;
  case 2:
    str += get_color_char(get_color(Face::UP, 0, 0));
    str += get_color_char(get_color(Face::BACK, 0, 2));
    str += get_color_char(get_color(Face::LEFT, 0, 0));
    break;
  case 3:
    str += get_color_char(get_color(Face::UP, 0, 2));
    str += get_color_char(get_color(Face::BACK, 0, 0));
    str += get_color_char(get_color(Face::RIGHT, 0, 2));
    break;
  case 4:
    str += get_color_char(get_color(Face::DOWN, 0, 2));
    str += get_color_char(get_color(Face::FRONT, 2, 2));
    str += get_color_char(get_color(Face::RIGHT, 2, 0));
    break;
  case 5:
    str += get_color_char(get_color(Face::DOWN, 0, 0));
    str += get_color_char(get_color(Face::FRONT, 2, 0));
    str += get_color_char(get_color(Face::LEFT, 2, 2));
    break;
  case 6:
    str += get_color_char(get_color(Face::DOWN, 2, 2));
    str += get_color_char(get_color(Face::BACK, 2, 0));
    str += get_color_char(get_color(Face::RIGHT, 2, 2));
    break;
  case 7:
    str += get_color_char(get_color(Face::DOWN, 2, 0));
    str += get_color_char(get_color(Face::BACK, 2, 2));
    str += get_color_char(get_color(Face::LEFT, 2, 0));
    break;
  }

  return str;
}

uint8_t Cube::get_corner_index(uint8_t ind) const {
  std::string corner = get_corner_color_string(ind);

  uint8_t ret = 0;

  for (auto c : corner) {
    if (c != 'W' && c != 'Y') continue;
    if (c == 'Y') {
      ret |= (1 << 2);
    }
  }

  for (auto c : corner) {
    if (c != 'R' && c != 'O') continue;
    if (c == 'O') {
      ret |= (1 << 1);
    }
  }

  for (auto c : corner) {
    if (c != 'B' && c != 'G') continue;
    if (c == 'G') {
      ret |= (1 << 0);
    }
  }
  return ret;
}

uint8_t Cube::get_corner_orientation(uint8_t ind) const {
  std::string corner = get_corner_color_string(ind);

  std::string actual_str = "";

  for (auto c : corner) {
    if (c != 'W' && c != 'Y') continue;
    actual_str.push_back(c);
  }

  if (corner[1] == actual_str[0]) {
    return 1;
  } else if (corner[2] == actual_str[0]) {
    return 2;
  } else {
    return 0;
  }
}
