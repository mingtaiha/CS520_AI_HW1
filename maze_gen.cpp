#include <iostream>
#include <cstdlib>
#include <ctime>
#include <armadillo>
#include <cstring>

#define SIZE 10
#define BLOCK_PROB 30
#define TESTING 1
//Note:: The blocking probability is 100 times the actually probability

using namespace std;
using namespace arma;

imat maze_gen(int size, int block_prob) {

	int rand_val;
	imat maze(size, size);
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			rand_val = rand() % 100 + 1;

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


bool maze_save(imat maze, int i = 0) {

	char maze_name[256];
	string name;
	
	sprintf(maze_name, "Maze%d.dat", i);
	name = string(maze_name);
	maze.save(name);

}


imat maze_load(string maze_name) {

	imat loaded_maze;
	loaded_maze.load(maze_name);

	return loaded_maze;
}



#if TESTING
int main()
{
		
	imat maze;
	imat loaded_maze;
	bool isSaved;

	cout << "Generating a maze.\n";

	maze = maze_gen(SIZE, BLOCK_PROB);

	cout << "Printing the maze\n\n";

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << maze(i , j) << " ";
		}
		cout << endl;
	}

	isSaved = maze_save(maze);

	loaded_maze.load("Maze0.dat");
	
	cout << loaded_maze << endl;

	return 0;
}
#endif
