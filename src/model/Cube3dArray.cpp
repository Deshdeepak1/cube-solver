#include "Cube.hpp"

class Cube3dArray : public Cube {
private:
  Color cube[total_faces][total_rows][total_cols]{};

  void rotate_face(const unsigned int face_index) {
    Color temp[3][3]{};
    for (unsigned int j = 0; j < total_rows; j++) {
      for (unsigned int k = 0; k < total_cols; k++) {
        temp[j][k] = cube[face_index][j][k];
      }
    }

    for (unsigned int i = 0; i < 3; i++)
      cube[face_index][0][i] = temp[2 - i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[face_index][i][2] = temp[0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[face_index][2][2 - i] = temp[i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[face_index][2 - i][0] = temp[2][2 - i];
  };

public:
  Cube3dArray() {
    for (unsigned int i = 0; i < total_faces; i++) {
      for (unsigned int j = 0; j < total_rows; j++) {
        for (unsigned int k = 0; k < total_cols; k++) {
          cube[i][j][k] = Color(i);
        }
      }
    }
  }

  Color get_color(Face face, unsigned int row,
                  unsigned int col) const override {
    const unsigned int face_index = static_cast<unsigned int>(face);
    return cube[face_index][row][col];
  }

  bool is_solved() const override {
    for (const auto &f : cube) {
      Color fc = f[1][1];
      for (const auto &r : f) {
        for (const auto &c : r) {
          if (c != fc) {
            return false;
          }
        }
      }
    }
    return true;
  }

  Cube &u() override {
    const unsigned int face_index = static_cast<unsigned int>(Face::UP);
    this->rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[4][0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[4][0][i] = cube[1][0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[1][0][i] = cube[2][0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[2][0][i] = cube[3][0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[3][0][i] = temp[i];

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
    const unsigned int face_index = static_cast<unsigned int>(Face::LEFT);
    this->rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[0][i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[0][i][0] = cube[4][2 - i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[4][2 - i][2] = cube[5][i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[5][i][0] = cube[2][i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[2][i][0] = temp[i];
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
    const unsigned int face_index = static_cast<unsigned int>(Face::FRONT);
    this->rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[0][2][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[0][2][i] = cube[1][2 - i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[1][2 - i][2] = cube[5][0][2 - i];
    for (unsigned int i = 0; i < 3; i++)
      cube[5][0][2 - i] = cube[3][i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[3][i][0] = temp[i];
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
    const unsigned int face_index = static_cast<unsigned int>(Face::RIGHT);
    this->rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[0][i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[0][i][2] = cube[2][i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[2][i][2] = cube[5][i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[5][i][2] = cube[4][2 - i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[4][2 - i][0] = temp[i];
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
    const unsigned int face_index = static_cast<unsigned int>(Face::BACK);
    rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[0][0][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[0][0][i] = cube[3][i][2];
    for (unsigned int i = 0; i < 3; i++)
      cube[3][i][2] = cube[5][2][2 - i];
    for (unsigned int i = 0; i < 3; i++)
      cube[5][2][2 - i] = cube[1][2 - i][0];
    for (unsigned int i = 0; i < 3; i++)
      cube[1][2 - i][0] = temp[i];
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
    const unsigned int face_index = static_cast<unsigned int>(Face::DOWN);
    rotate_face(face_index);

    Color temp[3]{};
    for (unsigned int i = 0; i < 3; i++)
      temp[i] = cube[2][2][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[2][2][i] = cube[1][2][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[1][2][i] = cube[4][2][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[4][2][i] = cube[3][2][i];
    for (unsigned int i = 0; i < 3; i++)
      cube[3][2][i] = temp[i];
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
};
