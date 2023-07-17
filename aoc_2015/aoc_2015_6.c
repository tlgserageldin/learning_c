/*
Because your neighbors keep defeating you in the holiday house decorating contest year after year,
you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction;
the lights at each corner are at 0,0, 0,999, 999,999, and 999,0.
The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs.
Each coordinate pair represents opposite corners of a rectangle, inclusive;
a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.

For example:

    turn on 0,0 through 999,999 would turn on (or leave on) every light.
    toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
    turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.

After following the instructions, how many lights are lit?
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ON 1
#define OFF 0
#define TOGGLE 0
#define TURNON 1
#define TURNOFF 2
#define MAXLINELEN 100

void toggle_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
void turnon_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
void turnoff_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
int parse_input(char *line);

int main(void) {
	//int lights[1000][1000];
	//FILE *input = fopen("aoc_2015_6_input.txt", "r");
	//if (input == NULL) {
	//	printf("failed to open file, exiting...\n");
	//	exit(1);
	//}
	//char line[MAXLINELEN];
	//while ((fgets(line, MAXLINELEN, input)) != NULL) {
	//	line[strlen(line) - 1] = '\0';
	//}
	//fclose(input);
	return 0;
}

void toggle_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y) {
	for (int i = fcoord_y; i <= tcoord_y; i++) {
		for (int j = fcoord_x; j <= tcoord_x; j++) {
			if (array[i][j] == ON) {
				array[i][j] = OFF;
			} else {
				array[i][j] = ON;
			}
		}
	}
}
void turnon_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y) {
	for (int i = fcoord_y; i <= tcoord_y; i++) {
		for (int j = fcoord_x; j <= tcoord_x; j++) {
				array[i][j] = ON;
		}
	}
}

void turnoff_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y) {
	for (int i = fcoord_y; i <= tcoord_y; i++) {
		for (int j = fcoord_x; j <= tcoord_x; j++) {
				array[i][j] = OFF;
		}
	}
}

int parse_input(char *line) {
	if (line == NULL) {
		printf("passed char* is null, exiting...\n");
		exit(1);
	}
	char fword[10];
	char *c = line;
	int i = 0;
	while (*c != ' ') {
		fword[i] = *c;
		c++;
		i++;
	}
	fword[i++] = '\0';
	c++;
	if (strcmp(fword, "toggle") == 0) {
		return TOGGLE;
	} else {
		i = 0;
		while (*c != ' ') {
			fword[i] = *c;
			c++;
			i++;
		}
		fword[i++] = '\0';
		if (strcmp(fword, "on") == 0) {
			return TURNON;
		} else {
			return TURNOFF;
		}
	
	}
}

