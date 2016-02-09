#ifndef searchstate_h
#define searchstate_h

#include "heuristic.h"
#include <iostream>
#include <vector>
#include <new>
#include <armadillo>


using namespace std;
using namespace arma;


class state {

	public:
	
		int x;							// Current x-coordinates
		int y;							// Current y-coordinates
		state * parent;					// Pointer to the parent state
		vector<state *> children;		// Vector of pointers to each child node
		double g_value;					// Cost of getting to the current state
		double h_value;					// Estimated cost of getting to the goal
										//		from the current state

		state(ivec loc, state * parent);
		~state();
		bool operator<(const state &other);
		bool operator>(const state &other);
		bool operator<=(const state &other);
		bool operator>=(const state &other);
		bool operator==(const state &other);

};


ostream &operator<<(ostream &out, state &cur_state);


class heaptree {

	public:

		
};



class searchtree {

	public:

		searchtree(ivec start, ivec goal, mat map);
		~searchtree();
		void addChild(state child);
		void setG(ivec start);
		void setH(ivec goal);


		mat map;
		ivec start;
		ivec end;
		state root

};

#endif
