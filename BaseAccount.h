#ifndef BASE
#define BASE
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

/*�����˻�����*/
class BaseAccount {
protected:
	string account; //�˺�
	string userName; //����
	string IdNumber; //���֤
	string password; //����
	double limit_of_each; //ÿ���޶�
	double limit_of_day; //ÿ���޶�
	bool status; //�˻�״̬������/����
public:
	//���캯��
	BaseAccount();
	//��������
	void setPassword(string p);
	//�����˻�״̬
	void setStatus(bool a);
	//��ȡ�˻�״̬
	bool getStatus();
	//��ȡ���޶�
	double getDayLimit();
	//��ȡÿ���޶�
	double getEachLimit();
	//���������Ƿ�һ��
	bool ComparePassword(string p);
	//�����˻��Ƿ�һ��
	bool CompareAccount(string p);
	//������������
	friend ostream& operator <<(ostream& os, const BaseAccount& a);
};

#endif // !BASE