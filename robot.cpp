#include "robot.h"

robot::robot(ivec pos) {
  assert(pos.n_elem == 2);
  this->x = pos(0);
  this->y = pos(1);
  this->searchalgo = nullptr;
}

robot::~robot(void) {
}

void robot::search(arma::imat map, arma::ivec &start, arma::ivec &goal,
    int forward_mode, int heuristic_mode, int tie_mode){
  this->searchalgo = algo;
}

void robot::run(void) {
}

void robot::complete(void) {
}
