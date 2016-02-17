#ifndef astar_h
#define astar_h

#include <vector>
#include <armadillo>
#include "searchtree.h"

class AStar {
  public:
    AStar(arma::imat map, arma::ivec &start, arma::ivec &goal,
        int forward_mode = true, int heuristic_mode = H_REPEATED);
    ~AStar(void);
    void compute(void);
    void decision_space(std::vector<arma::ivec> &path);
    void final_decision(std::vector<arma::ivec> &path);
    bool complete(void);
    bool impossible(void);

    arma::imat map;
    arma::ivec start;
    arma::ivec goal;

    // stuff for the decision making capability
    searchtree tree;
	  state * fin;
	  bool isComplete;

    // flags
    int heuristic_mode;
};

#endif
