#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable:4996)

#define ENTER_KEY 13
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
int getKey, x, y;

//void gotoxy(int x, int y);
void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenPrint(int x, int y, char string);
void Render();

int main()
{
    ScreenInit();
    printf("@");

    while (1) {
        if (_kbhit) {
            if (getch() == ENTER_KEY) {
                system("cls");
                printf("���α׷� ����");
                break;
            }
            Render();
        }
    }
    return 0;
}

//void gotoxy(int x, int y) {
//    COORD pos = { x, y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}

//ȭ�� ���� �ʱ�ȭ
void ScreenInit()
{
    CONSOLE_CURSOR_INFO cci;

    // ȭ�� ���� 2���� �����.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // Ŀ���� �����.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

//Ȱ��ȭ�� ���ۿ� ��Ȱ��ȭ ���� ��ü
void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

//���۰� ȭ�鿡 ǥ�õǴ� ���� ��Ȱ��ȭ�� ���۸� ����� �Լ�
void ScreenClear()
{
    //��ǥ
    COORD Coor = { 0, 0 };
    //cpu�� �� ���� ó���� �� �ִ� �������� ũ�� ���� WORD
    //DWORD(unsigned long), bool(char), BOOL(int), BYTE(unsigned char), WORD(unsigned short), UINT(unsigned int)
    DWORD dw;
    //(���ϴ� ��, ���ϴ� ����(' '), ���ϴ� ����, ���ϴ� Ŀ��, ���̸� ��ȯ�� ��)
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 300 * 300, Coor, &dw);
}

//(x, y)��ǥ�� string ���
void ScreenPrint(int x, int y, char string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], &string, 1, &dw, NULL);
}


void Render()
{
    //��Ȱ�� ���۸� ����
    ScreenClear();

    switch (getch()) {
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
        break;
    }

    //��Ȱ�� ���ۿ� ���
    ScreenPrint(x, y, '@');
    //���۱�ü
    ScreenFlipping();
}