#pragma once

#include "Solver.hpp"

template <typename CubeType>
class BFSSolver : public Solver<CubeType> {
private:
  std::unordered_map<CubeType, bool> visited;
  std::unordered_map<CubeType, Cube::Move> cube_move;
  std::vector<Cube::Move> moves;

  CubeType bfs() {
    std::queue<CubeType> q;
    q.push(cube);
    visited[cube] = true;

    while (!q.empty()) {
      CubeType node = q.front();
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
  CubeType cube;

  BFSSolver(CubeType cube) { this->cube = cube; }

  std::vector<Cube::Move> solve() {
    CubeType solved_cube = bfs();
    assert(solved_cube.is_solved());

    CubeType temp_cube = solved_cube;
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
