#include "Cube.hpp"

class CubeBitboard : public Cube {
 private:
  uint64_t solved_bitboard[6]{};

  int arr[3][3] = {
    {0, 1, 2},
    {7, 8, 3},
    {6, 5, 4},
  };

  constexpr static uint64_t one_8 = (1 << 8) - 1, one_24 = (1 << 24) - 1;

  void rotate_face(const int face_index) {
    bitboard[face_index] =
      (bitboard[face_index] << 16) | (bitboard[face_index] >> (64 - 16));
  };

  void rotate_side(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1,
                   int s2_2, int s2_3) {
    uint64_t color1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);
    uint64_t color2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);
    uint64_t color3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

    bitboard[s1] =
      (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (color1 << (8 * s1_1));
    bitboard[s1] =
      (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (color2 << (8 * s1_2));
    bitboard[s1] =
      (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (color3 << (8 * s1_3));
  }

 public:
  uint64_t bitboard[6]{};

  CubeBitboard() {
    for (int side = 0; side < total_faces; side++) {
      uint64_t color = 1 << side;
      bitboard[side] = 0;
      for (int face_idx = 0; face_idx < 8; face_idx++) {
        bitboard[side] |= color << (8 * face_idx);
      }
      solved_bitboard[side] = bitboard[side];
    }
  }

  void set_cubies(const Color cube[total_faces][total_rows][total_cols]) {
    for (int side = 0; side < total_faces; side++) {
      uint64_t color = 1 << side;
      bitboard[side] = 0;
      for (int face_idx = 0; face_idx < 8; face_idx++) {
        bitboard[side] |= color << (8 * face_idx);
      }
      solved_bitboard[side] = bitboard[side];
    }
  }

  Color get_color(Face face, int row, int col) const override {
    const int face_index = static_cast<int>(face);
    int idx = arr[row][col];
    if (idx == 8) return Color(face_index);

    uint64_t side = bitboard[face_index];
    uint64_t color = (side >> (8 * idx)) & one_8;

    int bit_pos = 0;

    while (color != 0) {
      color = color >> 1;
      bit_pos++;
    }

    return Color(bit_pos - 1);
  }

  bool is_solved() const override {
    for (int i = 0; i < 6; i++) {
      if (solved_bitboard[i] != bitboard[i]) return false;
    }
    return true;
  }

  Cube &u() override {
    const int face_index = static_cast<int>(Face::UP);
    this->rotate_face(face_index);

    uint64_t temp = bitboard[2] & one_24;
    bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
    bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
    bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
    bitboard[1] = (bitboard[1] & ~one_24) | temp;

    return *this;
  }

  Cube &u_prime() override {
    this->u();
    this->u();
    this->u();
    return *this;
  }

  Cube &u2() override {
    this->u();
    this->u();
    return *this;
  }

  Cube &l() override {
    const int face_index = static_cast<int>(Face::LEFT);
    this->rotate_face(face_index);

    uint64_t color1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
    uint64_t color2 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);
    uint64_t color3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

    this->rotate_side(2, 0, 7, 6, 0, 0, 7, 6);
    this->rotate_side(0, 0, 7, 6, 4, 4, 3, 2);
    this->rotate_side(4, 4, 3, 2, 5, 0, 7, 6);

    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (color1 << (8 * 0));
    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (color2 << (8 * 7));
    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (color3 << (8 * 6));

    return *this;
  }

  Cube &l_prime() override {
    this->l();
    this->l();
    this->l();
    return *this;
  }

  Cube &l2() override {
    this->l();
    this->l();
    return *this;
  }

  Cube &f() override {
    const int face_index = static_cast<int>(Face::FRONT);
    this->rotate_face(face_index);

    uint64_t color1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
    uint64_t color2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
    uint64_t color3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);

    this->rotate_side(0, 4, 5, 6, 1, 2, 3, 4);
    this->rotate_side(1, 2, 3, 4, 5, 0, 1, 2);
    this->rotate_side(5, 0, 1, 2, 3, 6, 7, 0);

    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (color1 << (8 * 6));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (color2 << (8 * 7));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (color3 << (8 * 0));

    return *this;
  }

  Cube &f_prime() override {
    this->f();
    this->f();
    this->f();
    return *this;
  }

  Cube &f2() override {
    this->f();
    this->f();
    return *this;
  }

  Cube &r() override {
    const int face_index = static_cast<int>(Face::RIGHT);
    this->rotate_face(face_index);
    uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
    uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 3))) >> (8 * 3);
    uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);

    this->rotate_side(0, 2, 3, 4, 2, 2, 3, 4);
    this->rotate_side(2, 2, 3, 4, 5, 2, 3, 4);
    this->rotate_side(5, 2, 3, 4, 4, 7, 6, 0);

    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr1 << (8 * 7));
    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

    return *this;
  }

  Cube &r_prime() override {
    this->r();
    this->r();
    this->r();
    return *this;
  }

  Cube &r2() override {
    this->r();
    this->r();
    return *this;
  }

  Cube &b() override {
    const int face_index = static_cast<int>(Face::BACK);
    rotate_face(face_index);

    uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
    uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
    uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);

    this->rotate_side(0, 0, 1, 2, 3, 2, 3, 4);
    this->rotate_side(3, 2, 3, 4, 5, 4, 5, 6);
    this->rotate_side(5, 4, 5, 6, 1, 6, 7, 0);

    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

    return *this;
  }

  Cube &b_prime() override {
    this->b();
    this->b();
    this->b();
    return *this;
  }

  Cube &b2() override {
    this->b();
    this->b();
    return *this;
  }

  Cube &d() override {
    const int face_index = static_cast<int>(Face::DOWN);
    rotate_face(face_index);

    uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
    uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
    uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

    this->rotate_side(2, 4, 5, 6, 1, 4, 5, 6);
    this->rotate_side(1, 4, 5, 6, 4, 4, 5, 6);
    this->rotate_side(4, 4, 5, 6, 3, 4, 5, 6);

    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));

    return *this;
  }

  Cube &d_prime() override {
    this->d();
    this->d();
    this->d();
    return *this;
  }

  Cube &d2() override {
    this->d();
    this->d();
    return *this;
  }

  bool operator==(const CubeBitboard &other) const {
    for (int i = 0; i < total_faces; i++) {
      if (bitboard[i] != other.bitboard[i]) return false;
    }
    return true;
  }

  CubeBitboard &operator=(const CubeBitboard &other) {
    for (int i = 0; i < total_faces; i++) {
      bitboard[i] = other.bitboard[i];
    }
    return *this;
  }

  std::unique_ptr<Cube> clone() const override {
    return std::make_unique<CubeBitboard>(*this);
  }
};

namespace std {

template <>
struct hash<CubeBitboard> {
  size_t operator()(const CubeBitboard &cube) const noexcept {
    uint64_t final_hash = cube.bitboard[0];
    for (int i = 0; i < Cube::total_faces; i++) {
      final_hash ^= cube.bitboard[i];
    }
    return (size_t)final_hash;
  }
};

}  // namespace std
