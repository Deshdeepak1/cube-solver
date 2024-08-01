#include "CornerDBMaker.hpp"

#include "../model/CubeBitboard.cpp"

CornerDBMaker::CornerDBMaker(std::string file_name) : file_name(file_name){};

CornerDBMaker::CornerDBMaker(std::string file_name, uint8_t init_val)
    : file_name(file_name), corner_db(init_val){};

bool CornerDBMaker::bfs_and_store() {
  CubeBitboard cube;

  std::queue<CubeBitboard> q;
  q.push(cube);

  corner_db.set_num_moves(cube, 0);
  int curr_depth = 0;

  while (!q.empty()) {
    int n = q.size();
    curr_depth++;
    if (curr_depth == 9) break;
    for (int counter = 0; counter < n; counter++) {
      CubeBitboard neighbour = q.front();
      q.pop();

      for (int i = 0; i < Cube::total_moves; i++) {
        Cube::Move move = Cube::Move(i);
        neighbour.move(move);
        if ((int)corner_db.get_num_moves(neighbour) > curr_depth) {
          corner_db.set_num_moves(neighbour, curr_depth);
          q.push(neighbour);
        }
        neighbour.invert(move);
      }
    }
  }

  corner_db.to_file(file_name);
  return true;
}
