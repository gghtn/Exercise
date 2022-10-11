#pragma once
#include <iostream>
using namespace std;

class CObject {
	char* name;
	static int m_nNum;
	int m_nLife, m_nLength;
public:
	CObject() :name(NULL), m_nLife(0), m_nLength(0) {}
	CObject(const char* name, int life);
	CObject(const CObject& Other);
	~CObject();

	void operator=(const CObject&);

	pair<int, char*> strNum();

	void Display();

	////////to_string 사용 안할 시/////////
	int getNumLength();
	char* getNumStr();
};