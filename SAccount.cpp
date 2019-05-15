#include "SAccount.h"

//构造函数
//参数s:账户数据的字符串
SAccount::SAccount(string s) {
	stringstream input(s);
	input >> account;
	input >> password;
	input >> userName;
	input >> IdNumber;
	input >> SMoney;
}

//获取余额
double SAccount::getSMoney()
{
	return SMoney;
}

//存款操作
//参数a:存入的数额
void SAccount::saveMoney(double a)
{
	SMoney += a;
}

//取钱操作
//参数a：取出的数额
void SAccount::dropMoney(double a)
{
		SMoney -= a; //余额减去数额
		limit_of_day -= a; //日限额减去数额
}

//输出操作符重载
ostream& operator <<(ostream& os, const SAccount& a) {
	os << a.account << " " << a.password << " " << a.userName << " " << a.IdNumber << " " << a.SMoney ;

	return os;
}