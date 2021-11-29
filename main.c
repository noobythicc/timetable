#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createTimetable(char arg[]);
void printTimetable(char arg[]);
void deleteTimetable(char arg[]);
void drawCurrentTimetable(char timetable[25][25][25], int columns, int rows, char filename[]);
char* get_file(char filename[]);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Error: arguments missing\n");
		return 1;

	}
	else if (argc == 2) {
		printf("Error: one more argument missing\n");
		return 1;

	}
	else if (argc >= 4) {
		printf("Error: too many arguments\n");
		return 1;

	}

	if (strcmp(argv[1], "create") == 0) {
		createTimetable(argv[2]);

	}
	else if (strcmp(argv[1], "print") == 0) {
		printTimetable(argv[2]);

	}
	else if (strcmp(argv[1], "delete") == 0) {
		deleteTimetable(argv[2]);

	}
	else {
		printf("Error: first argument unknown\n");
		return 1;

	}

	return 0;

}

void createTimetable(char arg[]) {
	char days_of_the_week[5][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
	int rows;
	
	printf("timetable rows: ");
	scanf("%d", &rows);

	char timetable[25][25][25]; // 5 + 1 bec of "time" | 6, rows, 25

	strcpy(timetable[0][0], "Time"); // adding "time"
	for (int i = 1; i < 6; i++) {
		strcpy(timetable[i][0], days_of_the_week[i - 1]); // adding days of the week

	}

	int filling_num = 1;
	for (int c = 0; c < 6; c++) {
		for (int r = 1; r < rows + 1; r++) {
			sprintf(timetable[c][r], "%d", filling_num);
			filling_num++;

		}

	}
	
	char input[24];
	while ((getchar()) != '\n');

	int num = 1;

	drawCurrentTimetable(timetable, 6, rows, arg);
	for (int c = 0; c < 6; c++) {
		for (int r = 1; r < rows + 1; r++) {
			printf("cell %d: ", num);
			gets(input);
			sprintf(timetable[c][r], input);

			drawCurrentTimetable(timetable, 6, rows, arg);

			num++;

		}

	}

	printf("finished... saved as %s.", arg);

}

void printTimetable(char arg[]) {
	char* file = get_file(arg);

	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("file %s couldnt be found\n", arg);
		exit(1);

	}

	printf("timetable \"%s\":\n", arg);

	char ch;
	while ((ch = fgetc(fp)) != EOF)
		printf("%c", ch);

	fclose(fp);

}

void deleteTimetable(char arg[]) {
	char* file = get_file(arg);

	if (remove(file) == 0)
		printf("deleted timetable \"%s\" successfully\n", arg);
	else
		printf("couldnt delete the timetable \"%s\".", arg);

}

void drawCurrentTimetable(char timetable[25][25][25], int columns, int rows, char filename[]) {
	int max = 0;

	char* file = get_file(filename);

	// printf("%s\n", file);
	FILE* fp = fopen(file, "w");

	for (int c = 0; c < columns + 1; c++) {
		for (int r = 0; r < rows + 1; r++) {
			// printf("%s, ", timetable[c][r]);
			if (strlen(timetable[c][r]) > max) {
				max = strlen(timetable[c][r]);

			}

		}

	}
	//printf("%d", max);

	for (int i = 0; i < rows + 1; i++) {
		for (int x = 0; x < columns - 1; x++) {
			printf(" %s ", timetable[x][i]);
			fprintf(fp, " %s ", timetable[x][i]); // <--

			for (int z = 0; z < max - strlen(timetable[x][i]); z++) {
				printf(" ");
				fprintf(fp, " "); // <--

			}
			printf("|");
			fprintf(fp, "|"); // <--

		}
		printf(" %s\n", timetable[columns - 1][i]);
		fprintf(fp, " %s\n", timetable[columns - 1][i]); // <--
		
		for (int j = 0; j < max * columns + columns * 3 - 1; j++) { // long line
			printf("-");
			fprintf(fp, "-"); // <--

		}
		printf("\n");
		fprintf(fp, "\n"); // <--

	}

	fclose(fp);

}

char *get_file(char filename[]) {
	char* file;
	file = malloc(strlen("timetables/.timetable") + strlen(filename) + 1);
	file[0] = '\0';
	strcat(file, "timetables/");
	strcat(file, filename);
	strcat(file, ".timetable");

	return file;

}