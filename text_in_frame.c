/* Write a function that takes a list of strings an prints them, one per line,
 * in a rectangular frame. For example the list 
 * ["Hello", "World", "in", "a", "frame"] gets printed as:
* 
* *********
* * Hello *
* * World *
* * in    *
* * a     *
* * frame *
* *********
*/

/*
 * find longest string
 * then print each passed string
 * 		
 */

#include <stdio.h>
#include <strings.h>

#define SIZE 100

int findLenLongestWord(const char *inputString) {
	int longestLength, currentLength;
	longestLength = currentLength = 0;
	for (int i = 0; i < strlen(inputString); i++) {
		if (*(inputString+i) == ' ') {
			if (currentLength > longestLength)
				longestLength = currentLength;
			currentLength = 0;
		}
		else {
			currentLength++;
		}
	}
	if (currentLength > longestLength)
		longestLength = currentLength;
	return longestLength;
}

int main(void) {
	printf("\nEnter a string to be placed into a frame (%d char): ", SIZE);
	char inputString[SIZE];
	fgets(inputString, SIZE, stdin); 
	inputString[strlen(inputString)-1]='\0';

	int longestWord = findLenLongestWord(inputString);
	char paddingString[longestWord+3];
	for (int i = 0; i <= longestWord+3; i++) {
		*(paddingString+i) = '*';
	}

	printf("%s\n", inputString);
	printf("%d\n", longestWord);
	printf("%s\n", paddingString);
	return 0;
}
