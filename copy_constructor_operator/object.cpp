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

	cout << this << "-> ������ ������ ����\n";
}

//���������
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

	cout << this << "-> ���� ������\n";
}

//operator ����
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

	cout << this << "-> operator����\n";
}

CObject::~CObject() {
	delete[] name;
	m_nNum--;
	cout << this << "-> �Ҹ���\n\n";
}

//m_nNum�� �ڸ����� char* ���� ����
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
	cout << "�̸�: " << name << "  ����ġ: " << m_nLife << "  �Ϸù�ȣ: " << m_nNum << "\n\n";
}



////////to_string ��� ���� ��/////////
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
