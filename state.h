#ifndef state_h
#define state_h

#include <iostream>
#include <armadillo>

class state {

	public:
	
		int x;							// Current x-coordinates
		int y;							// Current y-coordinates
		state * parent;					// Pointer to the parent state
		state * children[4];		// Vector of pointers to each child node
		double g_value;					// Cost of getting to the current state
		double h_value;					// Estimated cost of getting to the goal
										//		from the current state
    arma::imat map;

		state(int x, int y, state * parent, arma::imat &map);
		~state();
		void setG(int start_x, int start_y);
		void setH(int goal_x, int goal_y);
    double f;
		bool operator<(const state &other);
		bool operator>(const state &other);
		bool operator<=(const state &other);
		bool operator>=(const state &other);
		bool operator==(const state &other);
		bool operator!=(const state &other);
};

std::ostream &operator<<(std::ostream &out, state &cur_state);

#endif
