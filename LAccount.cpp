#include "LAccount.h"

//构造函数
//参数s：账户信息的字符串
LAccount::LAccount(string s) {
	stringstream input(s);
	input >> account;
	input >> password;
	input >> userName;
	input >> IdNumber;
	input >> LMoney;
	input >> creditlimit;
}

//获取欠款额
double LAccount::getLMoney()
{
	return LMoney;
}

//获取信用额度
double LAccount::getCreditLimit()
{
	return creditlimit;
}

//取款函数
//参数a：取出的数量
void LAccount::dropMoney(double a)
{
	LMoney += a; // 欠款加上取款额
	limit_of_day -= a; // 当日限额减去取款额
	creditlimit -= a; // 信用额度改变
}

//还款函数
//参数a：还款数量
void LAccount::returnMoney(double a)
{
	LMoney -= a; //欠款减去还款额
	creditlimit += a; //信用额度加上还款额
}

//输出操作符重载
 ostream& operator <<(ostream& os, const LAccount& a) {
	os <<a.account<< " " << a.password << " " << a.userName <<" "<< a.IdNumber << " " << a.LMoney << " " << a.creditlimit;
	return os;
}