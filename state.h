#ifndef state_h
#define state_h

#include "heuristic.h"
#include <iostream>
#include <cassert>
#include <armadillo>

class state {

public:
	int x;                          // Current x-coordinates
	int y;                          // Current y-coordinates
	state * parent;                 // Pointer to the parent state
	svec children;                  // Vector of pointers to each child node
	double g_value;                 // Cost of getting to the current state
	double h_value;                 // Estimated cost of getting to the goal
									//      from the current state

	state(int x, int y, state * parent);
	~state();                                                                                                                                                                                         
	void setG(int start_x, int start_y);
	void setH(int goal_x, int goal_y);
	bool operator<(const state &other);
	bool operator>(const state &other);
	bool operator<=(const state &other);
	bool operator>=(const state &other);
	bool operator==(const state &other);
	bool operator!=(const state &other);
};


ostream &operator<<(ostream &out, state &cur_state);


#endif
