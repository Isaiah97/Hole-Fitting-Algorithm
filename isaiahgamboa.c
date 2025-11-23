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

void print_menu(void);
void print_allocated_blocks(void);

void enter_parameters(void);
void allocated_first_fit(void);
void allocated_best_fit(void);
void deallocate_block(void);
void defragment_memory(void);

Block *find_block_by_id(int id);
bool id_exists(int id);
void clear_all_blocks(void);

int main(void) {
	int choice;
	int running = 1;

	while (running) {
		print_menu();
		printf("\nEnter selection: ");
		if(scanf("%d", &choice) != 1) {
			int c;
			while((c = getchar()) != '\n' && c!= EOF) { }
				printf("Invalid input. Please enter a number between 1 and 6. \n");
			continue;
		}

		
	}
}