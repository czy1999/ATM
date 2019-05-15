#ifndef LA_H_
#define LA_H_
#include"BaseAccount.h"

/*存款账户类型*/

class LAccount :public BaseAccount {
private:
	double LMoney; //欠款额
	double creditlimit; //信用额度
public:
	//构造函数
	LAccount(string s);
	//获取欠款额
	double getLMoney();
	//获取信用额度
	double getCreditLimit();
	//取款函数
	void dropMoney(double a);
	//还款函数
	void returnMoney(double a);
	//输出运算符重载
	friend ostream& operator <<(ostream& os, const LAccount& a);
};
#endif // !LA_H_
