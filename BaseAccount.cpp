#include"BaseAccount.h"

//构造函数，初始化内部成员
BaseAccount::BaseAccount() {
	status = true;
	account = "NAN";
	password = "000000";
	userName = "NAN";
	IdNumber = "NAN";
	limit_of_each = 1000.0;
	limit_of_day = 5000.0;
}

//设置密码
void BaseAccount::setPassword(string p)
{
	password=p;
}

//设置账户状态
void BaseAccount::setStatus(bool a)
{
	status = a;
}

//获取账户状态
bool BaseAccount::getStatus()
{
	return status;
}

//获取每日限额
double BaseAccount::getDayLimit()
{
	return limit_of_day;
}

//获取每笔限额
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


