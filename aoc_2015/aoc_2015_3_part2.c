/*
 * just going to use a linked list and take the performance hit for iterating through the list.
 */
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct House {
	int x;
	int y;
	struct House * next;
};

int not_duplicate(int x, int y, struct House * start);
void push(int x, int y, struct House ** head);
int count_houses(struct House * head); 

int main(void) {
	int c, index;
	int santa_x, santa_y, r_santa_x, r_santa_y;
	index = santa_x = santa_y = r_santa_x = r_santa_y = 0;

	FILE * f_input;
	f_input = fopen("aoc_2015_3_input.txt", "r");

	struct House * head = malloc(sizeof(struct House));
	head->x = head->y = 0;
	head->next = NULL;

	while ((c = fgetc(f_input)) != EOF) {
		switch (c) {
			case '^':
				if ((index % 2) != 0) {
					santa_y++;
					break;
				} else {
					r_santa_y++;
					break;
				}
			case 'v':
				if ((index % 2) != 0) {
					santa_y--;
					break;
				} else {
					r_santa_y--;
					break;
				}
			case '>':
				if ((index % 2) != 0) {
					santa_x++;
					break;
				} else {
					r_santa_x++;
					break;
				}
			case '<':
				if ((index % 2) != 0) {
					santa_x--;
					break;
				} else {
					r_santa_x--;
					break;
				}
			case '\n':
				printf("hit newline\n");
				break;
			default:
				printf("unexpected char, exiting...\n");
				printf("%c\n", c);
				return 1;
		}
		if (not_duplicate(r_santa_x, r_santa_y, head)) {
			push(r_santa_x, r_santa_y, &head);
		}
		else if (not_duplicate(santa_x, santa_y, head)) {
			push(santa_x, santa_y, &head);
		}
		index++;
	}
	fclose(f_input);
	printf("number of houses visited: %d\n", count_houses(head));
	return 0;
}

int not_duplicate(int x, int y, struct House * start) {
	while (start != NULL) {
		if ((start->x == x) && (start->y == y)) {
			return FALSE;
		}
		start = start->next;
	}
	return TRUE;
}

void push(int new_x, int new_y, struct House ** head) {
	struct House * temp = malloc(sizeof(struct House));
	temp->x = new_x;
	temp->y = new_y;
	temp->next = *head;
	*head = temp;
}

int count_houses(struct House * head) {
	int count = 0;
	while (head != NULL) {
		count++;
		head = head->next;
	}
	return count;
}
