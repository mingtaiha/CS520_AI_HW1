#include <iostream>
#include <string>
#include <cstdio>
#include <signal.h>
#include <armadillo>
#include "astar.h"
#include "sim_window.h"
#include "draw.h"
#include "maze_gen.h"
#include "maze_imgio.h"
#include "robot.h"

#define SIZE 101
#define block_prob 0
#define t_delay 500
using namespace std;
using namespace arma;

void stopprog(int signo) {
  printf("Time ran out, quitting.\n");
  exit(1);
}

SDL_Surface *screen;
static bool mouseon;

ivec getClickedPoint(void) {
  SDL_Event *e;
  for (;;) {
    while ((e = sim_window::get_event())) {
      if (e->type == SDL_QUIT) {
        sim_window::destroy();
        exit(1);
      }
      if (e->type == SDL_MOUSEBUTTONDOWN) {
        if (mouseon == false) {
          mouseon = true;
        }
      }
      if (e->type == SDL_MOUSEBUTTONUP) {
        if (mouseon == true) {
          mouseon = false;
          return ivec({ gridx(e->button.x), gridy(screen->h - e->button.y - 1) });
        }
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

  // grab the start and goal positions
  bool isSame = 1;
  ivec start;
  ivec goal;
  while(isSame) {
    printf("Waiting for point 1\n");
    start = getClickedPoint();

    printf("Waiting for point 2\n");
    goal = getClickedPoint();

    if (start(0) == goal(0) && start(1) == goal(1)) {
      printf("You clicked on the same point twice. Please pick two different points.\n");
    }
    else {
      isSame = 0;
    }
  }
  Robot robot(start);
  robot.search(map, start, goal, F_FORWARD, H_ADAPTIVE, G_MAX);
  int i_blip = 0;
  while (!robot.complete() && !robot.stuck()) {
    // search the space to find a path
    while (!robot.searchalgo->complete() && !robot.searchalgo->impossible()) {
      SDL_Event *e;
      while ((e = sim_window::get_event())) {
        if (e->type == SDL_QUIT) {
          sim_window::destroy();
          exit(1);
        }
      }
      robot.run();
      robot.searchalgo->decision_space(path);
      if (i_blip % 1 == 0) {
        drawGrid(pathmap, map);
        drawPath(pathmap, path);
        drawBot(pathmap, robot.x, robot.y);
        blitRGB(screen, pathmap);
        sim_window::update();
        SDL_Delay(t_delay);
      }
      i_blip++;
    }
    if (robot.searchalgo->impossible()) {
      printf("Impossible to find a path!\n");
      return;
    }
    // draw the final decision
    robot.searchalgo->final_decision(path);
    drawGrid(pathmap, map);
    drawPath(pathmap, path);
    drawBot(pathmap, robot.x, robot.y);
    blitRGB(screen, pathmap);
    sim_window::update();
    SDL_Delay(t_delay * 5);

    // move the robot to the new position
    if (path.size() >= 2) {
      robot.move(robot.getMotion());
    }
  }
  drawGrid(pathmap, map);
  drawBot(pathmap, robot.x, robot.y);
  blitRGB(screen, pathmap);
  sim_window::update();
  SDL_Delay(t_delay * 5);
}

int main(int argc, char *argv[]) {
  signal(SIGALRM, stopprog);
  alarm(120);
  // TODO: create argument labels for generating maps and using static maps, as well as options for the simulation
  //  if (argc < 2) {
  //    printf("input file name\n");
  //    return 1;
  //  }
  // create maps
  //vector<imat> maps;
  //srand(getpid());
  //  string mazename = string(argv[1]);
  //imat maze = maze_gen(SIZE, block_prob);
  string mazename = string("maze2.png");
  imat maze = flipud(load_maze(mazename));
  //maps.push_back(maze);
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
  setBlockSize(30);
  screen = sim_window::init(getGridWidth(maze.n_cols), getGridHeight(maze.n_rows));
  //for (imat &map : maps) {
    run_map(maze);
    sleep(1);
  //}
  sim_window::destroy();

  return 0;
}
