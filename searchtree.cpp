#include "searchtree.h"
#include "heuristic.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <armadillo>

#define hparent(index) (((index)-1)/2)
#define lchild(index)  (((index)*2)+1)
#define rchild(index)  (((index)*2)+2)

#define TESTING 0

using namespace std;

/// ------------ HEAP -------------- ///

heap_n::heap_n() {
}

heap_n::~heap_n() {
}

void heap_n::swap(int a, int b) {
  state * temp = this->queue[a];
  this->queue[a] = this->queue[b];
  this->queue[b] = temp;
}

void heap_n::siftup() {
  assert(this->queue.size() > 0);
  int index = this->queue.size() - 1;
  while(index != 0) {
    if (*(queue[index]) < *(queue[hparent(index)])) {
      this->swap(index, hparent(index));
      index = hparent(index);
    } else {
      break;
    }
  }
}

void heap_n::siftdown() {
  int index = this->queue.size() - 1;
  int ptr = 0;

  int swap_target = lchild(ptr);
  while (swap_target <= index) {
    if (rchild(ptr) <= index && *(this->queue[rchild(ptr)]) < *(this->queue[lchild(ptr)])) {
      swap_target = rchild(ptr);
    }
    if (*(this->queue[swap_target]) < *(this->queue[ptr])) {
      this->swap(swap_target, ptr);
      ptr = swap_target;
      swap_target = lchild(ptr);
    } else {
      break;
    }
  }
}

void heap_n::insert(state * item) {
  this->queue.push_back(item);
  this->siftup();
}


state * heap_n::remove() {
  if (this->queue.size() == 0) {
    return NULL;
  } else {
    state * s = this->queue[0];
    this->swap(0, this->queue.size()-1);
    this->queue.pop_back();
    this->siftdown();
    return s;
  }
}

bool heap_n::isEmpty() {
  return this->queue.size() == 0;
}

/// ------------ SEARCHTREE -------------- /// 

searchtree::searchtree() {
}

searchtree::searchtree(int sx, int sy, int gx, int gy, imat &map, int hmode) {
  init(sx, sy, gx, gy, map, hmode);
}

void searchtree::init(int start_x, int start_y, int goal_x, int goal_y, imat &map, int hmode) {
  this->map = map;
  this->start_x = start_x;
  this->start_y = start_y;
  this->goal_x = goal_x;
  this->goal_y = goal_y;
  opened = zeros<imat>(map.n_rows, map.n_cols);
  closed = zeros<imat>(map.n_rows, map.n_cols);
  // initially set root to NULL
  root = NULL;
  state * temp = new state(start_x, start_y, NULL, map, hmode);
  temp->setG(start_x, start_y);
  temp->setH(goal_x, goal_y, start_x, start_y);
  pqueue.insert(temp);
  this->opened(start_y, start_x) = 1;
}

searchtree::~searchtree() {
  // delete all open nodes
  for (state * s : pqueue.queue) {
    delete s;
  }
  pqueue.queue.clear();
  // delete all closed nodes
  if (root) {
    root->clear();
    delete root;
    root = NULL;
  }
}

void searchtree::addChildren(state * cur, int hmode) {

  state * temp;
  int x_s = cur->x;
  int y_s = cur->y;

  // get all the neighbors of the current cell
  ivec x_t = {x_s - 1, x_s, x_s + 1, x_s};
  ivec y_t = {y_s, y_s + 1, y_s, y_s - 1};

  for (int i = 0; i < 4; i++) {
    // check the bounds
    if (x_t(i) < 0 || x_t(i) >= (int)map.n_cols || y_t(i) < 0 || y_t(i) >= (int)map.n_rows) {
      continue;
    }
    // check if it was an obstacle
    if (map(y_t(i), x_t(i)) == 1) {
      continue;
    }
    // check if opened already
    if (opened(y_t(i), x_t(i)) == 1) {
      continue;
    }
    // create a new node with cur as the parent
    temp = new state(x_t(i), y_t(i), cur, map, hmode);
    temp->setG(start_x, start_y);
    temp->setH(goal_x, goal_y, start_x, start_y);
    // add to queue
    pqueue.insert(temp);
    opened(y_t(i), x_t(i)) = 1;
  }
}

int childid(int x1, int y1, int x2, int y2) {
  return (((y2 - y1) > 0) << 1) | ((x2 - x1) > 0);
}

void searchtree::addToTree(state * node) {
  closed(node->y, node->x) = 1;
  if (node->parent == NULL) {
    this->root = node;
  } else {
    // add to the tree
    node->parent->children[childid(node->x, node->y, node->parent->x, node->parent->y)] = node;
  }
}

/// ------------ TESTING -------------- ///


#if TESTING


int main() {
  return 0;
}

#endif
