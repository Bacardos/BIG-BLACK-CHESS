
#include <iostream>
#include <Windows.h>
void drawmenu();
void newGame();
typedef struct {
	char figure;
	int player;
} cell;
typedef struct {
	int x;
	int y;
} point;


using namespace std;
void movef(cell field[8][8], point start, point end, int* player);
void drawf(cell field[8][8]);
void playgame(cell field[8][8]);
bool checkmove(cell field[8][8], point start, point end, int* player);

int main()
{
	SetConsoleOutputCP(65001);
	drawmenu();
	return 0;
}
bool checkmove(cell field[8][8], point start, point end, int* player) {
	point moveVector;
	int anotherPlayer;
	*player == 1 ? anotherPlayer = 2 : anotherPlayer = 1;
	moveVector.x = end.x - start.x;
	moveVector.y = end.y - start.y;
	if (field[start.x][start.y].player == 0 || field[start.x][start.y].player != *player) {
		cout << "Incorrect player" << endl;
		return false;
	}
	if (field[start.x][start.y].player == field[end.x][end.y].player) {
		cout << "Incorrect move" << endl;
		return false;
	}
	switch (field[start.x][start.y].figure) {
	case 80:
		if (abs(moveVector.x) > 2 || abs(moveVector.y) > 1 || abs(moveVector.y) == 1 && field[end.x][end.y].player == 0 || abs(moveVector.x) == 2 && start.x != 1 && start.x != 6 || abs(moveVector.y) != 1 && field[end.x][end.y].player == anotherPlayer) {
			return false;
		}
		break;
	case 82:
		if (abs(moveVector.x) > 0 && abs(moveVector.y) > 0) {
			return false;
		}
		break;
	case 69:
		if (abs(moveVector.x) != abs(moveVector.y)) {
			return false;
		}
		break;
	case 81:
		if (abs(moveVector.x) != abs(moveVector.y) && (abs(moveVector.x) > 0 && abs(moveVector.y) > 0)) {
			return false;
		}
		break;
	case 75:
		if (abs(moveVector.x) != abs(moveVector.y) && abs(moveVector.x) > 0 && abs(moveVector.y) > 0 || abs(moveVector.x) > 1 || abs(moveVector.y) > 1) {
			return false;
		}
		break;
	case 72:
		if (sqrt(pow(moveVector.x, 2) + pow(moveVector.y, 2)) != sqrt(5)) {
			return false;
		}

	}
	return true;
}
void movef(cell field[8][8], point start, point end, int* player) {
	if (checkmove(field, start, end, player)) {
		field[end.x][end.y].figure = field[start.x][start.y].figure;
		field[end.x][end.y].player = field[start.x][start.y].player;
		field[start.x][start.y].figure = '0';
		field[start.x][start.y].player = 0;
		*player == 1 ? *player = 2 : *player = 1;
	}
	return;
}

void drawmenu() {
	int a;
	bool flag = false;
	while (flag == false) {

		cout << "1. New Game" << endl;
		cout << "2. Load Game" << endl;
		cout << "3. Save Game" << endl;
		cout << "4. Quit Game" << endl;

		cin >> a;
		switch (a) {
		case 1:
			newGame();
			flag = true;
			break;
		case 2:
			cout << "Load Game";
			flag = true;
			break;
		case 3:
			cout << "Save Game";
			flag = true;
			break;
		case 4:
			return;
		default:
			cout << "Please choose correct menu item \uE29994!" << endl;
		}
	}
}

void drawf(cell field[8][8]) {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (field[i][j].player == 1) {
				printf("\x1B[37m%c\033[0m ", field[i][j].figure);
			}
			else if (field[i][j].player == 2) {
				printf("\x1B[95m%c\033[0m ", field[i][j].figure);
			}
			else {
				printf("\x1B[36m%c\033[0m ", field[i][j].figure);
			}
		}
		cout << endl;
	}
}

void newGame() {
	int i, j;
	cell field[8][8];
	char data[8][8] = {
		{'R', 'H', 'E', 'Q', 'K', 'E', 'H', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{'0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{'R', 'H', 'E', 'Q', 'K', 'E', 'H', 'R'}
	};
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			field[i][j].figure = data[i][j];
			if (i < 2) {
				field[i][j].player = 2;
			}
			else if (i > 5) {
				field[i][j].player = 1;
			}
			else {
				field[i][j].player = 0;
			}
		}
	}
	playgame(field);

}
void playgame(cell field[8][8]) {
	point to, from;
	int currentPlayer = 1;
	to.x = 0;
	to.y = 0;
	from.x = 0;
	from.y = 0;
	while (to.x < 8 && to.y < 8 && from.x < 8 && from.y < 8) {
		cout << endl << endl;
		drawf(field);
		printf_s("Player %d turn\n", currentPlayer);
		cout << "Enter from coordinates" << endl;
		scanf_s("%d %d", &from.x, &from.y);
		if (from.x > 7 || from.y > 7) {
			return;
		}
		cout << "Enter to coordinates" << endl;
		scanf_s("%d %d", &to.x, &to.y);
		if (to.x > 7 || to.y > 7) {
			return;
		}
		movef(field, from, to, &currentPlayer);
	}
}