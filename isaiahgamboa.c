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
void allocated_first_fit(void){
	int id, block_size;

	if (pm_size <= 0) {
		printf("Error: Physical memory size not set. Choose option 1 first.\n");
		return;
	}

	printf("Enter block id: ");
	if (scanf("%d", &id) != 1) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Invalid id.\n");
		return;
	}

	printf("Enter block size: ");
	if (scanf("%d", &block_size) != 1 || block_size <= 0){
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Invalid block size.\n");
		return;
	}

	if (id_exists(id)) {
		printf("Error: Duplicate block id. Allocation rejected. \n");
		return
	}

	if (head == NULL) {
		if (block_size > pm_size) {
			printf("Error: Not enough memory to allocate block.\n");
			return;
		}

		Block *new_block = (Block *)malloc(sizeof(Block));
		if (!new_block) {
			printf("Error: Memory allocation failed.\n");
			return;
		}

		new_block->id = id;
		new_block->start = 0;
		new_block->end = block_size;
		new_block->next = NULL;

		head = new_block;
		return;
	}

	
}
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
		switch (choice) {
		case 1:
			enter_parameters();
			print_allocated_blocks();
			break;

		case 2:
			allocated_first_fit();
			print_allocated_blocks();
			break;

		case 3:
			allocated_best_fit();
			print_allocated_blocks();
			break;

		case 4:
			deallocate_block();
			print_allocated_blocks();
			break;

		case 5:
			defragment_memory();
			print_allocated_blocks();
			break;

		case 6:
			printf("Quitting program...\n");
			running = 0;
			break;

		default:
			printf("Invalid selection. Please enter a number between 1 and 6.\n");
			break;
		}
	}
	clear_all_blocks();
	return 0;
}