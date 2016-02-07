#include "heuristic.h"
#include <cmath>

double mdist(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}
