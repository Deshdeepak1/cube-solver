#pragma once

#include "../model/Cube.hpp"
#include <algorithm>
#include <cassert>

template <typename T>
class BFSSolver {
private:
  std::unordered_map<T, bool> visited;
  std::unordered_map<T, Cube::Move> cube_move;
  std::vector<Cube::Move> moves;

  T bfs() {
    std::queue<T> q;
    q.push(cube);
    visited[cube] = true;

    while (!q.empty()) {
      T node = q.front();
      q.pop();
      if (node.is_solved()) {
        return node;
      }

      for (unsigned int i = 0; i < Cube::total_moves; i++) {
        Cube::Move move = Cube::Move(i);
        node.move(move);
        if (!visited[node]) {
          q.push(node);
          visited[node] = true;
          cube_move[node] = move;
        }
        node.invert(move);
      }
    }

    return cube;
  }

public:
  T cube;

  BFSSolver(T cube) { this->cube = cube; }

  std::vector<Cube::Move> solve() {
    T solved_cube = bfs();
    assert(solved_cube.is_solved());

    T temp_cube = solved_cube;
    while (!(temp_cube == cube)) {
      Cube::Move move = cube_move[temp_cube];
      moves.push_back(move);
      temp_cube.invert(move);
    }

    cube = solved_cube;
    reverse(moves.begin(), moves.end());

    return moves;
  }
};
