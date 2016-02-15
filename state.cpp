#include "state.h"
#include <cstring>
#include "heuristic.h"

using namespace std;
using namespace arma;

state::state(int x, int y, state * parent, imat &map) {
	this->x = x;
	this->y = y;
	g_value = -1;
	h_value = -1;
  f = g_value + h_value;
	this->parent = parent;
  this->map = map;
  memset(&this->children, 0, sizeof(state *) * 4); // reset the children
}

state::~state() {
}

void state::setG(int start_x, int start_y) {
	g_value = (this->parent == NULL) ? 0 : this->parent->g_value + 1;
  f = g_value + h_value;
}

void state::setH(int goal_x, int goal_y) {
	h_value = mdist(this->x, this->y, goal_x, goal_y);
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

ostream &operator<<(ostream &out, state &st) {
	out << "{" << &st << "} [x y] = [" << st.x << " " << st.y << "]\n"
    "\tCOST: [g h] = [" << st.g_value << " " << st.h_value << "]\n"
    "\tPARENT: " << st.parent << "\n"
    "\tOBSTACLE: " << (st.map(st.y, st.x) == 1) << "\n";
}
