#include<iostream>
#include <fstream>
#include<string>
#include"ATM.h"
using namespace std;

//ATM构造函数，读取数据
ATM::ATM()
{
	//读取数据文件
	Read_LAccount("LAccount.txt");
	Read_SAccount("SAccount.txt");
}

//读取文件中的LAccount账户
//参数：文件路径
void ATM::Read_LAccount(string filepath)
{
	ifstream input(filepath, ios::in);
	if (!input)
	{
		cerr << "Open input file error!" << endl;
		exit(-1);
	}
	string s;
	//循环读入，放入vector中
	while (getline(input, s))
	{
		LAccount temp(s);
		LAccount_list.push_back(temp);
	}
}

//读取文件中的SAccount账户
//参数：文件路径
void ATM::Read_SAccount(string filepath)
{
	ifstream input(filepath, ios::in);
	if (!input)
	{
		cerr << "Open input file error!" << endl;
		exit(-1);
	}
	string s;
	//循环读入，放入vector中
	while (getline(input, s))
	{
		SAccount temp(s);
		SAccount_list.push_back(temp);
	}
}

//将账户信息存储到文件中
//参数：两个路径，分别存入两种账户类型
void ATM::Save_to_file(string LAccountpath, string SAccountpath)
{
	//打开两个文件
	ofstream file1(LAccountpath);
	ofstream file2(SAccountpath);
	if (file1.is_open()&& file2.is_open())
	{
		for (unsigned int i = 0; i < LAccount_list.size(); i++)
			file1 << LAccount_list.at(i) << endl;

		for (unsigned int i = 0; i < SAccount_list.size(); i++)
			file2 << SAccount_list.at(i) << endl;

		file1.close();
		file2.close();
		cout << "保存成功！";
	}
	else
		cout << "Open file failed!" << endl;

}

//查找账户函数
//参数account：需要进行查找的账户
//返回值：若查找到，则返回该账户所在的位置，否则返回-1表示未找到
int ATM::findaccount(string account)
{	
	//在LAccount中找
	int flag = 0;
	for (unsigned int i = 0; i < LAccount_list.size(); i++) {
		if (LAccount_list.at(i).CompareAccount(account)) {
			flag = 1;
			return i;
		}
	}

	//在SAccount中查找
	for (unsigned int i = 0; i < SAccount_list.size(); i++) {
		if (SAccount_list.at(i).CompareAccount(account)) {
			flag = 1;
			return i;
		}
	}
	//若没找到，输出错误信息
	if (!flag) {
		cout << "该账户不存在，请重新输入！" << endl;
		return -1;
	}
}

//转账功能
//参数s：进行转账的账户
void ATM::transfer(SAccount& s)
{
	int n = -1;
	double transfer_money;
	string receive,receive_2;//收款账户
	//获取收款账户
	while (n==-1) {
		cout << "请输入转账账户：" ;
		cin >> receive;
		n = findaccount(receive);
		cout << "请再次输入转账账户：";
		cin >> receive_2;
		if (receive!=receive_2)
			cout << "两次输入的账户不一致，请重新输入！";
	}
	//获取转账额度
	while (1) {
		cout << "请输入转账数额：";
		cin >> transfer_money;

		//判断转账数额是否合法
		if (transfer_money <= 0.0) {
			cout << "转账数额必须大于0元，请重新输入!" << endl;
			continue;
		}

		//判断是否余额不足
		if (s.getSMoney() - transfer_money < 0) {
			cout << "余额不足，转出失败，请重新输入！" << endl;
			continue;
		}

		//开始转账操作
		s.dropMoney(transfer_money); //本账户先减去转账额
		if (receive.at(0) == '6')	//转入所输入账户，6开头表示是存款账户
			SAccount_list.at(n).saveMoney(transfer_money);
		else
			LAccount_list.at(n).returnMoney(transfer_money);
		cout << "转账" << transfer_money << "元成功，账户余额为" << s.getSMoney() << "元" << endl;
		break;
	}
}

//存款账户的存款函数
//参数s：存款的账户
void ATM::saveMoney(SAccount& s)
{

	while (1) {
		cout << "请输入存款数额：" ;
		int smoney;
		cin >> smoney;
		if (smoney % 100 == 0) {
			s.saveMoney(smoney);//调用SAccount的还款方法，进行数据操作
			cout << "存入" << smoney << "元成功! 存入后余额为" << s.getSMoney() << "元。" << endl;
			break;
		}
		else
			cout << "必须存入100的整数额，请重新存入。" << endl;
	}
}

