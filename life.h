/*
 * life.h
 *
 *  Created on: Mar 30, 2016
 *      Author: Derek
 */

#ifndef LIFE_H_
#define LIFE_H_

#include "stdheader.h"

struct _frame{
	int size;
	int width;
	int height;
	int maxframes;
	char** array;
};

typedef struct _frame frame;
typedef struct _frame* frame_ptr;

void load(char[13],int);
frame_ptr step(frame_ptr);
char fate(frame_ptr,int,int);
void display(frame_ptr);

#endif /* LIFE_H_ */
