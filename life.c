/*
 * life.c
 *
 *  Created on: Mar 30, 2016
 *      Author: Derek
 */

#include "life.h"

void load(char file[13], int n){
	FILE* f = fopen(file, "r");
	frame_ptr p = (frame_ptr)malloc(sizeof(frame));
	p -> maxframes = n;
	fscanf(f, "%*[^\n]\n", NULL); //Skips P2
	fscanf(f, "%d", &p -> width); //Model width
	fscanf(f, "%d", &p -> height); //Model height
	int trash;
	fscanf(f, "%d", trash); //Skips White Value
	int first[p -> width + 2][p -> height + 2]; //Creates boarder around model for first frame
	int w = p -> width + 1;
	int h = p -> height + 1;
	memset(first, 0, (w+1)*(h+1)*sizeof(int));
	int a = (w-1) * (h-1);
	int temp[a];
	int counter = 0;
	int i,j;

	//Reads initial configuration and assigns it to a temp model
	for(i = 0; i < a; i++){
		fscanf(f, "%d", &temp[i]);
	}
	for(j = 1; j < p -> height + 1; j++){
		for(i = 1; i < p -> width + 1; i++){
			first[i][j] = temp[counter];
			counter ++;
		}
	}

	//Changes 0 to O and 1 to X
	char cfirst[p -> width + 2][p -> height + 2];
	for(j = 0; j < p -> height + 2; j++){
		for(i = 0; i < p -> width + 2; i++){
			if(first[i][j] == 0){
				cfirst[i][j] = 'O';
			}
			else if(first[i][j] == 1){
				cfirst[i][j] = 'X';
			}
		}
	}

	//Allocates the frame model
	p -> array = (char**)malloc((w+1)*sizeof(char*));
	for(i = 0; i < w+1; i++){
		p -> array[i] = (char*)malloc((h+1)*sizeof(char));
	}

	//Applies the initial configuration to the frame model
	for(j = 0; j < p -> height + 2; j++) {
		for(i = 0; i < p -> width + 2; i++) {
			p -> array[i][j] = cfirst[i][j];
		}
	}

	display(p);
}

//Produces subsequent iteration of the model by calling fate of each cell
frame_ptr step(frame_ptr p){
	char next[p -> width + 2][p -> height + 2];
	int i,j;
	for(j = 0; j < p -> height + 2; j++){
		for(i = 0; i < p -> width + 2; i++){
			next[i][j] = 'O';
		}
	}
	for(j = 1; j < p -> height + 1; j++){
		for(i = 1; i < p -> width + 1; i++){
			next[i][j] = fate(p, i, j);
		}
	}
	for(j = 0; j < p -> height + 2; j++) {
		for(i = 0; i < p -> width + 2; i++) {
			p -> array[i][j] = next[i][j];
		}
	}

	return p;
}

//Determines the fate of the specified cell (X designates survival and O represents death)
char fate(frame_ptr p, int i, int j){
	if(p -> array[i][j] == 'O'){
		int live = 0;
		if(p -> array[i+1][j] == 'X')
			live ++;
		if(p -> array[i][j+1] == 'X')
			live ++;
		if(p -> array[i-1][j] == 'X')
			live ++;
		if(p -> array[i][j-1] == 'X')
			live ++;
		if(p -> array[i+1][j+1] == 'X')
			live ++;
		if(p -> array[i+1][j-1] == 'X')
			live ++;
		if(p -> array[i-1][j+1] == 'X')
			live ++;
		if(p -> array[i-1][j-1] == 'X')
			live ++;
		if(live == 3) //recovers through reproduction
			return 'X';
		else if(live != 3){ //remains dead
			return 'O';
		}
	}
	if(p -> array[i][j] == 'X'){
		int live = 0;
		if(p -> array[i+1][j] == 'X')
			live ++;
		if(p -> array[i][j+1] == 'X')
			live ++;
		if(p -> array[i-1][j] == 'X')
			live ++;
		if(p -> array[i][j-1] == 'X')
			live ++;
		if(p -> array[i+1][j+1] == 'X')
			live ++;
		if(p -> array[i+1][j-1] == 'X')
			live ++;
		if(p -> array[i-1][j+1] == 'X')
			live ++;
		if(p -> array[i-1][j-1] == 'X')
			live ++;
		if(live == 2 || live == 3) //lives
			return 'X';
		if(live < 2){ //dies to underpopulation
			return 'O';
		}
		if(live > 3){ //dies to overpopulation
			return 'O';
		}
	}
	return 'F'; //indicating the function failed
}

//Displays the inital configuration (the seed) and the specified number of iterations
void display(frame_ptr p){
	int x,i,j;
	printf("Seed: %d %d\n", p -> width, p -> height);
	for(j = 0; j < p -> height + 2; j++) {
		for(i = 0; i < p -> width + 2; i++) {
			printf("%c ", p -> array[i][j]);
		}
		printf("\n");
	}
	for(x = 1; x <= p -> maxframes; x++){
		p = step(p);
		printf("Frame: %d\n", x);
		for(j = 0; j < p -> height + 2; j++) {
		    for(i = 0; i < p -> width + 2; i++) {
		        printf("%c ", p -> array[i][j]);
		    }
		    printf("\n");
		}
	}
}
