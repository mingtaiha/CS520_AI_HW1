	#ifndef astar_h
#define astar_h

#include <vector>
#include <armadillo>
#include "svec.h"
#include "state.h"
#include "searchstate.h"

class ForwardAStar {
  public:
    ForwardAStar(arma::imat map, arma::ivec &start, arma::ivec &goal);
    ~ForwardAStar(void);
    void compute(void);
	state * AStar(state * root, searchtree tree);
    void decision_space(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);
    void final_decision(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);
    bool complete(void);

    arma::imat map;
    arma::ivec start;
    arma::ivec goal;

    // stuff for the decision making capability
    searchtree tree;
	state * fin;
	bool isComplete;
};

#endif
