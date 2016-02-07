#include <cstring>
#include <armadillo>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace arma;


imat maze_gen(int size, int block_prob);
bool maze_save(imat maze, int i = 0);
imat maze_load(string maze_name);
