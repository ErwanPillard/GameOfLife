/*
 * lab1b.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"
#include <stdlib.h>
#include <unistd.h>
#include "stdio.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(int argc, char ** argv)
{
	int n;

	/* TODO: initialize the world, from file argv[1]
	   if command line argument provided (argc > 1), or
	   using hard-coded pattern (use Part A) otherwise */

	if (argc > 1) {
        initialize_world_from_file(argv[1]);
		
    } else {
        initialize_world();  // Assume this function initializes a default pattern
    }
	
	for (n = 0; n < NUM_GENERATIONS; n++) {
			output_world();    // Display the world
			sleep(1);          // Pause for visual effect
			
			if (is_World_Empty()) {  // Check if all cells are dead
				printf("World is empty. Ending simulation early.\n");
				break;
			}

			next_generation();  // Proceed to the next generation
	}
	/* TODO: output final world state to console and save
	   world to file "world.txt" in current directory */

	output_world();
	save_world_to_file("world.txt");

	return 0;
}

void next_generation(void) {
	/* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) and set_next_state(x,y) */
	for(int i = 0; i < get_world_width(); i++){ //Largeur
		for (int j = 0; j < get_world_height(); j++){ //Hauteur
			set_cell_state(i, j, get_next_state(i, j));
		}
	}
	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	/* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */

	int numCellAlive = 0;
	numCellAlive = num_neighbors(x, y);
	if(get_cell_state(x, y) == ALIVE){ //ALIVE
		if(numCellAlive > 3 || numCellAlive < 2){
			return DEAD;
		}
		else{
			return ALIVE;
		}
	}
	else{ //DEAD
		if(numCellAlive == 3){
			return ALIVE;
		}
		else{
			return DEAD;
		}
	}
}

int num_neighbors(int x, int y) {
	/* TODO: for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */

	int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

	int numCellAlive = 0;

	for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
		
        if(get_cell_state(nx, ny) == ALIVE){
			numCellAlive++;
		}
    }
	return numCellAlive;
}

