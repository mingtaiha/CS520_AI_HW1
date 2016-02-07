#include "drawgrid.h"

using namespace arma;

static int blocksize = 32;
static int linethickness = 2;

void setBlockSize(int bs) {
  blocksize = bs;
}

void setLineThickness(int lt) {
  linethickness = lt;
}

int getGridWidth(int n_cols) {
  int truewidth = (int)(n_cols + 3) * linethickness + (int)n_cols * blocksize;
  return truewidth;
}

int getGridHeight(int n_rows) {
  int trueheight = (int)(n_rows + 3) * linethickness + (int)n_rows * blocksize;
  return trueheight;
}

void drawGrid(SDL_Surface *screen, arma::mat map) {
  int w = getGridWidth();
  int h = getGridHeight();
  uint32_t *pixels = (uint32_t *)screen->pixels;
  for (int i = 0; i < (int)map.n_cols; i++) {
    for (int j = 0; j < (int)map.n_rows; j++) {
      // stop this
    }
  }
}
