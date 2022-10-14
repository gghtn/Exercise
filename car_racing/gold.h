#pragma once
#include "object.h"

class CGold : public CObject {
	int mGold;
public:
	CGold(int x) : CObject(x) { mGold = 0; }

	void SetStr() { mObjectStr = "       ($$)       "; }

	void SetGold() { mGold++; }
};