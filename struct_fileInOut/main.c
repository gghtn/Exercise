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
//	BOOL bIsLive;  // ���� ����
//	int	nDamage;  // ���� ���� ����
//	int	nLife;    // ����
//} CHARACTER;

int main() {
	FILE* in;
	int live_character = 100, death_character, revive, avoid, total_death = 0, turn = 0;

	//���� ĳ���͸� ����� �迭
	int* death = (int*)malloc(sizeof(int) * MAX);
	if (death == NULL) { return 0; }

	//ĳ���� ����
	CHARACTER* hero = (CHARACTER*)malloc(sizeof(CHARACTER) * MAX);
	if (hero == NULL) { return 0; }

	memset(death, 0, sizeof(int) * MAX);
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++) { //ĳ���� �ʱ�ȭ
		hero[i].bIsLive = TURE;
		hero[i].nDamage = 0;
		hero[i].nLife = rand() % 51 + 50;
	}

	in = fopen(FILE_NAME, "rb");

	if (NULL == in) {}					//���������� ������� ���	
	else {
		printf("���������� �ҷ����ڽ��ϱ�?(Y/N)");
		if (getch() == YES) {
			__read(hero, death, in);	//���� �ҷ��ͼ� �� ����
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

						if (i == MAX - 1 && is_revive != 0) i = 0;	//99������ ���� ��Ȱ�� �� ���ϸ� i�� 0���� �����.
						else if (is_revive == 0) break;
					}
				}

			}
		}


		for (int i = 0; i < MAX; i++) {
			hero[i].nDamage = 0;						//������ �ʱ�ȭ
			if (hero[i].bIsLive) {
				hero[i].nDamage = rand() % 10;
				if (hero[i].nDamage == 0) avoid++;		//�������� 0�� ��� ȸ��+1
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
				if (hero[j].bIsLive) printf("  NO. %3d \u2665 ������ %d ü�� %3d  |", j, hero[j].nDamage, hero[j].nLife);
				else printf("  NO. %3d \u2661 ������ %d ü�� %3d  |", j, hero[j].nDamage, hero[j].nLife);
			}
			printf("\n");
		}
		printf("���� ���� ������ ��:%5d\t ���� �׾��ִ� ������ ��: %5d\n", live_character, total_death);
		printf("�̹� �Ͽ� ��Ȱ�� ��:%5d\t �̹� �������� ���� ������ ��:%2d\n", revive, death_character);
		printf("�̹��Ͽ� ���� ���� ���� ������ ��: %d\n", avoid);


		printf("�����ϰ� ������ �����Ͻðڽ��ϱ�?(Y/N) ");
		if (getch() == YES) {
			__write(hero, death); //���Ͽ� ����
			free(death);
			free(hero);
			return 0;
		}
	}

	free(death);
	free(hero);
}