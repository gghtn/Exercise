#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "ReadWriteFile.h"
#pragma warning(disable:4996)

#define MAX 100
#define FILE_NAME "charinfo.bin"
#define TURE 1
#define FLASE 0
#define YES 121
typedef int BOOL;

//typedef struct
//{
//	BOOL bIsLive;  // 생존 여부
//	int	nDamage;  // 공격 받은 정도
//	int	nLife;    // 생명
//} CHARACTER;

int main() {
	FILE* in;
	int live_character = 100, death_character, revive, avoid, total_death = 0, turn = 0;

	//죽은 캐릭터를 기록할 배열
	int* death = (int*)malloc(sizeof(int) * MAX);
	if (death == NULL) { return 0; }

	//캐릭터 생성
	CHARACTER* hero = (CHARACTER*)malloc(sizeof(CHARACTER) * MAX);
	if (hero == NULL) { return 0; }

	memset(death, 0, sizeof(int) * MAX);
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++) { //캐릭터 초기화
		hero[i].bIsLive = TURE;
		hero[i].nDamage = 0;
		hero[i].nLife = rand() % 51 + 50;
	}

	in = fopen(FILE_NAME, "rb");

	if (NULL == in) {}					//저장파일이 비어있을 경우	
	else {
		printf("저장파일을 불러오겠습니까?(Y/N)");
		if (getch() == YES) {
			__read(hero, death, in);	//파일 불러와서 값 저장
			fclose(in);
			for (int i = 0; i < MAX; i++) {
				if (death[i]) {
					total_death++;
					live_character--;
				}
			}
		}
	}


	while (1) {
		turn++;
		avoid = 0, death_character = 0, revive = 0;

		if (total_death >= 10) {

			int is_revive = total_death / 10;

			total_death -= is_revive;
			revive = is_revive;
			live_character += is_revive;


			while (is_revive) {
				int i = rand() % MAX;
				for (; i < MAX; i++) {
					if (death[i]) {
						hero[i].bIsLive = TURE;
						hero[i].nLife = rand() % 50 + 50;
						is_revive--;
						death[i] = 0;

						if (i == MAX - 1 && is_revive != 0) i = 0;	//99번까지 가도 부활을 다 못하면 i를 0으로 만든다.
						else if (is_revive == 0) break;
					}
				}

			}
		}


		for (int i = 0; i < MAX; i++) {
			hero[i].nDamage = 0;						//데미지 초기화
			if (hero[i].bIsLive) {
				hero[i].nDamage = rand() % 10;
				if (hero[i].nDamage == 0) avoid++;		//데미지가 0일 경우 회피+1
				else hero[i].nLife -= hero[i].nDamage;

				if (hero[i].nLife <= 0) {
					hero[i].nLife = 0;
					hero[i].bIsLive = FLASE;
					death[i] = 1;
					live_character--, death_character++, total_death++;
				}
			}
		}

		printf("TURN: %d\n", turn);

		for (int i = 0; i < MAX; i += 4) {
			for (int j = i; j < i + 4; j++) {
				if (hero[j].bIsLive) printf("  NO. %3d \u2665 데미지 %d 체력 %3d  |", j, hero[j].nDamage, hero[j].nLife);
				else printf("  NO. %3d \u2661 데미지 %d 체력 %3d  |", j, hero[j].nDamage, hero[j].nLife);
			}
			printf("\n");
		}
		printf("현재 생존 영웅의 수:%5d\t 현재 죽어있는 영웅의 수: %5d\n", live_character, total_death);
		printf("이번 턴에 부활한 수:%5d\t 이번 공격으로 죽은 영웅의 수:%2d\n", revive, death_character);
		printf("이번턴에 공격 받지 않은 영웅의 수: %d\n", avoid);


		printf("저장하고 게임을 종료하시겠습니까?(Y/N) ");
		if (getch() == YES) {
			__write(hero, death); //파일에 저장
			free(death);
			free(hero);
			return 0;
		}
	}

	free(death);
	free(hero);
}