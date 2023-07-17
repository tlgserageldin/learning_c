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
#define MAXCHARPAIRS 15
#define TRUE 1
#define FALSE 0

struct CharPair {
	char first_letter;
	char second_letter;
	int indexf;
};

void test_has_two_letters_twice(void);
void test_cmp_charpair(void);
void test_has_repeat_with_one_inbetween(void);
void print_charpair_struct(struct CharPair *pair);
int cmp_charpair(const void *a, const void *b);
int has_two_letters_twice(char *line);
int has_repeat_with_one_inbetween(char *line);

int main(void) {
	// FILE *f_input;
	// f_input = fopen("aoc_2015_5_input.txt", "r");
	// if (f_input == NULL) {
	// 	printf("failed to open file, exiting...\n");
	// 	exit(1);
	// }
	// char line[LINESIZE];
	// int ns = 0;
	// while ((fgets(line, LINESIZE+1, f_input)) != NULL) {
	// 	line[strlen(line)-1] = '\0';
	// 	printf("%s\n", line);
	// 	if (has_two_letters_twice(line) && has_repeat_with_one_inbetween(line)) {
	// 		ns++;
	// 	}
	// }
	// fclose(f_input);
	// printf("\n\nnice strings: %d\n\n", ns);
	// return 0;
	test_has_two_letters_twice();
}

// like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
// intput lines guaranteed to be 16 char + '\0'
int has_two_letters_twice(char *line) {
	if (line == NULL || strlen(line) != LINESIZE-1) { //should be guaranteed to not be null, just in case
		return 0;
	}
	char *first, *second;
	size_t npairs = 1;
	struct CharPair *pairs = malloc(sizeof(struct CharPair));
	if (pairs == NULL) {
		printf("failed malloc call, exiting...\n\n");
		exit(1);
	}
	pairs[0].first_letter = pairs[0].second_letter = '\0';
	pairs[0].indexf = 0;
	for (int i = 0; i < strlen(line)-1; i++) {
		first = line+i;
		second = line+i+1;
		struct CharPair key = {.first_letter=*first, .second_letter=*second};
		struct CharPair *res = bsearch(&key, pairs, npairs, sizeof(struct CharPair), cmp_charpair);
		if (res) {
			printf("found pair %c %c\n", res->first_letter, res->second_letter);
			if (!((i-res->indexf) < 2)) {
				return TRUE;
			}
			printf("pair overlapped, doesnt count\n");
		} else {
			printf("did not find %c %c, adding to array\n", *first, *second);
			pairs = realloc(pairs, npairs++ * sizeof(struct CharPair));
			if (pairs == NULL) {
				printf("failed realloc call, exiting...\n");
				exit(1);
			}
			pairs[npairs-1].first_letter = *first;
			pairs[npairs-1].second_letter = *second;
			pairs[npairs-1].indexf = i;
			qsort(pairs, npairs, sizeof(struct CharPair), cmp_charpair);
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
	if (!strcmp(line, "")) {
		return FALSE;
	}
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
	char *test_str = "aabcdefvhijklmaa"; //aa
	char *empty_str = ""; //empty
	char *test_str2 = "abbbcdefghijklmn";
	char *test_str3 = "abcdefbclkjhuion"; //should work bc is there twice
	char *test_str4 = "aaaaefbclkjhuion"; //aaaa should work
	assert(has_two_letters_twice(test_str));
	assert(!has_two_letters_twice(empty_str));
	assert(!has_two_letters_twice(test_str2));
	assert(has_two_letters_twice(test_str3));
	assert(has_two_letters_twice(test_str4));
}
void test_has_repeat_with_one_inbetween(void) {
	char *test_str = "abacdefabcdefghi";//repeat at beginning
	assert(has_repeat_with_one_inbetween(test_str)); 
	char *empty_str = ""; //empty
	assert(!has_repeat_with_one_inbetween(empty_str)); 
	char *test_str2 = "abcdefgabcdefcac"; //repeat at end
	assert(has_repeat_with_one_inbetween(test_str2));
	char *test_str3 = "abcdefabcdefghij"; //no repeate
	assert(!has_repeat_with_one_inbetween(test_str3));
}

void print_charpair_struct(struct CharPair *pair) {
	printf("charpair first char: %c, charpair second char: %c, count: %d\n", pair->first_letter, pair->second_letter, pair->indexf);
}

void test_cmp_charpair(void) {
	struct CharPair a = { .first_letter='a', .second_letter='b' };
	struct CharPair b = { .first_letter='a', .second_letter='b' };
	assert(cmp_charpair(&a, &b) == 0);
	struct CharPair c = { .first_letter='a' };
	struct CharPair d = { .first_letter='b' };
	assert(cmp_charpair(&c, &d) == -1);
	struct CharPair e = { .first_letter='a', .second_letter='a' };
	struct CharPair f = { .first_letter='a', .second_letter='b' };
	assert(cmp_charpair(&e, &f) == -1);
	struct CharPair g = { .first_letter='b', .second_letter='a' };
	struct CharPair h = { .first_letter='a', .second_letter='b' };
	assert(cmp_charpair(&g, &h) == 1);
	struct CharPair i = { .first_letter='b', .second_letter='a' };
	struct CharPair j = { .first_letter='a', .second_letter='b' };
	assert(cmp_charpair(&i, &j) == 1);
}
