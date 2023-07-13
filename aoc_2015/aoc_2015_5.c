/*
A nice string is one with all of the following properties:

It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TRUE 1
#define FALSE 0

int has_repeated_char(char* string);
int has_three_vowels(char* string);
int has_2char_substring(char* string, char* substring);
int is_element(char c, char* char_array);
void test_has_2char_substring(void);
void test_has_three_vowels(void);
void test_has_repeated_char(void);

int main(void) {
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

void test_has_three_vowels(void) {
	char test_string1[10];
	char test_string2[10];
	char test_string3[10];
	char test_string4[10];
	strcpy(test_string1, "tstvbscbd"); //test for 0 vowels
	strcpy(test_string2, "teaioaues"); //test for >3 vowels
	strcpy(test_string3, "xxsasides"); //test for ==3 vowels
	strcpy(test_string4, "axstsodss"); //test for <3 vowels
	printf("Testing has_three_vowels.\n");
	has_three_vowels(test_string1)? printf("test for 0 vowels failed.\n"): printf("test for 0 vowels passed.\n");
	has_three_vowels(test_string2)? printf("test for >3 vowels passed.\n"): printf("test for >3 vowels failed.\n");
	has_three_vowels(test_string3)? printf("test for ==3 vowels passed.\n"): printf("test for ==3 vowels failed.\n");
	has_three_vowels(test_string4)? printf("test <3 vowels failed.\n"): printf("test for <3 vowels passed.\n");
}
void test_has_2char_substring(void) {
	char test_string1[10];
	char test_string2[10];
	char test_string3[10];
	char test_string4[10];
	strcpy(test_string1, "testssdes"); //test for middle
	strcpy(test_string2, "testsades"); //test for no repeat
	strcpy(test_string3, "xxstssdes"); //test for repeat in front
	strcpy(test_string4, "axstssdss"); //test for repeat in end
	char substring[3];
	strcpy(substring, "ss");
	printf("Testing has_2char_substring.\n");
	has_2char_substring(test_string1, substring)? printf("find in middle passed.\n"): printf("find in middle failed.\n");
	has_2char_substring(test_string2, substring)? printf("find in middle failed.\n"): printf("no substring passed.\n");
	has_2char_substring(test_string3, substring)? printf("find at front passed.\n"): printf("find at front failed.\n");
	has_2char_substring(test_string4, substring)? printf("find at end passed\n"): printf("find at end failed\n");
}

void test_has_repeated_char(void) {
	char test_string1[10];
	char test_string2[10];
	char test_string3[10];
	char test_string4[10];
	strcpy(test_string1, "testsstde"); //test for middle
	strcpy(test_string2, "testsades"); //test for no repeat
	strcpy(test_string3, "xxstssdes"); //test for repeat in front
	strcpy(test_string4, "axstssdss"); //test for repeat in end
	printf("Testing has_repeated_char.\n");
	has_repeated_char(test_string1)? printf("repeat in middle test has passed.\n"): printf("repeat in middle failed.\n");
	has_repeated_char(test_string2)? printf("no repeat has failed.\n"): printf("no repeat has passed.\n");
	has_repeated_char(test_string3)? printf("repeat in the front has passed.\n"): printf("repeat in the front has failed.\n");
	has_repeated_char(test_string4)? printf("repeat in the end has passed.\n"): printf("repeat at the end has failed.\n");
	has_repeated_char("")? printf("empty string test has failed.\n"): printf("empty string test has passed.\n");
}
