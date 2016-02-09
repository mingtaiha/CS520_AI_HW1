#include "astar.h"

using namespace arma;

/** The goal of this function is to initialize the AStar algorithm,
 *  including any data structures which you are to use in the
 *  computation of the next state
 *  @param map This is the map which you are given
 *  @param start This is the starting position of the robot
 *  @param goal This is the goal of the robot
 */
ForwardAStar::ForwardAStar(mat &map, ivec start, ivec goal) {
  // TODO: YOUR CODE GOES HERE
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
}

/** Grab the entire tree of nodes and edges from the search space
 *  @param path a vector of (x, y) tuples
 *  @param edges a vector of (edgeindex1, edgeindex2) tuples, where
 *         each edgeindex is an index of path
 */
void ForwardAStar::decision_space(vector<ivec> &path, vector<ivec> &edges) {
  // TODO: YOUR CODE GOES HERE
}

/** Grab the final path of nodes and edges from the search space
 *  to the goal
 *  @param path a vector of (x, y) tuples
 *  @param edges a vector of (edgeindex1, edgeindex2) tuples, where
 *         each edgeindex is an index of path
 */
void ForwardAStar::final_decision(vector<ivec> &path, vector<ivec> &edges) {
  // TODO: YOUR CODE GOES HERE
}

/** Return whether or not the goal has been reached
 *  @return true if goal is reached, false otherwise
 */
bool ForwardAStar::complete(void) {
  // TODO: YOUR CODE GOES HERE
}
