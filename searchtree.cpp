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

searchtree::searchtree(int sx, int sy, int gx, int gy, imat &map) {
  init(sx, sy, gx, gy, map);
}

void searchtree::init(int start_x, int start_y, int goal_x, int goal_y, imat &map) {
  this->map = map;
  this->start_x = start_x;
  this->start_y = start_y;
  this->goal_x = goal_x;
  this->goal_y = goal_y;
  visited = zeros<imat>(map.n_rows, map.n_cols);
  queued = zeros<imat>(map.n_rows, map.n_cols);
  // initially set root to NULL
  root = NULL;
  state * temp = new state(start_x, start_y, NULL, map);
  temp->setG(start_x, start_y);
  temp->setH(goal_x, goal_y);
  pqueue.insert(temp);
}

searchtree::~searchtree() {
}

void searchtree::addChildren(state * cur, heap_n &pqueue, imat &visited, imat &queued, imat &map,
    int start_x, int start_y, int goal_x, int goal_y) {

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
    // check if queued already
    if (queued(y_t(i), x_t(i)) == 1) {
      continue;
    }
    // create a new node with cur as the parent
    temp = new state(x_t(i), y_t(i), cur, map);
    temp->setG(start_x, start_y);
    temp->setH(goal_x, goal_y);
    // add to queue
    pqueue.insert(temp);
    queued(y_t(i), x_t(i)) = 1;
  }
}

int childid(int x1, int y1, int x2, int y2) {
  return (((y2 - y1) > 0) << 1) | ((x2 - x1) > 0);
}

void searchtree::addToTree(state * node, imat &visited) {
  visited(node->y, node->x) = 1;
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

  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  heap_n pqueue;
  arma::imat m;
  state *t;
  t = new state(0, 0, NULL, m);
  t->g_value = 6;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 5;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 3;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 1;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 8;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 7;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 2;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  t = new state(0, 0, NULL, m);
  t->g_value = 4;
  t->h_value = 0;
  pqueue.insert(t);
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";


  /// SIFT DOWN ///
  state *s;
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  s = pqueue.remove();
  cout << "removed: " << s->g_value << endl;
  for (int i = 0; i < pqueue.queue.size(); i++) {
    state *s = pqueue.queue[i];
    cout << s->g_value << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  return 0;

}

#endif
