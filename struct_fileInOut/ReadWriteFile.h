#include <stdio.h>
#pragma warning(disable:4996)
#define MAX 100
#define FILE_NAME "charinfo.bin"

typedef int BOOL;
typedef struct
{
	BOOL bIsLive;  // ���� ����
	int	nDamage;  // ���� ���� ����
	int	nLife;    // ����
} CHARACTER;

void __write(CHARACTER* hero, int* death);

void __read(CHARACTER* hero, int* death, FILE* in);