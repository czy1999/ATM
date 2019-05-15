#ifndef SA_H_
#define SA_H_
#include"BaseAccount.h"

/*存款账户类型*/
class SAccount:public BaseAccount{
private:
	double SMoney; //存款余额
public:
	//构造函数
	SAccount(string s);
	//获取余额
	double getSMoney();
	//存款操作
	void saveMoney(double a);
	//取款操作
	void dropMoney(double a);
	//输出操作符重载
	friend ostream& operator <<(ostream& os, const SAccount& a);
};

#endif //!SA_H_