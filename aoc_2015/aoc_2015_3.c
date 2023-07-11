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

void print_nodes(struct House_Node * start) {
	int i = 0;
	while (start != NULL) {
		printf("House %d: x=%d, y=%d\n", i, start->x, start->y);
		start = start->next;
		i++;
	}
}

int check_visited(struct House_Node * new_house, struct House_Node * start) {
	while (start != NULL) {
		if (start->x == new_house->x && start->y == new_house->y) {
			return TRUE;
		}
		start = start->next;
	}

	return FALSE;
}

void init_house(struct House_Node * house) {
	house->x = house->y = 0;
	house->next = NULL;
}

int count_nodes(struct House_Node * head) {
	int counter = 0;
	while (head != NULL) {
		counter++;
		head = head->next;
	}
	return counter;
}

void push_node(struct House_Node ** head, int new_x, int new_y) {
	struct House_Node * new_house = malloc(sizeof(struct House_Node));
	new_house->x = new_x;
	new_house->y = new_y;
	new_house->next = *head;
	*head = new_house;
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
		if (!check_visited(current_house, head)) {
			push_node(&head, current_house->x, current_house->y);
		}
	}
	printf("Number of Houses: %d\n", count_nodes(head));
	return 0;
}
