#pragma once

#include "../model/Cube.hpp"
#include "../pattern_databases/CornerPatternDatabase.hpp"
#include "Solver.hpp"

template <typename CubeType>
class IDAStarSolver : public Solver<CubeType> {
 private:
  CornerPatternDatabase corner_db;
  std::vector<Cube::Move> moves;
  std::unordered_map<CubeType, bool> visited;
  std::unordered_map<CubeType, Cube::Move> cube_move;

  struct Node {
    CubeType cube;
    int depth;
    int estimate;

    Node(CubeType cube, int depth, int estimate)
        : cube(cube), depth(depth), estimate(estimate){};
  };

  struct compare_cube {
    bool operator()(const std::pair<Node, int> &p1,
                    const std::pair<Node, int> &p2) {
      const Node &n1 = p1.first, &n2 = p2.first;
      if (n1.depth + n1.estimate == n2.depth + n2.estimate) {
        return n1.estimate > n2.estimate;
      } else
        return n1.depth + n1.estimate > n2.depth + n2.estimate;
    }
  };

  void reset() {
    moves.clear();
    visited.clear();
    cube_move.clear();
  }

  std::pair<CubeType, int> IDAStar(int max_bound) {
    std::priority_queue<std::pair<Node, int>, std::vector<std::pair<Node, int>>,
                        compare_cube>
      pq;

    Node start = Node(cube, 0, corner_db.get_num_moves(cube));
    pq.push(std::make_pair(start, 0));

    int next_bound = 100;

    while (!pq.empty()) {
      auto p = pq.top();
      pq.pop();

      Node node = p.first;

      if (visited[node.cube]) continue;

      visited[node.cube] = true;

      cube_move[node.cube] = Cube::Move(p.second);

      if (node.cube.is_solved()) {
        return std::make_pair(node.cube, max_bound);
      }

      node.depth++;

      for (int i = 0; i < Cube::total_moves; i++) {
        Cube::Move move = Cube::Move(i);
        node.cube.move(move);
        if (!visited[node.cube]) {
          node.estimate = corner_db.get_num_moves(node.cube);
          if (node.depth + node.estimate > max_bound) {
            next_bound = std::min(next_bound, node.estimate + node.depth);
          } else {
            pq.push(std::make_pair(node, i));
          }
        }
        node.cube.invert(move);
      }
    }

    return std::make_pair(cube, next_bound);
  }

 public:
  CubeType cube;

  IDAStarSolver(CubeType cube, std::string file_name) {
    this->cube = cube;
    corner_db.from_file(file_name);
  }

  std::vector<Cube::Move> solve() {
    int max_bound = 1;
    std::pair<CubeType, int> p;
    while (true) {
      p = IDAStar(max_bound);
      if (p.second == max_bound) {
        break;
      }
      reset();
      max_bound = p.second;
    }

    CubeType solved_cube = p.first;
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
