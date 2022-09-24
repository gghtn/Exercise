#define _CRT_SECURE_NO_WARNINGS
#define ENTER_KEY 13
#include <Windows.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h> // stdio.h - getch(), iostream - _getch()

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
int g_numofFPS;
clock_t CurTime, OldTime;
char* FPSTextInfo;

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
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

//���۸� ����
void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

//(x, y)��ǥ�� string ���
void ScreenPrint(int x, int y, char* string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

// 
void Render()
{
    ScreenClear();

    if (CurTime - OldTime >= 1000) // ��� �ڵ� 1��
    {
        //��°�(���ڿ� "FPS : %d")�� ���� FPSTextInfo�� ���� , ���x
        sprintf(FPSTextInfo, "FPS : %d", g_numofFPS);
        OldTime = CurTime;
        g_numofFPS = 0;
    }

    g_numofFPS++;
    ScreenPrint(0, 0, FPSTextInfo);
    ScreenFlipping();
}

void Release()
{
    delete[] FPSTextInfo;
}

int main()
{
    g_numofFPS = 0;
    FPSTextInfo = new char[128];
    memset(FPSTextInfo, '\0', 128);

    ScreenInit();

    OldTime = clock(); // �ð��� �����Ѵ�. 1�ʸ��� �����Ѵ�.

    while (1)
    {
        if (_kbhit()) {     //Ư��Ű�� ������
            if (_getch() == ENTER_KEY) break;    //����Ű�ϰ�� Ż��
        }
        CurTime = clock();
        Render();
    }

    Release();
    ScreenRelease();

    return 0;
}