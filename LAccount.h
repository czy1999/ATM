#ifndef LA_H_
#define LA_H_
#include"BaseAccount.h"

/*����˻�����*/

class LAccount :public BaseAccount {
private:
	double LMoney; //Ƿ���
	double creditlimit; //���ö��
public:
	//���캯��
	LAccount(string s);
	//��ȡǷ���
	double getLMoney();
	//��ȡ���ö��
	double getCreditLimit();
	//ȡ���
	void dropMoney(double a);
	//�����
	void returnMoney(double a);
	//������������
	friend ostream& operator <<(ostream& os, const LAccount& a);
};
#endif // !LA_H_
