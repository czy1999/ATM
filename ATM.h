#ifndef ATM_H_
#define ATM_H_
#include<vector>
#include"LAccount.h"
#include"SAccount.h"

/*
ATM类主要负责ATM程序的界面和数据操作，每次初始化时加载文件中的数据，
存入容器中。类中设计了交互程序，指导用户进行存取款、转账、修改密码
等操作。当程序操作完毕时，数据也会被写回文件中，以备下次读取
*/

class ATM{
private:
	//内部成员，两个vector容器分别存储两种账户
	vector<LAccount> LAccount_list;
	vector<SAccount> SAccount_list;
public:
	//构造函数，构造时读取用户数据
	ATM();

	//读取用户账户数据
	//参数：文件路径
	void Read_LAccount(string filepath);
	void Read_SAccount(string filepath);

	//保存用户数据到文件中
	//参数：两个路径，分别存入两种账户类型
	void Save_to_file(string filepath1, string filepath2);

	//查找账户，根据账户寻找用户	
	//参数account：需要进行查找的账户
	//返回值：若查找到，则返回该账户所在的位置，否则返回-1表示未找到
	int findaccount(string account);

	//验证账户密码功能
	//参数s：需要检验的账户
	//返回值：bool类型 是否通过密码验证
	bool checkPassword(BaseAccount& s);

	//修改账户密码功能
	//参数s：修改密码的账户
	void changePassword(BaseAccount& s);

	//转账功能函数
	//参数s：进行转账的账户
	void transfer(SAccount& s);

	//存还款功能函数
	//参数s：存款的账户
	void saveMoney(SAccount& s);
	void saveMoney(LAccount& s);

	//取款功能函数
	//参数s：取款的账户
	void dropMoney(SAccount& s);
	void dropMoney(LAccount& s);

	//用户功能面板,负责用户功能的选择
	//参数：要进行操作的账户
	void SAccount_progress(SAccount &s);
	void LAccount_progress(LAccount &l);

	//启动ATM程序
	void start();
};


#endif // !ATM
