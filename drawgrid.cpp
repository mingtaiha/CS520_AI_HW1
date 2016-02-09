#include "drawgrid.h"
#include "sim_window.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

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

void drawGrid(SDL_Surface *screen, arma::imat map) {
  int w = getGridWidth(map.n_cols);
  int h = getGridHeight(map.n_rows);
  uint32_t *pixels = (uint32_t *)screen->pixels;
  uint32_t color_black = SDL_MapRGB(screen->format,0,0,0);
  uint32_t color_white = SDL_MapRGB(screen->format,255,255,255);
  SDL_FillRect(screen, NULL, color_black);
  for (int i = 0; i < (int)map.n_rows; i++) {
    for (int j = 0; j < (int)map.n_cols; j++) {
      int start_x = linethickness + (linethickness + blocksize) * j;
      int start_y = linethickness + (linethickness + blocksize) * i;
      for (int x = start_x; x < MIN(start_x + blocksize, (int)map.n_cols); x++) {
        for (int y = start_y; y < MIN(start_y + blocksize, (int)map.n_rows); y++) {
          pixels[XY2P(x, y, screen->w, screen->h)] =
            map(y, x) > 0 ? color_black : color_white;
        }
      }
    }
  }
}
