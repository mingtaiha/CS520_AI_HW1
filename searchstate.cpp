#include "searchstate.h"
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


state::state(ivec loc, state * parent) {
	x = loc(0);
	y = loc(1);
	g_value = -1;
	h_value = -1;
	this->parent = parent;
}

state::~state() {
}

void state::setG(ivec start) {
	g_value = mdist(this->x, this->y, start(0), start(1));
}

void state::setH(ivec goal) {
	h_value = mdist(this->x, this->y, goal(0), goal(1));
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

ostream &operator<<(ostream &out, state &st) {
	out << "[x y] = [" << st.x << " " << st.y << "]\t\t [g h] = [" << st.g_value << " " << st.h_value << "]\n";

}


/// ------------ HEAP -------------- ///


heap::heap() {
	this->n_elem = 0;
}

heap::~heap() {
}

void heap::swap(int a, int b) {
	state * temp = this->queue[a];
	this->queue[a] = this->queue[b];
	this->queue[b] = temp;
}

void heap::siftup() {
	assert(n_elem > 0);
	int index = n_elem - 1;
	while(index >= 0) {
		if (*(queue[index]) < *(queue[hparent(index)])) {
			this->swap(index, hparent(index));
			index = hparent(index);
		} else {
			break;
		}
	}
}

void heap::siftdown() {
	assert(n_elem > 0);
	int index = this->n_elem - 1;
	int ptr = 0;
	int end = index - 1;
	swap(0, index);
	
	int new_index = lchild(index);
	while(ptr < end) {
		if (new_index == index) {
			break;
		}
		if (rchild(index) < index && *(this->queue[rchild(ptr)]) < *(this->queue[lchild(ptr)])){
			new_index = rchild(ptr);
		}
		if (new_index < index && *(this->queue[new_index]) < *(this->queue[ptr])) {
			this->swap(new_index, ptr);
			ptr = new_index;
		} else {
			break;
		}
	}
}

void heap::insert(state * item) {
	this->queue.push_back(item);
	this->n_elem++;
	this->siftup();
}


state * heap::remove() {
	if(this->n_elem == 0) {
		return NULL;
	} else {
		state * s = queue[0];
		this->swap(0, --(this->n_elem) - 1);
		this->siftdown();
		return s;
	}
}

bool heap::isEmpty() {
	if(this->n_elem == 0) {
		return true;
	} else {
		return false;
	}
}


/// ------------ SEARCHTREE -------------- /// 








/// ------------ TESTING -------------- ///


#if TESTING


int main() {

	arma::ivec st(2);
	arma::ivec gl(2);
	arma::ivec a(2);
	arma::ivec b(2);
	arma::ivec c(2);
	arma::ivec d(2);
	arma::ivec e(2);
	arma::ivec f(2);

	st = {10, 0};
	gl = {20, 10};
	a = {0, 0};
	b = {10, 10};
	c = {30, 40};
	d = {10, 15};
	e = {15, 25};
	f = {25, 15};
	

	state test_a(a, NULL);
	state test_b(b, &test_a);
	state test_c(c, &test_b);
	state test_d(d, &test_c);
	state test_e(e, &test_d);
	state test_f(f, &test_e);

	test_a.setG(st);
	test_b.setG(st);
	test_c.setG(st);
	test_d.setG(st);
	test_e.setG(st);
	test_f.setG(st);
	test_a.setH(gl);
	test_b.setH(gl);
	test_c.setH(gl);
	test_d.setH(gl);
	test_e.setH(gl);
	test_f.setH(gl);

	cout << test_a << test_b << test_c << test_d << test_e << test_f;

	heap h;
	h.insert(&test_a);
	h.insert(&test_b);
	h.insert(&test_c);
	h.insert(&test_d);
	h.insert(&test_e);
	h.insert(&test_f);

	cout << *(h.queue[0]) << *(h.queue[1]) << *(h.queue[2]) << *(h.queue[3]) << *(h.queue[4]) << *(h.queue[5]); 
	cout << endl << *(h.remove()); //<< *(h.remove());
	
	return 0;

}

#endif
