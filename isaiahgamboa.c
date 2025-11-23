/**
The program simulates memory allocation with a chosen hole-fitting algorithm (First-fit,
Best-fit) and implements deallocation and defragmentation. A menu controls the
operations, and each choice calls the appropriate procedure, where the choices are:
1) Enter parameters
2) Allocate memory for a block using First-Fit
3) Allocate memory for a block using Best-Fit
4) Deallocate memory for a block
5) Defragment memory
6) Quit program and free memory
**/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Block {
	int id;
	int start;
	int end;
	struct Block *next;
}
Block;

int pm_size = 0;
Block *head = NULL;

