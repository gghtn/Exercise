#pragma once
#include "doublebuffer.h"

class CObject
{
protected:
	int mX, mY;
	bool mbCrash;
	string mObjectStr;
public:
	CObject(int x) { mX = x, mY = 0, mbCrash = false, mObjectStr = ""; }

	int GetX() { return mX; }
	int GetY() { return mY; }
	bool GetCrash() { return mbCrash; }

	void SetY(int num) { mY += num; }
	void SetCrash() { mbCrash = !mbCrash; }

	void Rend() {
		if (mbCrash) ScreenPrint(mX, mY, "");
		else {
			ScreenPrint(mX, mY, mObjectStr);
		}
	}
};