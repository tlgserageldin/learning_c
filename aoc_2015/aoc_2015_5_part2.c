/*
new nice string rules
It contains a pair of any two letters that appears at least twice in the string without overlapping,
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
*/
#include <stddef.h>
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
	if (line == NULL || strlen(line) < 2) { //unassigned pointer or string with <=1 char
		return FALSE;
	}
	char *one = line;
	char *two = line++;
	size_t n = 1;
	struct CharPair *pairs = calloc(n, sizeof(struct CharPair)); // will assue enough mem for this array
	pairs[0].first_letter = *one;
	pairs[0].second_letter = *two;
	pairs[0].count++; // init the first pair in array
	while (*two != '\0') { //no more pairs of char
		one = two;
		two++;

	}
	free(pairs); //put away toys
}

int cmp_charpair(void const *a, void const *b) {
	struct CharPair const *key = (struct CharPair *) a;
	struct CharPair const *elem = (struct CharPair *) b;
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
