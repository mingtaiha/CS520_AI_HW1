#include <iostream>
#include <string>
#include <cstdio>
#include <armadillo>
#include "astar.h"
#include "sim_window.h"
#include "draw.h"
#include "pqueue.h"
#include "maze_gen.h"
#include "mapcheck.h"
#include "searchstate.h"

using namespace std;
using namespace arma;

SDL_Surface *screen;

void run_map(imat map) {
  // select two points, for now the corners
  ivec A = {0, 0};
  ivec B = {100, 100};
  ForwardAStar astar(map, A, B);
  vector<ivec> path, edges;
  icube pathmap;
  drawGrid(pathmap, map);
  while (!astar.complete()) {
    astar.compute();
    astar.decision_space(path, edges);
    drawPath(pathmap, path, edges);
    blitRGB(screen, pathmap);
    sim_window::update();
    SDL_Delay(25);
  }
  // draw the final decision
  astar.final_decision(path, edges);
  drawPath(pathmap, path, edges);
  blitRGB(screen, pathmap);
  sim_window::update();
  SDL_Delay(25);
}

int main() {
  // create maps
  vector<imat> maps;
  for (int i = 0; i < 50; i++) {
    imat maze = maze_gen(101, 101);
    while (!isValidMap(maze, 0, 0, 100, 100)) {
      maze = maze_gen(101, 101);
    }
    maps.push_back(maze);
  }

  // after the maps are created, start the a_star algorithm
  screen = sim_window::init(getGridWidth(101), getGridHeight(101));
  for (imat &map : maps) {
    run_map(map);
    sleep(5);
  }
  sim_window::destroy();

  return 0;
}
