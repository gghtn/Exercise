#include "object.h"
#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

int CObject::m_nNum = 1;

CObject::CObject(const char* name, int life) {
	m_nLength = strlen(name);
	pair<int, char*> str = strNum();

	this->name = new char[m_nLength + str.first + 1];

	strcpy(this->name, name);
	strcat(this->name, str.second);

	m_nLife = life;

	delete[] str.second;

	cout << this << "-> 포인터 생성자 생성\n";
}

//복사생성자
CObject::CObject(const CObject& Other) {
	m_nNum++;
	m_nLife = Other.m_nLife;
	m_nLength = Other.m_nLength;
	pair<int, char*> str = strNum();

	this->name = new char[m_nLength + str.first + 1];
	memset(this->name, '\0', m_nLength + str.first + 1);
	strncat(this->name, Other.name, m_nLength);
	strcat(this->name, str.second);

	delete[] str.second;

	cout << this << "-> 복사 생성자\n";
}

//operator 복사
void CObject::operator=(const CObject& obj) {

	if (&obj == this) return;

	if (!name) {
		delete[] name;
		name = NULL;
	}
	m_nNum++;
	m_nLife = obj.m_nLife;
	m_nLength = obj.m_nLength;
	pair<int, char*> str = strNum();

	this->name = new char[m_nLength + str.first + 1];
	memset(this->name, '\0', m_nLength + str.first + 1);
	strncat(this->name, obj.name, m_nLength);
	strcat(this->name, str.second);

	delete[] str.second;

	cout << this << "-> operator복사\n";
}

CObject::~CObject() {
	delete[] name;
	m_nNum--;
	cout << this << "-> 소멸자\n\n";
}

//m_nNum의 자릿수와 char* 변형 리턴
pair<int, char*> CObject::strNum() {
	string str = to_string(m_nNum);
	int len = str.size();
	char* tmp = new char[len + 1];
	for (unsigned int i = 0; i < len; i++) {
		*(tmp + i) = str[i];
	}
	*(tmp + len) = '\0';

	pair<int, char*> result;
	result.first = str.size();
	result.second = tmp;

	return result;
}

void CObject::Display() {
	cout << "이름: " << name << "  생명치: " << m_nLife << "  일련번호: " << m_nNum << "\n\n";
}



////////to_string 사용 안할 시/////////
int CObject::getNumLength() {
	int result = 1;
	int num = m_nNum;
	while (num / 10) {
		result++;
		num /= 10;
	}
	return result;
}
char* CObject::getNumStr() {
	int nLen = getNumLength();
	int num = m_nNum;
	char* result = new char[nLen + 1];
	for (int i = nLen - 1; i >= 0; i--) {
		result[i] = num % 10 + '0';
		num /= 10;
	}
	result[nLen] = '\0';

	return result;
}
