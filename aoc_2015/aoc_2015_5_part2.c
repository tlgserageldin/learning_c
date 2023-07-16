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

	while ((fgets(line, LINESIZE+1, f_input)) != NULL) {
		line[strlen(line)-1] = '\0';
		if (has_two_letters_twice(line) && has_repeat_with_one_inbetween(line)) {
			ns++;
		}
	}
	fclose(f_input);
	printf("\n\nnice strings: %d\n\n", ns);
	return 0;
}

// like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
// intput lines guaranteed to be 16 char + '\0'
int has_two_letters_twice(char *line) {
	if (line == NULL || strlen(line) != 16) { //should be guaranteed to not be null, just in case
		return 0;
	}
	size_t n = strlen(line)/2; // should always be 8
	char *one = line;
	char *two = line++;
	struct CharPair *pairs = calloc(n, sizeof(struct CharPair));
	if (pairs == NULL) {
		printf("failed calloc call, exiting...\n\n");
		exit(1);
	}
	pairs[0].first_letter = *one;
	pairs[0].second_letter = *two;
	for (int i = 0; i < n; i++) {
		pairs[i].count = 1;
	}
	size_t foundp = 1;
	for (int i = 1; i < n; i++) {
		struct CharPair key = { .first_letter=*(one+=2), .second_letter=*(two+=2) };
		struct CharPair *res = bsearch(&key, pairs, n, sizeof(struct CharPair), cmp_charpair);
		if (res) {
			res->count++;
		} else {
			pairs[foundp] = *res;
			pairs[foundp].count = 1;
			foundp++;
		}
	}
	if (foundp == n) {
		qsort(pairs, n, sizeof(struct CharPair), cmp_charpair);
	} else {
		pairs = realloc(pairs, foundp * sizeof(struct CharPair));
		if (pairs == NULL) {
			printf("failed realloc call, exiting...\n\n");
			exit(1);
		}
		qsort(pairs, foundp, sizeof(struct CharPair), cmp_charpair);
	}
	for (int i = 0; i < foundp; i++) {
		if (pairs[i].count > 1) {
			return 1;
		}
	}
	free(pairs);
	return 0;
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
