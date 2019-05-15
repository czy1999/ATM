#ifndef SA_H_
#define SA_H_
#include"BaseAccount.h"

/*����˻�����*/
class SAccount:public BaseAccount{
private:
	double SMoney; //������
public:
	//���캯��
	SAccount(string s);
	//��ȡ���
	double getSMoney();
	//������
	void saveMoney(double a);
	//ȡ�����
	void dropMoney(double a);
	//�������������
	friend ostream& operator <<(ostream& os, const SAccount& a);
};

#endif //!SA_H_