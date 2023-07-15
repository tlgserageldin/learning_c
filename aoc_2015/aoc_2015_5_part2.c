/*
new nice string rules
It contains a pair of any two letters that appears at least twice in the string without overlapping,
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
*/
#include <stdio.h>
#include <string.h>

#define LINESIZE 17
#define TRUE 1
#define FALSE 0

struct TwoCharNode {
	char first_letter;
	char second_letter;
	int count;
	struct TwoCharNode *next;
};

void init_TwoCharNode(struct TwoCharNode* node);
int has_two_letters_twice(char *line);
int has_repeat_with_one_inbetween(char *line);

int main(void) {
	FILE *f_input;
	f_input = fopen("aoc_2015_5_input.txt", "r");
	char line[LINESIZE];
	int ns = 0;
	while ((fgets(line, LINESIZE, f_input)) != NULL) {
		line[strlen(line)-1] = '\0';
		if (has_two_letters_twice(line) && has_repeat_with_one_inbetween(line)) {
			ns++;
		}
	}
	fclose(f_input);
	printf("\n\nnice strings: %d\n\n", ns);
	return 0;
}

int has_two_letters_twice(char *line) {
	// linked list of every unique pairs
	// every node has its char[] and count
	// at any node.count > 1
	// return TRUE
}

void init_TwoCharNode(struct TwoCharNode* node) {
	node->count = 0;
	node->next = NULL;
	node->first_letter = '\0';
	node->second_letter = '\0';
}

