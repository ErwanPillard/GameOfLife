/*
 * lifegame.c
 *
 *  Created on:
 *      Author:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lifegame.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDHEIGHT][WORLDWIDTH];

/* next generation cell states */
static int nextstates[WORLDHEIGHT][WORLDWIDTH];

/* functions to write for Part B of lab */
void initialize_world_from_file(const char * filename) {
	/* TODO: read the state of the world from a file with
	   name "filename". Assume file exists, is readable, and
	   the ith character of the jth line (zero-indexed) describes
	   world[i][j] according to the characters CHAR_ALIVE and
	   CHAR_DEAD

	   Assume a line does not contain more than 256 characters
	   (including newline). If a line doesn't contain WORLDWIDTH
	   characters, remaining cells in line are presumed DEAD.
	   Similarly, if the file does not contain WORLDHEIGHT lines,
	   remaining lines are presumed dead.

	   On error, print some useful error message and call abort().

	   Also need to reset the next generation to DEAD
	 */

	FILE *file = NULL;
	file = fopen(filename, "r");
	if(file == NULL){
		fprintf(stderr,"Error while opening file\n");
		abort();
	}

	char str[256];

	for (int x = 0; x < WORLDHEIGHT; x++) {
		if (fgets(str, sizeof(str), file) != NULL) {
			for (int y = 0; y < WORLDWIDTH; y++) {
				if (y < strlen(str) - 1) { // Vérifie la limite de la ligne
					world[x][y] = (str[y] == CHAR_ALIVE) ? ALIVE : DEAD;
				} else {
					world[x][y] = DEAD; // Marque comme morte si en dehors
				}
			}
		} else {
			// Marque les lignes restantes comme mortes si manquantes
			for (int y = 0; y < WORLDWIDTH; y++) {
				world[x][y] = DEAD;
			}
		}
		for (int y = 0; y < WORLDWIDTH; y++) {
			nextstates[x][y] = DEAD; // Réinitialise le tableau des générations futures
		}
	}



	fclose(file);


}

void save_world_to_file(const char * filename) {
	/* TODO: write the state of the world into a file with
	   name "filename". Assume the file can be created, or if
	   the file exists, overwrite the file. The ith character
	   of the jth line (zero-indexed) describes world[i][j]
	   using the characters CHAR_ALIVE and CHAR_DEAD

	   This file should be readable using the function
	   initialize_world_from_file(filename) above; we can use
	   it to resume a game later
	 */
	FILE *file = NULL;
	file = fopen(filename, "w");
	if(file == NULL){
		fprintf(stderr,"Error while opening file\n");
		abort();
	}

	char str[WORLDWIDTH + 2]; // +2 for newline and null terminator

	for (int y = 0; y < WORLDHEIGHT; y++) { // Parcourt des lignes
		for (int x = 0; x < WORLDWIDTH; x++) { // Parcourt des colonnes
			str[x] = world[y][x] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		}
		str[WORLDWIDTH] = '\n'; // Ajout d'un saut de ligne
		str[WORLDWIDTH + 1] = '\0'; // Null-terminate
		fputs(str, file);
	}

	fclose(file);

}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDHEIGHT; i++)
		for (j = 0; j < WORLDWIDTH; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int is_World_Empty(void) {
	for (int i = 0; i < WORLDWIDTH; i++)
		for (int j = 0; j < WORLDHEIGHT; j++)
			if (world[i][j] == ALIVE) return 0;
	return 1;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[y][x];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[y][x] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[y][x] = nextstates[y][x];
			nextstates[y][x] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';

	/*for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}*/
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[i][j] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}

	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
