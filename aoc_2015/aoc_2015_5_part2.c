/*
new nice string rules
It contains a pair of any two letters that appears at least twice in the string without overlapping,
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 17
#define TRUE 1
#define FALSE 0

struct CharPair {
	char first_letter;
	char second_letter;
	int count;
};

int cmp_charpair(const void *a, const void *b);
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

/*
create pointers and step thru the passed char array
until second letter pointer == NULL
	binary search array for pair
	if !found
		append to end and quicksort array
	else
		TwoCharPair->count++
if any node.count > 1
	return TRUE
*/
int has_two_letters_twice(char *line) {
	char *first, *second;
	first = line;
	second = first+1;
	struct CharPair *pairs = malloc(sizeof(struct CharPair));
	pairs->first_letter = *first;
	pairs->second_letter = *second;
	pairs->count = 0;
	while (*second != '\0') {
	
	}
}

int cmp_charpair(void const *a, void const *b) {
	struct CharPair *key = (struct CharPair *) a;
	struct CharPair *elem = (struct CharPair *) b;
	if (key->first_letter < elem->first_letter) {
		return -1;
	} else if (key->first_letter > elem->first_letter) {
		return 1;
	} else {
		if (key->second_letter < elem->second_letter) {
			return -1;
		} else if (key->second_letter > elem->second_letter) {
			return 1;
		} else {
			return 0;
		}
	}
}
