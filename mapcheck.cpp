#include "mapcheck.h"
#include <iostream>
#include <cassert>

using namespace arma;
using namespace std;

#define TEST_bfscheck_cpp 1

// use bfs to validate the map
bool isValidMap(mat map, int x1, int y1, int x2, int y2) {
  assert(0 <= x1 && x1 < (int)map.n_cols);
  assert(0 <= y1 && y1 < (int)map.n_rows);
  assert(0 <= x2 && x2 < (int)map.n_cols);
  assert(0 <= y2 && y2 < (int)map.n_rows);
  // flood the thingy with bfs
  vector<ivec> fringe;
  fringe.push_back(ivec({ y1, x1 }));
  umat visited(map.n_rows, map.n_cols, fill::zeros);
  visited(y1, x1) = 1;
  for (int i = 0; i < fringe.size(); i++) {
    ivec pt = fringe[i];
    if (pt(0) == y2 && pt(1) == x2) {
      return true;
    }
    // add the neighbors
    ivec y = { pt(0) - 1, pt(0), pt(0), pt(0) + 1 };
    ivec x = { pt(1), pt(1) - 1, pt(1) + 1, pt(1) };
    for (int j = 0; j < 4; j++) {
      if (0 <= x(j) && x(j) < (int)map.n_cols &&
          0 <= y(j) && y(j) < (int)map.n_rows &&
          visited(y(j), x(j)) == 0 &&
          map(y(j), x(j)) == 0) {
        visited(y(j), x(j)) = 1;
        fringe.push_back(ivec({ y(j), x(j) }));
      }
    }
  }
  return false;
}

#if TEST_bfscheck_cpp

int main() {
  mat map1 = reshape(mat({
      0, 1, 0,
      0, 0, 0,
      0, 1, 0 }), 3, 3).t();
  mat map2 = reshape(mat({
      0, 1, 0,
      0, 1, 0,
      0, 1, 0 }), 3, 3).t();
  cout << isValidMap(map1, 0, 0, 2, 2) << endl;
  cout << isValidMap(map2, 0, 0, 2, 2) << endl;
  return 0;
}

#endif
