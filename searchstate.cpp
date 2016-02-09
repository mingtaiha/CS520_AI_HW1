#include "searchstate.h"
#include "heuristic.h"
#include <iostream>
#include <vector>
#include <armadillo>
#define TESTING 1 

using namespace std;


state::state(ivec loc, state * parent) {
	x = loc(0);
	y = loc(1);
	this->parent = parent;
}

state::~state() {
}

bool state::operator<(const state &other) {
	return (this->g_value + this->h_value) < (other->g_value + other->h_value);
}

bool state::operator>(const state &other) {
	return (this->g_value + this->h_value) > (other->g_value + other->h_value);
}

bool state::operator<=(const state &other) {
	return (this->g_value + this->h_value) <= (other->g_value + other->h_value);
}

bool state::operator>=(const state &other) {
	return (this->g_value + this->h_value) >= (other->g_value + other->h_value);
}

bool state::operator==(const state &other) {
	return (this->g_value + this->h_value) == (other->g_value + other->h_value);


ostream &operator<<(ostream &out, state &st) {
	out << "[x y] = [" << st.x << " " << st.y << "], [g h] = [" << st.g_value << " " << st.h_value << "]\n";

}






#if TESTING


int main() {

	arma::ivec st(2);
	arma::ivec gl(2);
	arma::ivec a(2);

	st = {10, 0};
	gl = {20, 10};
	a = {0, 0};

	state test(a);
	cout << test;

	test.setG(st);
	test.setH(gl);
	cout << test;

	return 0;

}

#endif
