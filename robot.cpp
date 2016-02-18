#include "robot.h"
#include <cassert>

Robot::Robot(ivec pos) {
  assert(pos.n_elem == 2);
  this->x = pos(0);
  this->y = pos(1);
  this->searchalgo = NULL;
}

Robot::~Robot(void) {
  if (this->searchalgo) {
    delete this->searchalgo;
    this->searchalgo = NULL;
  }
}

void Robot::search(arma::imat map, arma::ivec &start, arma::ivec &goal,
    int forward_mode, int heuristic_mode, int tie_mode) {
  this->searchalgo = new AStar(map, start, goal, forward_mode, heuristic_mode, tie_mode);
}

void Robot::run(void) {
  while (!searchalgo->complete() && !searchalgo->impossible()) {
    searchalgo->compute();
  }
  vector<ivec> path;
  searchalgo->final_decision(path); // backtrack
}

bool Robot::complete(void) {
  if (!this->searchalgo) {
    return true;
  }
  return this->x == this->searchalgo->goal(0) &&
         this->y == this->searchalgo->goal(1);
}

bool Robot::stuck(void) {
  if (!this->searchalgo) {
    return false;
  }
  return this->searchalgo->impossible();
}

void Robot::move(ivec newpos) {
  this->x = newpos(0);
  this->y = newpos(1);
  if (this->searchalgo) {
    this->searchalgo->tree.pqueue.queue.clear();
    this->searchalgo->opened.zeros();
    this->searchalgo->closed.zeros();
    /*imat map = this->searchalgo->map;
    ivec start({ this->x, this->y });
    ivec goal = this->searchalgo->goal;
    int forward_mode = this->searchalgo->forward_mode;
    int heuristic_mode = this->searchalgo->heuristic_mode;
    int tie_mode = this->searchalgo->tie_mode;
    delete this->searchalgo;
    this->searchalgo = new AStar(map, start, goal, forward_mode, heuristic_mode, tie_mode);*/
  }
}
