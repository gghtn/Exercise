#pragma once
#include "doublebuffer.h"

class CUser {
	int mTopScore, mScore;
	bool mbGameOver;
	int mUserX;
	const int mUserY;
	string mUserCar[4];
public:
	CUser();

	void SetGameOver() { mbGameOver = !mbGameOver; }
	void SetUserX(int num) { mUserX = num; }
};