#include "heuristic.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))

int mdist(int x1, int y1, int x2, int y2) {
  // TODO: fill in the manhattan distance here
//  printf("[heuristic.cpp] Remember to fill in the manhattan distance\n"); // remove this line
//  exit(1); // remove this line
  return ABS(x1 - x2) + ABS(y1 - y2);
}
