#include "heuristic.h"

double mdist(vec a, vec b) {
  return sum(abs(a - b));
}
