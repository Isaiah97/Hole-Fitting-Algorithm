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

void print_menu(void){
	printf("\nHole-fitting Algorithms\n");
    printf("---------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Allocate memory for block using First-fit\n");
    printf("3) Allocate memory for block using Best-fit\n");
    printf("4) Deallocate memory for block\n");
    printf("5) Defragment memory\n");
    printf("6) Quit program\n\n");
}

void print_allocated_blocks(void) {
	Block *curr = head;

	printf("\nID 	Start 	End\n");
	printf("-----------------");

	while (curr != NULL) {
		printf("%d\t%d\t%d\n", curr->id, curr->start, surr->end);
		curr = curr->next;
	}
}


void enter_parameters(void) {
	int size;

	printf("Enter size of physical memory: ");
	if (scanf("%d", &size) != 1 || size <= 0) {

		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Invalid memory size. Keeping previous settings.\n");
		return;
	}
	clear_all_blocks();
	pm_size = size;
}

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

	Block *curr = head;
	Block *prev = NULL;

	int hole_start;
	int hole_end;
	int hole_size;

	hole_start = 0;
	hole_end = head->start;	
	hole_size = hole_end - hole_start;

	if (hole_size >= block_size) {
		Block *new_block = (Block *)malloc(sizeof(Block));
		if (!new_block) {
			printf("Error: Memory allocation failed.\n");
			return;
		}

		new_block->id = id;
		new_block->start = hole_start;
		new_block->end = hole_start + block_size;
		new_block->next = head;
		head = new_block;
		return;
	}

	prev = head;
	curr = head->next;

	while (curr != NULL) {
		hole_start = prev->end;
		hole_end = curr->start;
		hole_size = hole_end - hole_start;

		if (hole_size >= block_size) {
			Block *new_block = (Block *)malloc(sizeof(Block));
			if (!new_block) {
				printf("Error: Memory allocation failed.\n");
				return;
			}

			new_block->id = id;
			new_block->start = hole_start;
			new_block->end = hole_start	+ block_size;

			new_block->next = curr;
			prev->next = new_block;
			return;
		}

		prev = curr;
		curr = curr->next;
	}

	hole_start = prev->end;
	hole_end = pm_size;
	hole_size = hole_end - hole_start;

	if (hole_size >= block_size) {
		Block *new_block = (Block *)malloc(sizeof(Block));
		if(!new_block) {
			printf("Error: Memory allocation failed");
			return;
		}

		new_block->id = id;
		new_block->start = hole_start;
		new_block->end = hole_start + block_size;
		new_block->next = NULL;

		prev->next = new_block;
		return;
	}

	printf("Error: Not enough memory to allocate block.\n");
}

void allocated_best_fit(void) {
	int id;
	int block_size;

	if (pm_size <= 0) {
		printf("Error: Physical memory size not set. Choose ")
		return;
	}

	printf("Enter block id: ");
	if (scanf("%d", &id) != 1){
		int c;
		 int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Invalid id.\n");
        return;
    }

    printf("Enter block size: ");
    if (scanf("%d", &block_size) != 1 || block_size <= 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Invalid block size.\n");
        return;
    }

    if (id_exists(id)) {
        printf("Error: Duplicate block id. Allocation rejected.\n");
        return;
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

    int best_hole_found = 0;
    int best_hole_start = -1;
    int best_hole_size = pm_size + 1; 

    Block *prev = NULL;
    Block *curr = head;

    int hole_start, hole_end, hole_size;

    hole_start = 0;
    hole_end = head->start;
    hole_size = hole_end - hole_start;

    if (hole_size >= block_size && hole_size < best_hole_size) {
        best_hole_found = 1;
        best_hole_start = hole_start;
        best_hole_size = hole_size;
    }

    prev = head;
    curr = head->next;

    while (curr != NULL) {
        hole_start = prev->end;
        hole_end = curr->start;
        hole_size = hole_end - hole_start;

        if (hole_size >= block_size && hole_size < best_hole_size) {
            best_hole_found = 1;
            best_hole_start = hole_start;
            best_hole_size = hole_size;
        }

        prev = curr;
        curr = curr->next;
    }

    hole_start = prev->end;
    hole_end = pm_size;
    hole_size = hole_end - hole_start;

    if (hole_size >= block_size && hole_size < best_hole_size) {
        best_hole_found = 1;
        best_hole_start = hole_start;
        best_hole_size = hole_size;
    }

    if (!best_hole_found) {
        printf("Error: Not enough memory to allocate block.\n");
        return;
    }

    Block *new_block = (Block *)malloc(sizeof(Block));
    if (!new_block) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    new_block->id = id;
    new_block->start = best_hole_start;
    new_block->end = best_hole_start + block_size;
    new_block->next = NULL;

    if (new_block->start < head->start) {
        new_block->next = head;
        head = new_block;
        return;
    }

    Block *iter = head;
    while (iter->next != NULL && iter->next->start < new_block->start) {
        iter = iter->next;
    }

    new_block->next = iter->next;
    iter->next = new_block;
}
	
void deallocate_block(void){
	int id;

	printf("Enter block id: ");
	if (scanf("%d", &id) != 1) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Invalid id.\n");
		return;
	}

	Block *curr = head;
	Block *prev = NULL;

	while (curr != NULL && curr->id != id) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Error: Block id not found. Deallocation rejected.\n");
		return;
	}

	if (prev == NULL) {
		head = curr->next;
	}else{
		prev->next = curr->next;
	}

	free(curr);
}

void defragment_memory(void) {
	if (pm_size <= 0) {
		return;
	}

	if (head == NULL) {
		return;
	}

	int current_start = 0;
	Block *curr = head;


	while (curr != NULL) {
		int size = curr->end - curr->start;
		curr->start = current_start;
		curr->end = curr->start + size;
		current_start = curr->end;

		curr = curr->next;
	}
}

Block *find_block_by_id(int id){
	Block *curr = head;
	while(curr != NULL) {
		if (curr->id == id) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

bool id_exists(int id) {
	return find_block_by_id(id) != NULL;
}

void clear_all_blocks(void){
	
}

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