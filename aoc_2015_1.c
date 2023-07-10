#include <stdio.H>

int main(void) {
	long floor = 0;
	long position = 0;
	char c;
	while ((c = getchar()) != EOF) {
		position++;
		if (c == '(') {
			floor++;
		}
		else if (c == ')') {
			floor--;
		}
		if (floor == -1) {
			break;
		}
	}
	printf("floor = %ld\n", floor);
	printf("position = %ld\n", position);
	return 0;
}
