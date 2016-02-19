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

static imat map_mdist(int n_rows, int n_cols, ivec start, ivec goal) {
  imat mm(n_rows, n_cols);
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      mm(i, j) = mdist(j, i, goal(0), goal(1));
    }
  }
  return mm;
}

void Robot::search(imat map, ivec &start, ivec &goal,
    int forward_mode, int heuristic_mode, int tie_mode) {
  this->goal = goal;
  this->forward_mode = forward_mode;
  set_cost(map_mdist(map.n_rows, map.n_cols, start, goal));
  if (forward_mode == F_FORWARD) {
    this->searchalgo = new AStar(map, start, goal, F_FORWARD, heuristic_mode, tie_mode);
  } else {
    this->searchalgo = new AStar(map, goal, start, F_FORWARD, heuristic_mode, tie_mode);
  }
  set_adaptive(heuristic_mode);
}

void Robot::run(void) {
  if (!searchalgo->complete() && !searchalgo->impossible()) {
    searchalgo->compute();
  }
}

bool Robot::complete(void) {
  if (!this->searchalgo) {
    return true;
  }
  return this->x == this->goal(0) &&
    this->y == this->goal(1);
}

bool Robot::stuck(void) {
  if (!this->searchalgo) {
    return false;
  }
  return this->searchalgo->impossible();
}

ivec Robot::getMotion(void) {
  vector<ivec> path;
  this->searchalgo->final_decision(path);
  if (this->forward_mode == F_FORWARD) {
    return path[path.size()-2];
  } else {
    return path[1];
  }
}

imat mod_cost(imat cost, imat interim, ivec goal) {
  int goalcost = cost(goal(1), goal(0));
  for (int i = 0; i < (int)cost.n_rows; i++) {
    for (int j = 0; j < (int)cost.n_cols; j++) {
      if (interim(i, j) != -1) {
        cost(i, j) = goalcost - interim(i, j);
      }
    }
  }
  return cost;
}

void Robot::move(ivec newpos) {
  this->x = newpos(0);
  this->y = newpos(1);
  if (this->searchalgo) {
    imat map = this->searchalgo->map;
    ivec start({ this->x, this->y });
    int heuristic_mode = this->searchalgo->heuristic_mode;
    int tie_mode = this->searchalgo->tie_mode;
    delete this->searchalgo;
    // switch up backward and forward
    if (this->forward_mode == F_FORWARD) {
      this->searchalgo = new AStar(map, start, this->goal, this->forward_mode, heuristic_mode, tie_mode);
    } else {
      this->searchalgo = new AStar(map, this->goal, start, this->forward_mode, heuristic_mode, tie_mode);
    }
  }
  set_cost(mod_cost(get_cost(), get_interim(), this->goal));
}
