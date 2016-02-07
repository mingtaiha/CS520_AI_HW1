#include "pqueue.h"
#include <iostream>
#include <vector>

#define hparent(index) (((index)-1)/2)
#define lchild(index) (((index)*2)+1)
#define rchild(index) (((index)*2)+2)
#define TEST_heap_cpp 0

using namespace std;

qcell::qcell(int x, int y, double cost, int parent_id) {
  this->x = x;
  this->y = y;
  this->cost = cost;
  this->parent_id = parent_id;
}

ostream &qcell::operator<<(ostream &out) {
  out << "[x:" << this->x << ", " << this->y << "] = " << this->cost << endl;
}

bool qcell::operator<(const qcell &other) {
  return this->cost < other.cost;
}

bool qcell::operator>(const qcell &other) {
  return this->cost > other.cost;
}

bool qcell::operator<=(const qcell &other) {
  return this->cost <= other.cost;
}

bool qcell::operator>=(const cqell &other) {
  return this->cost >= other.cost;
}

bool qcell::operator==(const qcell &other) {
  return this->cost == other.cost;
}

heap::heap(void) {
  this->n_elem = 0;
}

heap::~heap(void) {
}

void heap::swap(int a, int b) {
  qcell temp = this->queue[a];
  this->queue[a] = this->queue[b];
  this->queue[b] = temp;
}

// max heap
void heap::siftup(void) {
  int index = this->n_elem-1;
  while (index != 0) {
    if (this->queue[index].cost > this->queue[hparent(index)].cost) {
      this->swap(index, hparent(index));
      index = hparent(index);
    } else {
      break;
    }
  }
}

void heap::siftdown(void) {
  if (this->n_elem == 0) {
    return;
  }
  int index = this->n_elem - 1;
  int ptr = 0;
  int end = index - 1;
  this->swap(0, index);
  while (ptr < end) {
    int new_index = lchild(ptr);
    if (new_index == index) {
      break;
    }
    if (rchild(ptr) < index && this->queue[lchild(ptr)] < this->queue[rchild(ptr)]) {
      new_index = rchild(ptr);
    }
    if (new_index < index && this->queue[new_index] > this->queue[ptr]) {
      this->swap(ptr, new_index);
      ptr = new_index;
    } else {
      break;
    }
  }
}

void heap::insert(qcell item) {
  if (this->queue.size() == this->n_elem) {
    this->queue.push_back(item);
  } else {
    this->queue[this->n_elem] = item;
  }
  this->n_elem++;
  this->siftup();
}

qcell heap::remove(void) {
  if (this->n_elem == 0) {
    return { 0, 0, 0 };
  } else {
    qcell c = this->queue[0];
    this->swap(0, --this->n_elem);
    this->siftdown();
    return c;
  }
}

void heap::print(void) {
  cout << "heap contents:" << endl;
  for (qcell &c : this->queue) {
    cout << c << endl;
  }
  cout << "end heap print" << endl;
}

#if TEST_heap_cpp

int main() {
  heap h;
  qcell a(0, 0, 1);
  qcell b(0, 0, 2);
  qcell c(0, 0, 3);
  qcell d(0, 0, 4);
  h.print();
  h.insert(a);
  h.insert(b);
  h.insert(c);
  h.insert(d);
  h.print();
  qcell _a = h.remove();
  qcell _b = h.remove();
  qcell _c = h.remove();
  qcell _d = h.remove();
  cout << _a << ", "
       << _b << ", "
       << _c << ", "
       << _d
       << endl;
  return 0;
}

#endif
