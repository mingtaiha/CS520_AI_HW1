#ifndef drawgrid_h
#define drawgrid_h

#include <armadillo>
#include <SDL2/SDL.h>

void setBlockSize(int bs);
void setLineThickness(int lt);
int getGridWidth(int n_cols);
int getGridHeight(int n_rows);
void drawGrid(SDL_Surface *screen, arma::mat map);

#endif
