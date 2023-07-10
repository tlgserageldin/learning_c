#include <stdio.h>

int main(void) {
	long char_count;
	char_count = 0;

	while(getchar() != EOF) {
		char_count++;
	}

	printf("%ld\n", char_count);
	return 0;
}
