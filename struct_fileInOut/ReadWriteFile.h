#include <stdio.h>
#pragma warning(disable:4996)
#define MAX 100
#define FILE_NAME "charinfo.bin"

typedef int BOOL;
typedef struct
{
	BOOL bIsLive;  // 생존 여부
	int	nDamage;  // 공격 받은 정도
	int	nLife;    // 생명
} CHARACTER;

void __write(CHARACTER* hero, int* death);

void __read(CHARACTER* hero, int* death, FILE* in);