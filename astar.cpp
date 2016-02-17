#include "astar.h"
#include "searchtree.h"
#include "maze_gen.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
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
AStar::AStar(imat map, ivec &start, ivec &goal, int forward_mode, int heuristic_mode) {
  isComplete = 0;
  tree.init(start(0), start(1), goal(0), goal(1), map, heuristic_mode);
  tree.queued(start(1), start(0)) = 1;
  tree.visited(start(1), start(0)) = 0;
  if (forward_mode) {
    this->start = start;
    this->goal = goal;
  } else {
    this->start = goal;
    this->goal = start;
  }
  this->map = map;
  this->heuristic_mode = heuristic_mode;
}

AStar::~AStar(void) {
}

/** In this function, you are to get the next state off the
 *  priority queue and then traverse to that state,
 *  computing the cost and placing the state that was traversed
 *  into the search space
 */
void AStar::compute(void) {
  assert(!tree.pqueue.isEmpty());
  state * choice;
  svec breaktie;

  // STEP 1: Grab a list of minimum positions from the priority queue
  if (isComplete) {
    return;
  }
  state * s = tree.pqueue.remove();
  breaktie.push_back(s);
  while (!tree.pqueue.isEmpty()) {
    s = tree.pqueue.remove();
    if ((*s) != (*breaktie[0])) {
      tree.pqueue.insert(s);
      break;
    }
    breaktie.push_back(s);
  }

  // STEP 2: Use random tie breaking to choose a position from the queue,
  //         and place the rest back into the queue
  struct {
    int gx;
    int gy;
    bool operator()(state *a, state *b) {
      return a->g_value < b->g_value; // get the min value
    }
  } compareStates;
  compareStates.gx = goal(0);
  compareStates.gy = goal(1);
  sort(breaktie.begin(), breaktie.end(), compareStates);
  choice = breaktie[0];
  for (int i = 1; i < breaktie.size(); i++) {
    tree.pqueue.insert(breaktie[i]);
  }
  breaktie.clear(); // clear the vector for later usage

  // STEP 3: Detect if the current node is the goal node;
  //         if it is, RETURN (do not do anything)

  if (choice->x == tree.goal_x && choice->y == tree.goal_y) {
    isComplete = 1;
    fin = choice;
  } else {
    // STEP 4: Compute the cost of the 4-connected neighborhood and
    //         add them to the priority queue if they have not been
    //         added before
    tree.addToTree(choice, tree.visited);
    tree.addChildren(choice, tree.pqueue, tree.visited, tree.queued, tree.map,
        tree.start_x, tree.start_y, tree.goal_x, tree.goal_y, heuristic_mode);
    isComplete = 0;
  }	
}

/** Grab the entire tree of nodes from the search space
 *  @param path a vector of (x, y) tuples
 */

void AStar::decision_space(vector<ivec> &path) {
  path.clear();

  for (int i = 0; i < map.n_rows; i++) {
    for (int j = 0; j < map.n_cols; j++) {
      if (tree.visited(i, j) == 1) {
        path.push_back({j, i});
      }
    }
  }
}

/** Grab the final path of nodes from the search space
 *  to the goal
 *  @param path a vector of (x, y) tuples
 */
void AStar::final_decision(vector<ivec> &path) {
  path.clear();
  state * step = fin;
  int i = 0;
  path.push_back({step->x, step->y});
  step = step->parent;

  while(step != NULL) {
    path.push_back({step->x, step->y});
    step = step->parent;
  }	
}

/** Return whether or not the goal is impossible to reach
 *  @return true if it is impossible, false otherwise
 */
bool AStar::impossible(void) {
  return !isComplete && tree.pqueue.isEmpty();
}

/** Return whether or not the goal has been reached
 *  @return true if goal is reached, false otherwise
 */
bool AStar::complete(void) {
  return isComplete;
}

#if TESTING

int main() {

  return 0;
}

#endif
