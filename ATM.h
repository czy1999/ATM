#ifndef ATM_H_
#define ATM_H_
#include<vector>
#include"LAccount.h"
#include"SAccount.h"

/*
ATM����Ҫ����ATM����Ľ�������ݲ�����ÿ�γ�ʼ��ʱ�����ļ��е����ݣ�
���������С���������˽�������ָ���û����д�ȡ�ת�ˡ��޸�����
�Ȳ�����������������ʱ������Ҳ�ᱻд���ļ��У��Ա��´ζ�ȡ
*/

class ATM{
private:
	//�ڲ���Ա������vector�����ֱ�洢�����˻�
	vector<LAccount> LAccount_list;
	vector<SAccount> SAccount_list;
public:
	//���캯��������ʱ��ȡ�û�����
	ATM();

	//��ȡ�û��˻�����
	//�������ļ�·��
	void Read_LAccount(string filepath);
	void Read_SAccount(string filepath);

	//�����û����ݵ��ļ���
	//����������·�����ֱ���������˻�����
	void Save_to_file(string filepath1, string filepath2);

	//�����˻��������˻�Ѱ���û�	
	//����account����Ҫ���в��ҵ��˻�
	//����ֵ�������ҵ����򷵻ظ��˻����ڵ�λ�ã����򷵻�-1��ʾδ�ҵ�
	int findaccount(string account);

	//��֤�˻����빦��
	//����s����Ҫ������˻�
	//����ֵ��bool���� �Ƿ�ͨ��������֤
	bool checkPassword(BaseAccount& s);

	//�޸��˻����빦��
	//����s���޸�������˻�
	void changePassword(BaseAccount& s);

	//ת�˹��ܺ���
	//����s������ת�˵��˻�
	void transfer(SAccount& s);

	//�滹��ܺ���
	//����s�������˻�
	void saveMoney(SAccount& s);
	void saveMoney(LAccount& s);

	//ȡ��ܺ���
	//����s��ȡ����˻�
	void dropMoney(SAccount& s);
	void dropMoney(LAccount& s);

	//�û��������,�����û����ܵ�ѡ��
	//������Ҫ���в������˻�
	void SAccount_progress(SAccount &s);
	void LAccount_progress(LAccount &l);

	//����ATM����
	void start();
};


#endif // !ATM
