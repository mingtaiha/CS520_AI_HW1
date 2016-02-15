#include "draw.h"
#include "sim_window.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

using namespace arma;
using namespace std;

static int blocksize = 4;
static int linethickness = 1;

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

void blitRGB(SDL_Surface *screen, icube &image) {
  int w = getGridWidth(image.n_cols);
  int h = getGridHeight(image.n_rows);
  uint32_t *pixels = (uint32_t *)screen->pixels;
  uint32_t color_black = SDL_MapRGB(screen->format,0,0,0);
  SDL_FillRect(screen, NULL, color_black);
  for (int i = 0; i < (int)image.n_rows; i++) {
    for (int j = 0; j < (int)image.n_cols; j++) {
      // this might be a bit slow
      uint32_t color = SDL_MapRGB(screen->format,
          image(i,j,0),image(i,j,1),image(i,j,2));
      pixels[XY2P(j, i, screen->w, screen->h)] = color;
    }
  }
}

void drawGrid(icube &grid, imat &map) {
  int width = getGridWidth(map.n_cols);
  int height = getGridHeight(map.n_rows);
  if (grid.n_rows != height || grid.n_cols != width) {
    grid = icube(height, width, 3, fill::zeros);
  } else {
    grid.zeros();
  }
  icube whitesquare = ones<icube>(blocksize, blocksize, 3) * 255;
  icube graysquare = ones<icube>(blocksize, blocksize, 3) * 128;
  for (int i = 0; i < (int)map.n_rows; i++) {
    for (int j = 0; j < (int)map.n_cols; j++) {
      int startrow = linethickness * 2 + i * (blocksize + linethickness);
      int endrow = linethickness + (i + 1) * (blocksize + linethickness);
      int startcol = linethickness * 2 + j * (blocksize + linethickness);
      int endcol = linethickness + (j + 1) * (blocksize + linethickness);
      if (map(i, j)) {
        grid(span(startrow, endrow-1), span(startcol, endcol-1), span::all) = graysquare;
      } else {
        grid(span(startrow, endrow-1), span(startcol, endcol-1), span::all) = whitesquare;
      }
    }
  }
}

void drawPath(icube &grid, vector<ivec> &path, vector<ivec> &edges) {
  // start drawing the path
  icube redsquare = zeros<icube>(blocksize, blocksize, 3);
  redsquare.slice(0) = ones<imat>(blocksize, blocksize) * 255;
  for (ivec &node : path) {
    int x = node(0);
    int y = node(1);
    int startrow = linethickness * 2 + y * (blocksize + linethickness);
    int endrow = linethickness + (y + 1) * (blocksize + linethickness);
    int startcol = linethickness * 2 + x * (blocksize + linethickness);
    int endcol = linethickness + (x + 1) * (blocksize + linethickness);
    grid(span(startrow, endrow-1), span(startcol, endcol-1), span::all) = redsquare;
  }
  /*for (ivec &edge : edges){
    int idx1 = edge(0);
    int idx2 = edge(1);
    ivec pt1 = path[idx1];
    ivec pt2 = path[idx2];
    int cx1 = linethickness * 2 + pt1(0) * (blocksize + linethickness) + blocksize / 2;
    int cy1 = linethickness * 2 + pt1(1) * (blocksize + linethickness) + blocksize / 2;
    int cx2 = linethickness * 2 + pt2(0) * (blocksize + linethickness) + blocksize / 2;
    int cy2 = linethickness * 2 + pt2(1) * (blocksize + linethickness) + blocksize / 2;
    int x1 = MIN(cx1, cx2);
    int x2 = MAX(cx1, cx2);
    int y1 = MIN(cy1, cy2);
    int y2 = MAX(cy1, cy2);
    grid(span(y1, x1), span(y2, x2), span(0, 0)) = 0;
    grid(span(y1, x1), span(y2, x2), span(1, 1)) = 255;
    grid(span(y1, x1), span(y2, x2), span(2, 2)) = 0;
  }*/
}