//借款账户的还款函数
//参数s：还款的账户
void ATM::saveMoney(LAccount& s)
{
	while (1) {
		cout << "请输入还款数额：" ;
		int smoney;
		cin >> smoney;
		if (smoney % 100 == 0) {
			s.returnMoney(smoney);//调用LAccount的还款方法，进行数据操作
			cout << "还款" << smoney << "元成功! 还入后欠款为" << s.getLMoney() << "元。" << endl;
			break;
		}
		else
			cout << "必须存入100的整数额，请重新存入。" << endl;
	}
}

//存款账户的取款函数
//参数s：取款的账户
void ATM::dropMoney(SAccount& s)
{
	while (1) {
		cout << "请输入取款数额：";
		int smoney;
		cin >> smoney;

		//超出单笔限额，重新输入
		if (smoney > s.getEachLimit()) {
			cout << "取款超出每笔限额！请重新输入。" << endl;
			continue;
		}

		//超出当日限额，重新输入
		if (smoney > s.getDayLimit()) {
			cout << "取款超出当日限额！请重新输入。" << endl;
			continue;
		}

		//不是100的整数，重新输入
		if (smoney % 100 != 0) {
			cout << "取出必须100的整数额，请重新输入。" << endl;
			continue;
		}

		//超出余额，重新输入
		if (s.getSMoney() - smoney < 0) {
			cout << "余额不足，请重新输入。" << endl;
			continue;
		}

		//进行取款操作
		s.dropMoney(smoney); // 余额减去取款额
		cout << "取出" << smoney << "元成功! 剩余余额为" << s.getSMoney()<< "元。" << endl;
		break;
	}

}

//借款账户的取款函数
//参数l：取款的账户
void ATM::dropMoney(LAccount& l)
{
	while (1) {
		cout << "请输入取款数额：" << endl;
		int smoney;
		cin >> smoney;

		//超出单笔限额，重新输入
		if (smoney > l.getEachLimit()) {
			cout << "取款超出每笔限额！请重新输入。" << endl;
			continue;
		}

		//超出当日限额，重新输入
		if (smoney > l.getDayLimit()) {
			cout << "取款超出当日限额！请重新输入。" << endl;
			continue;
		}

		//不是100的整数，重新输入
		if (smoney % 100 != 0) {
			cout << "取出必须100的整数额，请重新输入。" << endl;
			continue;
		}

		//超出信用额度，重新输入
		if (smoney > l.getCreditLimit()) {
			cout << "取款超出额度，请重新输入。" << endl;
			continue;
		}

		//进行取款操作
		l.dropMoney(smoney); // 余额减去取款额
		cout << "取出" << smoney << "元成功! 当前欠款为" << l.getLMoney() << "元。" << endl;
		break;
	}
}

//检验密码函数
//参数s：需要检验的账户
//返回值：bool类型 是否通过密码验证
bool ATM::checkPassword(BaseAccount& s)
{
	string p;
	int wrongCount = 0;
	while (1) {
		if (s.getStatus()) {
			cout << "请输入六位数字密码：";
			cin >> p;
			if (s.ComparePassword(p)) {
				// 错误次数清零
				wrongCount = 0;
				cout << "登陆成功！" << endl;
				return true;
			}
			else {
				// 错误次数增加
				wrongCount++;
				// 若错误超过三次，冻结账号
				cout << "密码错误，请重新输入！" << endl;
				if (wrongCount >= 3)
					s.setStatus(false);
			}
		}
		else {
			cout << "错误次数过多，你的账号已被冻结。" << endl;
			return false;
		}
	}
}

//修改密码函数
//参数s：所要修改的账户
void ATM::changePassword(BaseAccount& s)
{
	string newpassword;
	while (1) {
		cout << "请输入新密码：";
		int flag = 1;
		cin >> newpassword;
		//判断输入是否都是数字
		for (int i = 0; i < newpassword.size(); i++)
		{
			int tmp = (int)newpassword[i];
			if (newpassword.size() == 6 && tmp >= 48 && tmp <= 57)
			{
				continue;
			}
			else
			{
				cout << "密码必须为六位数字,请重新输入密码！" << endl;
				flag = 0;
				break;
			}
		}

		//如果首次输入的密码通过检验，则进行第二次验证
		//判断两次输入是否一致
		if (flag) {
			cout << "请再次输入新密码：";
			string newpassword2;
			cin >> newpassword2;
			if (newpassword2 == newpassword) {
				s.setPassword(newpassword);
				cout << "密码修改成功！" << endl;
				break;
			}
			else
				cout << "两次输入密码不一致，请重新输入！" << endl;
		}
	}
}

