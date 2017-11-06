/*
 * main.c
 *
 *  Created on: Mar 30, 2016
 *      Author: Derek
 *
 *  Simulates population dispersion according to the model
 *  of Conway's Game of Life
 *
 *  After running life.exe, input the name of a pgm/txt (must include file extension) file containing
 *  the initial configuration as well as the number of frames to iterate.
 */

#include "life.h"

void main(){
	char name[13];
	int frames;
	while(1){
		printf("Please enter the name of the file containing the inital config: \n");
		scanf("%s", &name);
		printf("Please enter the number of iterations to simulate: \n");
		scanf("%d", &frames);
		load(name, frames);
	}
}
