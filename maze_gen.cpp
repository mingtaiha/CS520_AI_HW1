#include <iostream>
#include <cstdlib>
#include <ctime>
#include <armadillo>

#define size 10
#define block_prob 6
#define TESTING 0
//Note:: The blocking probability is 20 times the actually probability

using namespace std;
using namespace arma;


mat maze_gen() {

	int rand_val;
	mat maze(size, size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			rand_val = rand() % 20 + 1;

			if (rand_val <= block_prob) {
				maze(i , j) = 1;
			}
			else {
				maze(i , j) = 0;
			}
		}
	} 

	return maze;
}

#if TESTING
int main()
{
	
	mat maze;

	cout << "Generating a maze.\n";

	maze = maze_gen();

	cout << "Printing the maze\n\n";

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << maze(i , j ) << " ";
		}
		cout << endl;
	}
	return 0;
}
#endif
