/* this is first project where I am going to have to work with dynamic memory allocation.
 * you are on a 2-d plane, you are going to be given tranversing instructions
 * keep track of how many coordinate pairs are visited atleast once
 *
 * for part two we now need to make two seperate lists
 * if current_char index % 2 != 0
 * 	store in santa list
 * if current_char index % 2 = 0
 * 	store in robot-santa list
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

int check_visited(int x, int y, struct House_Node * house) {
	while (house != NULL) {
		if (house->x == x && house->y == y) {
			return TRUE;
		}
		house = house->next;
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
//	f_input = fopen("aoc_2015_3_input.txt", "r");
	f_input = fopen("aoc2015_3_test_input.txt", "r");
	int c, index;
	int santa_x, santa_y;
	int r_santa_x, r_santa_y;
	santa_y = santa_x = r_santa_x = r_santa_y = index = 0;
	struct House_Node * santa_list = malloc(sizeof(struct House_Node));
	init_house(santa_list);
	struct House_Node * r_santa_list = malloc(sizeof(struct House_Node));
	init_house(r_santa_list);
	while((c = fgetc(f_input)) != EOF) {
		if (index % 2 != 0) {
			switch (c) {
				case '^':
					santa_y += 1;
					break;
				case 'v':
					santa_y -= 1;
					break;
				case '>':
					santa_x += 1;
					break;
				case '<':
					santa_x -= 1;
					break;
				case '\n':
					printf("encountered end of line\n");
					break;
				default:
					printf("encountered unexpected character, exiting...\n");
					exit(1);
			}
			if (!check_visited(santa_x, santa_y, santa_list)) {
				push_node(&santa_list, santa_x, santa_y);
			}
		}
		else {
			switch (c) {
				case '^':
					r_santa_y += 1;
					break;
				case 'v':
					r_santa_y -= 1;
					break;
				case '>':
					r_santa_x += 1;
					break;
				case '<':
					r_santa_x -= 1;
					break;
				case '\n':
					printf("encountered end of line\n");
					break;
				default:
					printf("encountered unexpected character, exiting...\n");
					exit(1);
			}
			if (!check_visited(r_santa_x, r_santa_y, r_santa_list)) {
				push_node(&r_santa_list, r_santa_x, r_santa_y);
			}
		}
	index++;
	}
	printf("Number of Houses: %d\n", (count_nodes(santa_list) + count_nodes(r_santa_list)));
	print_nodes(santa_list);
	print_nodes(r_santa_list);
	return 0;
}
