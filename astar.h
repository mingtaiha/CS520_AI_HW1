#ifndef astar_h
#define astar_h

#include <vector>
#include <armadillo>

class AStar {
  public:
    AStar(arma::mat map, arma::ivec start, arma::ivec goal);
    ~AStar(void);
    void compute(void);
    void decision_space(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);
    void final_decision(std::vector<arma::ivec> &path, std::vector<arma::ivec> &edges);

    arma::ivec start;
    arma::ivec goal;

    // stuff for the decision making capability
    heap priority_queue;
};

#endif
