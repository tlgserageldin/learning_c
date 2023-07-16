/*
new nice string rules
It contains a pair of any two letters that appears at least twice in the string without overlapping,
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
*/
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 17
#define MAXCHARPAIRS 122
#define TRUE 1
#define FALSE 0

struct CharPair {
	char first_letter;
	char second_letter;
	int count;
};

void test_has_two_letters_twice(void);
void test_has_repeat_with_one_inbetween(void);
int cmp_charpair(const void *a, const void *b);
int has_two_letters_twice(char *line);
int has_repeat_with_one_inbetween(char *line);

int main(void) {
	//FILE *f_input;
	//f_input = fopen("aoc_2015_5_input.txt", "r");
	//char line[LINESIZE];
	//int ns = 0;
	//while ((fgets(line, LINESIZE+1, f_input)) != NULL) {
	//	line[strlen(line)-1] = '\0';
	//	if (has_two_letters_twice(line) && has_repeat_with_one_inbetween(line)) {
	//		ns++;
	//	}
	//}
	//fclose(f_input);
	//printf("\n\nnice strings: %d\n\n", ns);
	//return 0;
	test_has_two_letters_twice();
}

// like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
// intput lines guaranteed to be 16 char + '\0'
int has_two_letters_twice(char *line) {
	if (line == NULL || strlen(line) != LINESIZE-1) { //should be guaranteed to not be null, just in case
		return 0;
	}
	size_t n = MAXCHARPAIRS;
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
		struct CharPair key = { .first_letter=*(one++), .second_letter=*(two++) };
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
			return TRUE;
		}
	}
	free(pairs);
	return FALSE;
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

// It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
int has_repeat_with_one_inbetween(char *line) {
	char *c = line;
	for (int i = 0; i < strlen(line)-2; i++) {
		if (*(c+i) == *(c+i+2)) {
			return TRUE;
		}
	}
	return FALSE;
}

void test_has_two_letters_twice(void) {
// only expecting 16 len str
	char *test_str = "aabcdefvhijklmaa";
	char *empty_str = "";
	char *test_str2 = "abbbcdefghijklmn";
	char *test_str3 = "abcdefbclkjhuionp";
	assert(has_two_letters_twice(test_str));
	assert(!has_two_letters_twice(empty_str));
	assert(!has_two_letters_twice(test_str2));
	assert(has_two_letters_twice(test_str3));
}
void test_has_repeat_with_one_inbetween(void) {
}
