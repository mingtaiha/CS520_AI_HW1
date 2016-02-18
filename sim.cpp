#include <iostream>
#include <string>
#include <cstdio>
#include <signal.h>
#include <armadillo>
#include "astar.h"
#include "sim_window.h"
#include "draw.h"
#include "maze_gen.h"
#include "mapcheck.h"
#include "searchtree.h"
#include "load_maze.h"

#define SIZE 101
#define block_prob 20
#define t_delay 25
using namespace std;
using namespace arma;

void stopprog(int signo) {
  printf("Time ran out, quitting.\n");
  exit(1);
}

SDL_Surface *screen;

ivec getClickedPoint(void) {
  SDL_Event *e;
  for (;;) {
    while ((e = sim_window::get_event())) {
      if (e->type == SDL_QUIT) {
        sim_window::destroy();
        exit(1);
      }
      if (e->type == SDL_MOUSEBUTTONUP) {
        return ivec({ gridx(e->button.x), gridy(screen->h - e->button.y - 1) });
      }
    }
  }
  return ivec({0, 0});
}

void run_map(imat map) {
  // select two points, for now the corners
  icube pathmap;
  vector<ivec> path;
  drawGrid(pathmap, map);
  blitRGB(screen, pathmap);
  sim_window::update();

  bool isSame = 1;
  ivec A;
  ivec B;

  while(isSame) {
    printf("waiting for point 1\n");
    A = getClickedPoint();

    printf("waiting for point 2\n");
    B = getClickedPoint();

    if (A(0) == B(0) && A(1) == B(1)) {
      printf("You clicked on the same point twice. Please pick two different points.\n");
    }
    else {
      isSame = 0;
    }
  }
  //  do {
  //    B = getClickedPoint();
  //  } while (B(0) == A(0) && B(1) == A(1));
  AStar astar(map, A, B, true, H_REPEATED);
  int i_blip = 0;
  while (!astar.complete() && !astar.impossible()) {
    SDL_Event *e;
    while ((e = sim_window::get_event())) {
      if (e->type == SDL_QUIT) {
        sim_window::destroy();
        exit(1);
      }
    }
    astar.compute();
    astar.decision_space(path);
    if (i_blip % 5 == 0) {
      drawPath(pathmap, path);
      blitRGB(screen, pathmap);
      sim_window::update();
      SDL_Delay(t_delay);
    }
    i_blip++;
  }
  if (astar.impossible()) {
    printf("Impossible to find a path!\n");
    return;
  }
  // draw the final decision
  astar.final_decision(path);
  //  drawGrid(pathmap, map);
  //  drawPath(pathmap, path);
  blitRGB(screen, pathmap);
  sim_window::update();
  SDL_Delay(t_delay);
}

int main(int argc, char *argv[]) {
  signal(SIGALRM, stopprog);
  alarm(60);
  //  if (argc < 2) {
  //    printf("input file name\n");
  //    return 1;
  //  }
  // create maps
  vector<imat> maps;
  srand(getpid());
  //  string mazename = string(argv[1]);
  imat maze = maze_gen(SIZE, block_prob);
  maps.push_back(maze);
  //int size = SIZE;
  /*for (int i = 0; i < 1; i++) {
    imat maze = maze_gen(size, block_prob);
  //while (!isValidMap(maze, 0, 0, size-1, size-1)) {
  //maze = maze_gen(size, block_prob);
  //}
  maps.push_back(maze);
  }*/

  // after the maps are created, start the a_star algorithm
  //setLineThickness(0);
  //setBlockSize(1);
  screen = sim_window::init(getGridWidth(maze.n_cols), getGridHeight(maze.n_rows));
  for (imat &map : maps) {
    run_map(map);
    sleep(5);
  }
  sim_window::destroy();

  return 0;
}
