#include"BaseAccount.h"

//���캯������ʼ���ڲ���Ա
BaseAccount::BaseAccount() {
	status = true;
	account = "NAN";
	password = "000000";
	userName = "NAN";
	IdNumber = "NAN";
	limit_of_each = 1000.0;
	limit_of_day = 5000.0;
}

//��������
void BaseAccount::setPassword(string p)
{
	password=p;
}

//�����˻�״̬
void BaseAccount::setStatus(bool a)
{
	status = a;
}

//��ȡ�˻�״̬
bool BaseAccount::getStatus()
{
	return status;
}

//��ȡÿ���޶�
double BaseAccount::getDayLimit()
{
	return limit_of_day;
}

//��ȡÿ���޶�
double BaseAccount::getEachLimit()
{
	return limit_of_each;
}



bool BaseAccount::ComparePassword(string p)
{
	if (p == password)
		return true;
	else
		return false;
}

bool BaseAccount::CompareAccount(string p)
{
	if (p == account)
		return true;
	else
		return false;
}

ostream& operator <<(ostream & os, const BaseAccount & a) {
	os << "Name:" << a.userName << endl << "Account:" << a.account << endl << "IdNumber:" << a.IdNumber << endl;
	return os;
}


