#include"ATM.h"

/*
程序遵循了界面与数据隔离的原则，设计了账户类和ATM类

测试存款账号
6000123488888888888 123456
测试借款账号
9000123488888888888 123456
*/

int main() {
	//创建ATM实例
	ATM a;
	//开始运行
	a.start();
	return 0;
}