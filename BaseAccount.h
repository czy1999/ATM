#ifndef BASE
#define BASE
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

/*基础账户类型*/
class BaseAccount {
protected:
	string account; //账号
	string userName; //姓名
	string IdNumber; //身份证
	string password; //密码
	double limit_of_each; //每笔限额
	double limit_of_day; //每日限额
	bool status; //账户状态：冻结/正常
public:
	//构造函数
	BaseAccount();
	//设置密码
	void setPassword(string p);
	//设置账户状态
	void setStatus(bool a);
	//获取账户状态
	bool getStatus();
	//获取日限额
	double getDayLimit();
	//获取每笔限额
	double getEachLimit();
	//检验密码是否一致
	bool ComparePassword(string p);
	//检验账户是否一致
	bool CompareAccount(string p);
	//输出运算符重载
	friend ostream& operator <<(ostream& os, const BaseAccount& a);
};

#endif // !BASE