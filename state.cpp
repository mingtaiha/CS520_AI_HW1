#include "state.h"
#include <cstring>
#include "heuristic.h"

using namespace std;
using namespace arma;

state::state(int x, int y, state * parent, imat &map, int heuristic_mode) {
	this->x = x;
	this->y = y;
	g_value = -1;
	h_value = -1;
  f = g_value + h_value;
	this->parent = parent;
  this->map = map;
  memset(&this->children, 0, sizeof(state *) * 4); // reset the children
  hmode = heuristic_mode;
}

state::~state() {
}

void state::setG(int start_x, int start_y) {
	g_value = (this->parent == NULL) ? 0 : this->parent->g_value + 1;
  f = g_value + h_value;
}

void state::setH(int goal_x, int goal_y, int start_x, int start_y) {
  if (hmode == H_REPEATED) {
  	h_value = mdist(this->x, this->y, goal_x, goal_y);
  } else {
    h_value = mdist(start_x, start_y, goal_x, goal_y) -
      ((this->parent == NULL) ? 0 : this->parent->g_value + 1);
  }
  f = g_value + h_value;
}

bool state::operator<(const state &other) {
	return this->f < other.f;
}

bool state::operator>(const state &other) {
	return this->f > other.f;
}

bool state::operator<=(const state &other) {
	return this->f <= other.f;
}

bool state::operator>=(const state &other) {
	return this->f >= other.f;
}

bool state::operator==(const state &other) {
	return this->f == other.f;
}

bool state::operator!=(const state &other) {
	return this->f != other.f;
}

void state::clear(void) {
  for (int i = 0; i < 4; i++) {
    if (this->children[i]) {
      this->children[i]->clear();
      delete this->children[i];
    }
  }
}

ostream &operator<<(ostream &out, state &st) {
	out << "{" << &st << "} [x y] = [" << st.x << " " << st.y << "]\n"
    "\tCOST: [g h] = [" << st.g_value << " " << st.h_value << "]\n"
    "\tPARENT: " << st.parent << "\n"
    "\tOBSTACLE: " << (st.map(st.y, st.x) == 1) << "\n";
}
