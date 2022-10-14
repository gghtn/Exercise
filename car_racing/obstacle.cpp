#include "obstacle.h"

void CObstacle::Rend(bool invincible) {
	if (mbCrash) {
		if (invincible) {		//蜡历啊 公利老 版快
			mObjectStr = "[≤≤        ≤≤]";
			ScreenPrint(mX, mY, mObjectStr);
		}
		else {
			ScreenPrint(mX, mY, mObjectStr);
		}
	}
}