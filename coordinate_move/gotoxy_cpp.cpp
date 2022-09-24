#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable:4996)

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80

void gotoxy(int x, int y);

int main()
{
	int getKey;
	int x = 0, y = 0;
	while (1) {
		system("cls");
		gotoxy(x, y);
		printf("@");
		getKey = getch();

		getKey = getch();
		switch (getKey) {
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			return 0;
		}

	}
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}