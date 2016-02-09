#ifndef astar_h
#define astar_h

#include <vector>
#include <armadillo>
#include "pqueue.h"

class ForwardAStar {
  public:
    ForwardAStar(arma::imat map, arma::ivec &start, arma::ivec &goal);
    ~ForwardAStar(void);
    void compute(void);
    void decision_space(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);
    void final_decision(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);
    bool complete(void);

    arma::imat map;
    arma::ivec start;
    arma::ivec goal;

    // stuff for the decision making capability
    heap priority_queue;
};

#endif
