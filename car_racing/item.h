#pragma once
#include "object.h"

class CItem : public CObject {
	bool mbInvicible;
public:
	CItem(int x) : CObject(x) { mbInvicible = false; }

	void SetStr() { mObjectStr = "       (��)       "; }
	void SetInvicible() { mbInvicible = !mbInvicible; }
};