//存款账户的功能面板，负责用户功能的选择
void ATM::SAccount_progress(SAccount &s)
{
	//检验密码
	if (!checkPassword(s))
		return;
	int n;
	cout << "欢 迎 使 用 ATM 自 助 存 取 款 机" << endl;
	cout << endl;
	cout << "   请输入相应数字选择操作：" << endl;
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "-    0  退卡              -" << endl;
	cout << "-    1  查询余额          -" << endl;
	cout << "-    2  存款              -" << endl;
	cout << "-    3  取款              -" << endl;
	cout << "-    4  转账              -" << endl;
	cout << "-    5  修改密码          -" << endl;
	cout << "----------------------------" << endl;
	cout << endl;
	while (1) {
		cout << "请输入操作：";
		cin >> n;
		//switch选择功能
		switch (n)
		{
		case 0:
			Save_to_file("LAccount.txt", "SAccount.txt"); //退出时保存文件
			cout << "退卡成功，请收好卡片，欢迎您的下次使用~" << endl;
			return;
		case 1:
			cout << "【余额查询】"  << endl;
			cout << "您的余额为：" << s.getSMoney() << endl;
			break;
		case 2:
			cout << "【存款】" << endl;
			saveMoney(s);
			break;
		case 3:
			cout << "【取款】" << endl;
			dropMoney(s);
			break;
		case 4:
			cout << "【转账】" << endl;
			transfer(s);
			break;
		case 5:
			cout << "【修改密码】" << endl;
			changePassword(s);
			break;
		default:
			cout << "输入有误，请重新选择。"<<endl;
			break;
		}
	}

}

//借款账户的功能面板，负责用户功能的选择
void ATM::LAccount_progress(LAccount &l)
{
	//检查密码
	checkPassword(l);
	int n;
	cout << "欢 迎 使 用 ATM 自 助 存 取 款 机" << endl;
	cout << endl;
	cout << "   请输入相应数字选择操作：" << endl;
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "-    0  退卡              -" << endl;
	cout << "-    1  查询欠款          -" << endl;
	cout << "-    2  还款              -" << endl;
	cout << "-    3  取款              -" << endl;
	cout << "-    4  修改密码          -" << endl;
	cout << "----------------------------" << endl;
	cout << endl;
	while (1) {
		cout << "请输入操作：";
		cin >> n;
		//switch选择功能
		switch (n)
		{
		case 0:
			Save_to_file("LAccount.txt","SAccount.txt");
			cout << "退卡成功，请收好卡片，欢迎您的下次使用~" << endl;
			return;
		case 1:
			cout << "【欠款查询】" << endl;
			cout << "您的欠款为：" << l.getLMoney() << endl;
			cout << "剩余额度为：" << l.getCreditLimit()<<endl;
			break;
		case 2:
			cout << "【还款】" << endl;
			saveMoney(l);
			break;
		case 3:
			cout << "【取钱】" << endl;
			dropMoney(l);
			break;
		case 4:
			cout << "【修改密码】" << endl;
			changePassword(l);
			break;
		default:
			cout << "输入有误，请重新选择：";
			break;
		}
	}

}

//ATM开始运行，负责插卡并且判断账户类型
void ATM::start()
{
	while (1) {
		cout << "★☆★☆★☆★☆★☆欢迎使用本银行ATM存取款机☆★☆★☆★☆★☆★" << endl;
		int n = -1;
		string p;
		while (n == -1) {
			cout << "请输入您的卡号(输入q退出):";
			cin >> p;
			//如果是q则退出程序
			if (p == "q") {
				exit(0);
			}
			//找到账户的标号n
			n = findaccount(p);
		}
		//若是储蓄卡则加载储蓄卡程序界面，负责加载信用卡界面
		if (p.at(0) == '6')
			SAccount_progress(SAccount_list.at(n));
		else
			LAccount_progress(LAccount_list.at(n));
	}
}



