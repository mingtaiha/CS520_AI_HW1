#include "heuristic.h"
#include <iostream>
#include <cassert>
#include <armadillo>

#define hparent(index) (((index)-1)/2)
#define lchild(index)  (((index)*2)+1)
#define rchild(index)  (((index)*2)+2)

#define TESTING 0 

using namespace std;


state::state(int x, int y, state * parent) {
	this->x = x;
	this->y = y;
	g_value = -1;
	h_value = -1;
	this->parent = parent;
}

state::~state() {
} 


using namespace std;


state::state(int x, int y, state * parent) {
	this->x = x;
	this->y = y;
	g_value = -1;
	h_value = -1;
	this->parent = parent;
}

state::~state() {
}

void state::setG(int start_x, int start_y) {
	g_value = mdist(this->x, this->y, start_x, start_y);    
	//  g_value = 1 + ((this->parent == NULL) ? 0 : this->parent->g_value);
}

void state::setH(int goal_x, int goal_y) {
	h_value = mdist(this->x, this->y, goal_x, goal_y);
}

bool state::operator<(const state &other) {
	return (this->g_value + this->h_value) < (other.g_value + other.h_value);
}

bool state::operator>(const state &other) {
	return (this->g_value + this->h_value) > (other.g_value + other.h_value);
}

bool state::operator<=(const state &other) {
	return (this->g_value + this->h_value) <= (other.g_value + other.h_value);
}

bool state::operator>=(const state &other) {
	return (this->g_value + this->h_value) >= (other.g_value + other.h_value);
}

bool state::operator==(const state &other) {
	return (this->g_value + this->h_value) == (other.g_value + other.h_value);
}

bool state::operator!=(const state &other) {
	return (this->g_value + this->h_value) != (other.g_value + other.h_value);
}

ostream &operator<<(ostream &out, state &st) {
	out << "[x y] = [" << st.x << " " << st.y << "]\t\t \n\tCOST: [g h] = [" << st.g_value << " " << st.h_value << "]\n\tPARENT: " << st.parent << "\n";

}

