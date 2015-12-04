#include <stdio.h>
#include <string.h>

int main() {
	int cnt = 0;
	bool line = false;
	char puzzle[5][7];

	while (gets(puzzle[0])) {

		if (strcmp(puzzle[0], "Z") == 0)
			return 0;

		gets(puzzle[1]);
		gets(puzzle[2]);
		gets(puzzle[3]);
		gets(puzzle[4]);

		int blank_x;
		int blank_y;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (puzzle[i][j] == ' ') {
					blank_x = i;
					blank_y = j;
					i = j = 5;
				}
			}
		}

		char step[1000];
		bool valid = true;
		bool exit_koro = false;

		while (!exit_koro && gets(step)) {

			for (int i = 0; step[i] != 0; i++) {

				if (step[i] == '0' || !valid) {
					exit_koro = true;
					break;
				}

				switch (step[i]) {
				case 'A':
					if (blank_x == 0)
						valid = false;
					else {
						puzzle[blank_x][blank_y] = puzzle[blank_x - 1][blank_y];
						puzzle[blank_x - 1][blank_y] = ' ';
						blank_x--;
					}
					break;

				case 'B':
					if (blank_x == 4)
						valid = false;
					else {
						puzzle[blank_x][blank_y] = puzzle[blank_x + 1][blank_y];
						puzzle[blank_x + 1][blank_y] = ' ';
						blank_x++;
					}
					break;

				case 'R':
					if (blank_y == 4)
						valid = false;
					else {
						puzzle[blank_x][blank_y] = puzzle[blank_x][blank_y + 1];
						puzzle[blank_x][blank_y + 1] = ' ';
						blank_y++;
					}
					break;

				case 'L':
					if (blank_y == 0)
						valid = false;
					else {
						puzzle[blank_x][blank_y] = puzzle[blank_x][blank_y - 1];
						puzzle[blank_x][blank_y - 1] = ' ';
						blank_y--;
					}
					break;
				}
			}
		}

		if (line)
			printf("\n");
		line = true;

		printf("Puzzle #%d:\n", ++cnt);

		if (valid) {
			for (int i = 0; i < 5; i++) {
				printf("%c %c %c %c %c\n", puzzle[i][0], puzzle[i][1],
					puzzle[i][2], puzzle[i][3], puzzle[i][4]);
			}
		}

		else
			printf("This puzzle has no final configuration.\n");

	}

	return 0;
}
