#include "LAccount.h"

//���캯��
//����s���˻���Ϣ���ַ���
LAccount::LAccount(string s) {
	stringstream input(s);
	input >> account;
	input >> password;
	input >> userName;
	input >> IdNumber;
	input >> LMoney;
	input >> creditlimit;
}

//��ȡǷ���
double LAccount::getLMoney()
{
	return LMoney;
}

//��ȡ���ö��
double LAccount::getCreditLimit()
{
	return creditlimit;
}

//ȡ���
//����a��ȡ��������
void LAccount::dropMoney(double a)
{
	LMoney += a; // Ƿ�����ȡ���
	limit_of_day -= a; // �����޶��ȥȡ���
	creditlimit -= a; // ���ö�ȸı�
}

//�����
//����a����������
void LAccount::returnMoney(double a)
{
	LMoney -= a; //Ƿ���ȥ�����
	creditlimit += a; //���ö�ȼ��ϻ����
}

//�������������
 ostream& operator <<(ostream& os, const LAccount& a) {
	os <<a.account<< " " << a.password << " " << a.userName <<" "<< a.IdNumber << " " << a.LMoney << " " << a.creditlimit;
	return os;
}