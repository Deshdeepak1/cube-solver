#include "Cube.hpp"

class Cube1DArray : public Cube {
 private:
  static inline int get_index(int face_index, int row, int col) {
    return (face_index * total_face_squares) + (row * total_cols) + col;
  }

  void rotate_face(const int face_index) {
    Color temp[total_face_squares]{};
    for (int j = 0; j < total_rows; j++) {
      for (int k = 0; k < total_cols; k++) {
        temp[j * total_cols + k] = cube[get_index(face_index, j, k)];
      }
    }

    for (int i = 0; i < 3; i++)
      cube[get_index(face_index, 0, i)] = temp[get_index(0, 2 - i, 0)];
    for (int i = 0; i < 3; i++)
      cube[get_index(face_index, i, 2)] = temp[get_index(0, 0, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(face_index, 2, 2 - i)] = temp[get_index(0, i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(face_index, 2 - i, 0)] = temp[get_index(0, 2, 2 - i)];
  };

 public:
  Color cube[total_squares]{};

  Cube1DArray() {
    for (int i = 0; i < total_faces; i++) {
      for (int j = 0; j < total_rows; j++) {
        for (int k = 0; k < total_cols; k++) {
          cube[get_index(i, j, k)] = Color(i);
        }
      }
    }
  }

  Color get_color(Face face, int row, int col) const override {
    const int face_index = static_cast<int>(face);
    return cube[get_index(face_index, row, col)];
  }

  bool is_solved() const override {
    for (int i = 0; i < total_faces; i++) {
      for (int j = 0; j < total_rows; j++) {
        for (int k = 0; k < total_cols; k++) {
          if (cube[get_index(i, j, k)] != Color(i)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  Cube &u() override {
    const int face_index = static_cast<int>(Face::UP);
    this->rotate_face(face_index);

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(4, 0, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(4, 0, i)] = cube[get_index(1, 0, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(1, 0, i)] = cube[get_index(2, 0, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(2, 0, i)] = cube[get_index(3, 0, i)];
    for (int i = 0; i < 3; i++) cube[get_index(3, 0, i)] = temp[i];

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

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(0, i, 0)];
    for (int i = 0; i < 3; i++)
      cube[get_index(0, i, 0)] = cube[get_index(4, 2 - i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(4, 2 - i, 2)] = cube[get_index(5, i, 0)];
    for (int i = 0; i < 3; i++)
      cube[get_index(5, i, 0)] = cube[get_index(2, i, 0)];
    for (int i = 0; i < 3; i++) cube[get_index(2, i, 0)] = temp[i];
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

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(0, 2, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(0, 2, i)] = cube[get_index(1, 2 - i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(1, 2 - i, 2)] = cube[get_index(5, 0, 2 - i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(5, 0, 2 - i)] = cube[get_index(3, i, 0)];
    for (int i = 0; i < 3; i++) cube[get_index(3, i, 0)] = temp[i];
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

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(0, i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(0, i, 2)] = cube[get_index(2, i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(2, i, 2)] = cube[get_index(5, i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(5, i, 2)] = cube[get_index(4, 2 - i, 0)];
    for (int i = 0; i < 3; i++) cube[get_index(4, 2 - i, 0)] = temp[i];
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

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(0, 0, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(0, 0, i)] = cube[get_index(3, i, 2)];
    for (int i = 0; i < 3; i++)
      cube[get_index(3, i, 2)] = cube[get_index(5, 2, 2 - i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(5, 2, 2 - i)] = cube[get_index(1, 2 - i, 0)];
    for (int i = 0; i < 3; i++) cube[get_index(1, 2 - i, 0)] = temp[i];
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

    Color temp[3]{};
    for (int i = 0; i < 3; i++) temp[i] = cube[get_index(2, 2, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(2, 2, i)] = cube[get_index(1, 2, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(1, 2, i)] = cube[get_index(4, 2, i)];
    for (int i = 0; i < 3; i++)
      cube[get_index(4, 2, i)] = cube[get_index(3, 2, i)];
    for (int i = 0; i < 3; i++) cube[get_index(3, 2, i)] = temp[i];
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

  bool operator==(const Cube1DArray &other) const {
    for (int i = 0; i < other.total_squares; i++) {
      if (cube[i] != other.cube[i]) {
        return false;
      }
    }
    return true;
  }

  Cube1DArray &operator=(const Cube1DArray &other) {
    for (int i = 0; i < other.total_squares; i++) {
      cube[i] = other.cube[i];
    }
    return *this;
  }

  std::unique_ptr<Cube> clone() const override {
    return std::make_unique<Cube1DArray>(*this);
  }
};

namespace std {

template <>
struct hash<Cube1DArray> {
  size_t operator()(const Cube1DArray &cube) const noexcept {
    string str = "";
    for (int i = 0; i < cube.total_squares; i++) {
      str += cube.get_color_char(cube.cube[i]);
    }
    return hash<string>()(str);
  }
};

}  // namespace std
