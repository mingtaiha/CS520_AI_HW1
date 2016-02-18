#ifndef robot_h
#define robot_h

#include "astar.h"

class robot {
  public:
    robot(arma::ivec pos);
    ~robot(void);
    void initSearch(AStar *algo);
    void run(void);
    bool complete(void);

    int x;
    int y;
    AStar *searchalgo;
};

#endif
