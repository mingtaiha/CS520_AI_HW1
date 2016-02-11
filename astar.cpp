#include "astar.h"
#include "searchstate.h"
#include "maze_gen.h"
#include <algorithm>
#include <iostream>
#include <new>
#include <vector>
#include <armadillo>

using namespace arma;
using namespace std;

#define TESTING 0

/** The goal of this function is to initialize the AStar algorithm,
 *  including any data structures which you are to use in the
 *  computation of the next state
 *  @param map This is the map which you are given
 *  @param start This is the starting position of the robot
 *  @param goal This is the goal of the robot
 */
ForwardAStar::ForwardAStar(imat map, ivec &start, ivec &goal) {
	isComplete = 0;
	tree.map = map;
	tree.start_x = start(0);
	tree.start_y = start(1);
	tree.goal_x = goal(0);
	tree.goal_y = goal(1);
	tree.queued(start(0), start(1)) = 1;
	tree.visited(start(0), start(1)) = 1;
	this->start = start;
	this->goal = goal;
	this->map = map;
}

ForwardAStar::~ForwardAStar(void) {
}

/** In this function, you are to get the next state off the
 *  priority queue and then traverse to that state,
 *  computing the cost and placing the state that was traversed
 *  into the search space
 */
void ForwardAStar::compute(void) {
  // TODO: YOUR CODE GOES HERE
  // STEP 1: Grab a list of minimum positions from the priority queue
  // STEP 2: Use random tie breaking to choose a position from the queue,
  //         and place the rest back into the queue
  // STEP 3: Detect if the current node is the goal node;
  //         if it is, RETURN (do not do anything)
  // STEP 4: Compute the cost of the 4-connected neighborhood and
  //         add them to the priority queue if they have not been
  //         added before
  // STEP 5: set the added flag of the neighbors to true

	state * choice;
	vector<state *> breaktie;
	
	breaktie.push_back(tree.pqueue.remove());
	while (!tree.pqueue.isEmpty()) {
		state *s = tree.pqueue.remove();
		if ((*s) != (*breaktie[0])) {
			tree.pqueue.insert(s);
			break;
		}
	}
	struct {
		bool operator()(state *a, state *b) {
			return a->g_value > b->g_value;
		}
	} compareStates;
	std::sort(breaktie.begin(), breaktie.end(), compareStates);
	choice = breaktie[0];
	for (int i = 1; i < breaktie.size(); i++) {
		tree.pqueue.insert(breaktie[i]);
	}
	breaktie.clear(); // clear the vector for later usage


/*	
	if(tree.pqueue.isEmpty()) {
		return breaktie[0];
	}

	breaktie.push_back(tree.pqueue.remove());

	if (*(breaktie[0]) < *(breaktie[1])) {
		isDifferent = 1;
		reinsert = breaktie[1];
		tree.pqueue.insert(reinsert);
		breaktie.pop_back();
	} else {
		while(!(isDifferent || tree.pqueue.isEmpty())) {
			breaktie.push_back(tree.pqueue.remove());
			if (*(breaktie[0]) < *(breaktie[i])) {
				isDifferent = 1;
				reinsert = breaktie[i];
				tree.pqueue.insert(reinsert);
				breaktie.pop_back();
			} else {
				i++;
			}
		}
		for (int j = 0; j <= i; j++) {
			if (breaktie[i]->g_value < breaktie[index]->g_value) {
				index = 1;
			} else {
			}
		}

		choice = breaktie[index];
		state * temp = breaktie[0];
		breaktie[0] = breaktie[index];
		breaktie[index] = temp;

		while (i > 0) {
			reinsert = breaktie[i];
			tree.pqueue.insert(reinsert);
			breaktie.pop_back();
			i--;
		}
*/
	if (choice->x == tree.start_x && choice->y == tree.start_y) {
		isComplete = 1;
	} else {
		tree.addChildren(choice, tree.pqueue, tree.visited, tree.queued, tree.map,
						tree.start_x, tree.start_y, tree.goal_x, tree.goal_y);
		tree.addToTree(choice, tree.visited);
		isComplete = 0;
	}
}



/*
state * ForwardAStar::AStar(state * root, searchtree tree) {

    if (tree.start_x == tree.goal_x && tree.start_y == tree.goal_y) {					// Checking if the start and goal are the same
		return tree.root;															// If so, just return the root
	}
	else {
		tree.addToTree(root, tree.visited);
		tree.addChildren(root, tree.pqueue, tree.visited, tree.queued, tree.map,	// If not, then add the children of the heap. This function
							tree.start_x, tree.start_y, tree.goal_x, tree.goal_y);  //      (should) check if the neighbors are in the map
	}
	
	state * ptr =  root;															// Initializing a pointer for the tree growth to the root node
	while (!((ptr->x == tree.goal_x) && (ptr->y == tree.goal_y))) {					// While loop is valid when the (x,y) of the ptr and the goal
																					//		is NOT the same
		if (tree.pqueue.isEmpty()) {												// Checks if the heap is empty
			cout << "No path from start to goal...\n" << endl;
			return new state(-1, -1, NULL);											// Returns a default null state
		}
		ptr = compute(tree);														// Otherwise, a new pointer to a state will be returned after
																					//		computing the path once and advancing one state
	}
	return ptr;																		// Return the goal state, which is connect via parents to
																					// 		the start state
}
*/



/** Grab the entire tree of nodes and edges from the search space
 *  @param path a vector of (x, y) tuples
 *  @param edges a vector of (edgeindex1, edgeindex2) tuples, where
 *         each edgeindex is an index of path
 */

void ForwardAStar::decision_space(vector<ivec> &path, vector<ivec> &edges) {
  // TODO: YOUR CODE GOES HERE
  	
	int len = size(map, 1);

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (tree.queued(i, j) == 1) {
				if (tree.visited(i, j) == 1) {
					path.push_back({i, j});
				} else {
					edges.push_back({i, j});
				}
			}
		}
	}
}

/** Grab the final path of nodes and edges from the search space
 *  to the goal
 *  @param path a vector of (x, y) tuples
 *  @param edges a vector of (edgeindex1, edgeindex2) tuples, where
 *         each edgeindex is an index of path
 */
void ForwardAStar::final_decision(vector<ivec> &path, vector<ivec> &edges) {
  // TODO: YOUR CODE GOES HERE

	state * step = fin;

	while(step != NULL) {
		path.push_back({step->x, step->y});
		
		int nchild = step->children.size();
		for (int i = 0; i < nchild; i++) {
			edges.push_back({step->children[i]->x, step->children[i]->y});
		}
		step = step->parent;
	}	
}


/** Return whether or not the goal has been reached
 *  @return true if goal is reached, false otherwise
 */
bool ForwardAStar::complete(void) {
  // TODO: YOUR CODE GOES HERE
  return isComplete;
}


#if TESTING

int main() {

	return 0;

}

#endif
