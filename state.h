#ifndef state_h
#define state_h

#include <iostream>
#include <armadillo>

#define H_REPEATED 0
#define H_ADAPTIVE 1

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
    int hmode;

		state(int x, int y, state * parent, arma::imat &map, int heuristic_mode = H_REPEATED);
		~state();
		void setG(int start_x, int start_y);
		void setH(int goal_x, int goal_y, int start_x = 0, int start_y = 0);
    double f; // f_value
		bool operator<(const state &other);
		bool operator>(const state &other);
		bool operator<=(const state &other);
		bool operator>=(const state &other);
		bool operator==(const state &other);
		bool operator!=(const state &other);
    void clear(void);
};

std::ostream &operator<<(std::ostream &out, state &cur_state);

#endif
