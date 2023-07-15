/*
A nice string is one with all of the following properties:

It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
---

new nice string rules
It contains a pair of any two letters that appears at least twice in the string without overlapping,
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TRUE 1
#define FALSE 0

#define SIZE 100

int has_repeated_char(char* string);
int has_three_vowels(char* string);
int has_2char_substring(char* string, char* substring);
int is_element(char c, char* char_array);

int main(void) {
	FILE* f_input;
	f_input = fopen("aoc_2015_5_input.txt", "r");
	char line[SIZE];
	char b_strings[4][3] = {{'a', 'b', '\0'}, 
						    {'c', 'd', '\0'},
						    {'p', 'q', '\0'},
						    {'x', 'y', '\0'}};
	int ns_count = 0;
	while ((fgets(line, SIZE, f_input)) != NULL) {
		line[strlen(line)-1] = '\0';
		if (has_repeated_char(line) && has_three_vowels(line)) {
			int bs_count = 0;
			for (int i = 0; i<4; i++) {
				if (has_2char_substring(line, *(b_strings+i))) {
					bs_count++;
				}
			}
			if (bs_count == 0) {
				ns_count++;
			}
		}
	}
	fclose(f_input);
	printf("nice strings found: %d\n", ns_count);
	printf("\n\n");
	return 0;
}

int has_2char_substring(char* string, char* substring){
	while (*string != '\0') {
		if (*string == *substring) {
			char* old_string_loc;
			char* old_substring_loc;
			old_string_loc = string;
			old_substring_loc = substring;
			if (*string != '\0' || *substring != '\0') {
				string++;
				substring++;
				if (*string == *substring) {
					return TRUE;
				}
			}
			string = old_string_loc;
			substring = old_substring_loc;
		}
		string++;
	}
	return FALSE;
}

int has_repeated_char(char* string) {
	char last;
	while (*string != '\0') {
		if (last == *string) {
			return TRUE;
		}
		last = *string;
		string++;
	}
	return FALSE;
}

int has_three_vowels(char* string) {
	int v_count = 0;
	char vowels[6];
	strcpy(vowels, "aeiou");
	while(*string != '\0') {
		if (is_element(*string, vowels)) {
			v_count++;
		}
		string++;
	}
	if (v_count>=3) {
		return TRUE;
	}
	return FALSE;
}

int is_element(char c, char* string) {
	while (*string != '\0') {
		if (c == *string) {
			return TRUE;
		}
		string++;
	}
	return FALSE;
}
