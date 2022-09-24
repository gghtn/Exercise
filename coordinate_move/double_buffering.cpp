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

//화면 버퍼 초기화
void ScreenInit()
{
    CONSOLE_CURSOR_INFO cci;

    // 화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 커서를 숨긴다.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

//활성화된 버퍼와 비활성화 버퍼 교체
void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

//버퍼가 화면에 표시되는 동안 비활성화된 버퍼를 지우는 함수
void ScreenClear()
{
    //좌표
    COORD Coor = { 0, 0 };
    //cpu가 한 번에 처리할 수 있는 데이터의 크기 단위 WORD
    //DWORD(unsigned long), bool(char), BOOL(int), BYTE(unsigned char), WORD(unsigned short), UINT(unsigned int)
    DWORD dw;
    //(원하는 곳, 원하는 문자(' '), 원하는 넓이, 원하는 커서, 넓이를 반환할 곳)
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

//버퍼를 해제
void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

//(x, y)좌표에 string 출력
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

    if (CurTime - OldTime >= 1000) // 출력 코드 1초
    {
        //출력값(문자열 "FPS : %d")을 변수 FPSTextInfo에 저장 , 출력x
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

    OldTime = clock(); // 시간을 측정한다. 1초마다 갱신한다.

    while (1)
    {
        if (_kbhit()) {     //특정키가 눌리면
            if (_getch() == ENTER_KEY) break;    //엔터키일경우 탈출
        }
        CurTime = clock();
        Render();
    }

    Release();
    ScreenRelease();

    return 0;
}