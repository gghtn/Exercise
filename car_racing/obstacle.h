#pragma once
#include "object.h"

class CObstacle : public CObject {
public:
	CObstacle(int x) :CObject(x) {}

	void SetStr() { mObjectStr = "[�ܡܡܡܡܡܡܡ�]"; }

	void Rend(bool);

};

