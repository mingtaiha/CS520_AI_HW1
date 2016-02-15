#ifndef maze_gen_h
#define maze_gen_h

#include <cstring>
#include <armadillo>
#include <iostream>
#include <cstdlib>
#include <ctime>

//Note:: The blocking probability is 100 times the actually probability
#define SIZE 101
#define BLOCK_PROB 30

arma::imat maze_gen(int size = SIZE, int block_prob = BLOCK_PROB);
bool maze_save(arma::imat maze);
arma::imat maze_load(std::string maze_name);

#endif
