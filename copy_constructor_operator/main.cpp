#include <iostream>
#include <string>
#include "object.h"
using namespace std;

int main() {
	CObject ObjectOrg("¿µ¿õ", 100);
	ObjectOrg.Display();

	{
		CObject Object2(ObjectOrg);
		Object2.Display();
	}

	CObject Object3(ObjectOrg);
	Object3.Display();

	CObject Object4;
	Object4 = ObjectOrg;
	Object4.Display();

	return 0;
}