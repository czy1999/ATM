#include "SAccount.h"

//���캯��
//����s:�˻����ݵ��ַ���
SAccount::SAccount(string s) {
	stringstream input(s);
	input >> account;
	input >> password;
	input >> userName;
	input >> IdNumber;
	input >> SMoney;
}

//��ȡ���
double SAccount::getSMoney()
{
	return SMoney;
}

//������
//����a:���������
void SAccount::saveMoney(double a)
{
	SMoney += a;
}

//ȡǮ����
//����a��ȡ��������
void SAccount::dropMoney(double a)
{
		SMoney -= a; //����ȥ����
		limit_of_day -= a; //���޶��ȥ����
}

//�������������
ostream& operator <<(ostream& os, const SAccount& a) {
	os << a.account << " " << a.password << " " << a.userName << " " << a.IdNumber << " " << a.SMoney ;

	return os;
}