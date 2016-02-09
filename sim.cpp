#include <iostream>
#include <string>
#include <cstdio>
#include <armadillo>
#include "astar.h"
#include "sim_window.h"
#include "drawgrid.h"
#include "heap.h"

using namespace std;
using namespace arma;

void run_map(imat map) {
  // select two points, for now the corners
  ivec A = {0, 0};
  ivec B = {100, 100};
  ForwardAStar astar(map, A, B);
  vector<ivec> path, edges;
  while (!astar.complete()) {
    astar.compute();
    astar.decision_space(path, edges);
    mat pathmap = blitPath(map, path);
  }
  astar.final_decision(path, edges);
  mat pathmap = blitPath(map, path);
}

int main() {
  // create maps
  vector<imat> maps;
  for (int i = 0; i < 50; i++) {
    imat maze = maze_gen(101, 101);
    while (!isValidMap(maze, 0, 0, 100, 100)) {
      maze = maze_gen(101, 101);
    }
    maps.push_back(maze_gen);
  }

  // after the maps are created, start the a_star algorithm
  for (imat &map : maps) {
    run_map(map);
  }

  return 0;
}
