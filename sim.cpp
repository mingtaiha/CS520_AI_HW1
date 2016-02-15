#include <iostream>
#include <string>
#include <cstdio>
#include <armadillo>
#include "astar.h"
#include "sim_window.h"
#include "draw.h"
#include "maze_gen.h"
#include "mapcheck.h"
#include "searchtree.h"

#define SIZE 101
#define block_prob 30
#define t_delay 25
using namespace std;
using namespace arma;

SDL_Surface *screen;

void run_map(imat map) {
  // select two points, for now the corners
  ivec A = {0, 0};
  ivec B = {size-1, size-1};
  ForwardAStar astar(map, A, B);
  vector<ivec> path, edges;
  icube pathmap;
  drawGrid(pathmap, map);
  int i_blip = 0;
  while (!astar.complete()) {
    SDL_Event *e;
    while ((e = sim_window::get_event())) {
      if (e->type == SDL_QUIT) {
        sim_window::destroy();
        exit(1);
      }
    }
    astar.compute();
    astar.decision_space(path, edges);
    if (i_blip % 10 == 0) {
      drawPath(pathmap, path, edges);
      blitRGB(screen, pathmap);
      sim_window::update();
      SDL_Delay(t_delay);
    }
    i_blip++;
  }
  // draw the final decision
  astar.final_decision(path, edges);
  drawGrid(pathmap, map);
  drawPath(pathmap, path, edges);
  blitRGB(screen, pathmap);
  sim_window::update();
  SDL_Delay(t_delay);
}

int main() {
  // create maps
  vector<imat> maps;
  srand(getpid());
  int size = SIZE;
  /*for (int i = 0; i < 50; i++) {
    imat maze = maze_gen(size, block_prob);
    while (!isValidMap(maze, 0, 0, size-1, size-1)) {
      maze = maze_gen(size, block_prob);
    }
    maps.push_back(maze);
  }*/

  // after the maps are created, start the a_star algorithm
  screen = sim_window::init(getGridWidth(size), getGridHeight(size));
  for (imat &map : maps) {
    run_map(map);
    sleep(5);
  }
  sim_window::destroy();

  return 0;
}
