/* this is first project where I am going to have to work with dynamic memory allocation.
 * you are on a 2-d plane, you are going to be given tranversing instructions
 * keep track of how many coordinate pairs are visited atleast once
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct House_Node {
	int x;
	int y;
	struct House_Node * next;
};

void print_house_nodes(struct House_Node * start) {
	struct House_Node * current = start;
	int i = 0;
	while (current != NULL) {
		printf("House %d: x=%d, y=%d\n", i, current->x, current->y);
		current = current->next;
		i++;
	}
}

int already_visited(struct House_Node * new_house, struct House_Node * start) {
	struct House_Node * current;
	current = start;

	while (current != NULL) {
		if (current->x == new_house->x && current->y == new_house->y) {
			return TRUE;
		}
		current = current->next;
	}

	return FALSE;
}

void init_house(struct House_Node * house) {
	house->x = house->y = 0;
	house->next = NULL;
}

int number_of_houses(struct House_Node * head) {
	int counter = 0;
	struct House_Node * current = head;
	while (current != NULL) {
		counter++;
		current = current->next;
	}
	return counter;
}

int main(void) {
	FILE *f_input;
	f_input = fopen("aoc_2015_3_input.txt", "r");
//	f_input = fopen("aoc2015_3_test_input.txt", "r");
	int c;
	struct House_Node * head = malloc(sizeof(struct House_Node));
	init_house(head);
	struct House_Node * current_house = malloc(sizeof(struct House_Node));
	init_house(current_house);
	while((c = fgetc(f_input)) != EOF) {
		switch (c) {
			case '^':
				current_house->y += 1;
				break;
			case 'v':
				current_house->y -= 1;
				break;
			case '>':
				current_house->x += 1;
				break;
			case '<':
				current_house->x -= 1;
				break;
			case '\n':
				printf("encountered end of line\n");
				break;
			default:
				printf("encountered unexpected character, exiting...\n");
				exit(1);
		}
		if (!already_visited(current_house, head)) {
			struct House_Node * new_house = malloc(sizeof(struct House_Node));
			new_house->x = current_house->x;
			new_house->y = current_house->y;
			new_house->next = head;
			head = new_house;
		}
	}
	printf("Number of Houses: %d\n", number_of_houses(head));
	return 0;
}
