#include "obstacle.h"

void CObstacle::Rend(bool invincible) {
	if (mbCrash) {
		if (invincible) {		//������ ������ ���
			mObjectStr = "[�ܡ�        �ܡ�]";
			ScreenPrint(mX, mY, mObjectStr);
		}
		else {
			ScreenPrint(mX, mY, mObjectStr);
		}
	}
}