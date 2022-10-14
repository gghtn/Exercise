#include "user.h"

CUser::CUser() :mUserY(45) {
	mTopScore = 0, mScore = 0;
	mbGameOver = false;
	mUserX = 26;
	mUserCar[0] = "¦£¦¡¦¤";
	mUserCar[1] = "¡Û  ¡Û";
	mUserCar[2] = "¦¢  ¦¢";
	mUserCar[3] = "¡Û¦¡¡Û";

}