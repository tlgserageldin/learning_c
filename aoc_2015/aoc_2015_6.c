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

#define TRUE 1
#define FALSE 0

#define TOGGLE 0
#define TURNON 1
#define TURNOFF 2

#define MAXLINELEN 100
#define MAXARGSSIZE 20

void toggle_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
void turnon_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
void turnoff_lights(int array[1000][1000], int fcoord_x, int fcoord_y, int tcoord_x, int tcoord_y);
int parse_for_command(char *line);
int *parse_for_arguments(char *line);
int is_element(char e, char *list, int len);
unsigned long count_lights(int array[1000][1000]);

int main(void) {
	int lights[1000][1000];
	turnoff_lights(lights, 0, 0, 999, 999);
	assert(count_lights(lights) == 0);
	char line[MAXLINELEN];
	FILE *input = fopen("aoc_2015_6_input.txt", "r");
	if (input == NULL) {
		printf("failed to open file, exiting...\n");
		exit(1);
	}
	while ((fgets(line, MAXLINELEN-1, input)) != NULL) {
		line[strlen(line)-1] = '\0';
		int cmd = parse_for_command(line);
		int *args = parse_for_arguments(line);
		if (cmd == TOGGLE) {
			toggle_lights(lights, *(args), *(args+1), *(args+2), *(args+3));
		} else if (cmd == TURNON) {
			turnon_lights(lights, *(args), *(args+1), *(args+2), *(args+3));
		} else {
			turnoff_lights(lights, *(args), *(args+1), *(args+2), *(args+3));
		}
	}
	printf("number of lights on: %lu\n",count_lights(lights));
	fclose(input);
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

int parse_for_command(char *line) {
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

int *parse_for_arguments(char *line) {
	char *c = line;
	char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char argsf[MAXARGSSIZE], argst[MAXARGSSIZE]; 
	static int args[4];
	while (!is_element(*c, nums, 10)) {
		c++;
	}
	int i = 0;
	while (*c != ' ') {
		argsf[i] = *c;
		c++;
		i++;
	}
	argsf[i++] = '\0';
	while (!is_element(*c, nums, 10)) {
		c++;
	}
	i = 0;
	while (*c != '\0') {
		argst[i] = *c;
		c++;
		i++;
	}
	args[0] = atoi(strtok(argsf, ","));
	args[1] = atoi(strtok(NULL, "\0"));
	args[2] = atoi(strtok(argst, ","));
	args[3] = atoi(strtok(NULL, "\0"));
	return args;
}

int is_element(char e, char *list, int len) {
	for (int i = 0; i < len; i++) {
		if (e == list[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

unsigned long count_lights(int array[1000][1000]) {
	unsigned long count = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (array[i][j] == ON) {
				count++;
			}
		}
	}
	return count;
}
