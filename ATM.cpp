#include<iostream>
#include <fstream>
#include<string>
#include"ATM.h"
using namespace std;

//ATM���캯������ȡ����
ATM::ATM()
{
	//��ȡ�����ļ�
	Read_LAccount("LAccount.txt");
	Read_SAccount("SAccount.txt");
}

//��ȡ�ļ��е�LAccount�˻�
//�������ļ�·��
void ATM::Read_LAccount(string filepath)
{
	ifstream input(filepath, ios::in);
	if (!input)
	{
		cerr << "Open input file error!" << endl;
		exit(-1);
	}
	string s;
	//ѭ�����룬����vector��
	while (getline(input, s))
	{
		LAccount temp(s);
		LAccount_list.push_back(temp);
	}
}

//��ȡ�ļ��е�SAccount�˻�
//�������ļ�·��
void ATM::Read_SAccount(string filepath)
{
	ifstream input(filepath, ios::in);
	if (!input)
	{
		cerr << "Open input file error!" << endl;
		exit(-1);
	}
	string s;
	//ѭ�����룬����vector��
	while (getline(input, s))
	{
		SAccount temp(s);
		SAccount_list.push_back(temp);
	}
}

//���˻���Ϣ�洢���ļ���
//����������·�����ֱ���������˻�����
void ATM::Save_to_file(string LAccountpath, string SAccountpath)
{
	//�������ļ�
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
		cout << "����ɹ���";
	}
	else
		cout << "Open file failed!" << endl;

}

//�����˻�����
//����account����Ҫ���в��ҵ��˻�
//����ֵ�������ҵ����򷵻ظ��˻����ڵ�λ�ã����򷵻�-1��ʾδ�ҵ�
int ATM::findaccount(string account)
{	
	//��LAccount����
	int flag = 0;
	for (unsigned int i = 0; i < LAccount_list.size(); i++) {
		if (LAccount_list.at(i).CompareAccount(account)) {
			flag = 1;
			return i;
		}
	}

	//��SAccount�в���
	for (unsigned int i = 0; i < SAccount_list.size(); i++) {
		if (SAccount_list.at(i).CompareAccount(account)) {
			flag = 1;
			return i;
		}
	}
	//��û�ҵ������������Ϣ
	if (!flag) {
		cout << "���˻������ڣ����������룡" << endl;
		return -1;
	}
}

//ת�˹���
//����s������ת�˵��˻�
void ATM::transfer(SAccount& s)
{
	int n = -1;
	double transfer_money;
	string receive,receive_2;//�տ��˻�
	//��ȡ�տ��˻�
	while (n==-1) {
		cout << "������ת���˻���" ;
		cin >> receive;
		n = findaccount(receive);
		cout << "���ٴ�����ת���˻���";
		cin >> receive_2;
		if (receive!=receive_2)
			cout << "����������˻���һ�£����������룡";
	}
	//��ȡת�˶��
	while (1) {
		cout << "������ת�����";
		cin >> transfer_money;

		//�ж�ת�������Ƿ�Ϸ�
		if (transfer_money <= 0.0) {
			cout << "ת������������0Ԫ������������!" << endl;
			continue;
		}

		//�ж��Ƿ�����
		if (s.getSMoney() - transfer_money < 0) {
			cout << "���㣬ת��ʧ�ܣ����������룡" << endl;
			continue;
		}

		//��ʼת�˲���
		s.dropMoney(transfer_money); //���˻��ȼ�ȥת�˶�
		if (receive.at(0) == '6')	//ת���������˻���6��ͷ��ʾ�Ǵ���˻�
			SAccount_list.at(n).saveMoney(transfer_money);
		else
			LAccount_list.at(n).returnMoney(transfer_money);
		cout << "ת��" << transfer_money << "Ԫ�ɹ����˻����Ϊ" << s.getSMoney() << "Ԫ" << endl;
		break;
	}
}

//����˻��Ĵ���
//����s�������˻�
void ATM::saveMoney(SAccount& s)
{

	while (1) {
		cout << "�����������" ;
		int smoney;
		cin >> smoney;
		if (smoney % 100 == 0) {
			s.saveMoney(smoney);//����SAccount�Ļ�������������ݲ���
			cout << "����" << smoney << "Ԫ�ɹ�! ��������Ϊ" << s.getSMoney() << "Ԫ��" << endl;
			break;
		}
		else
			cout << "�������100������������´��롣" << endl;
	}
}

//����˻��Ļ����
//����s��������˻�
void ATM::saveMoney(LAccount& s)
{
	while (1) {
		cout << "�����뻹�����" ;
		int smoney;
		cin >> smoney;
		if (smoney % 100 == 0) {
			s.returnMoney(smoney);//����LAccount�Ļ�������������ݲ���
			cout << "����" << smoney << "Ԫ�ɹ�! �����Ƿ��Ϊ" << s.getLMoney() << "Ԫ��" << endl;
			break;
		}
		else
			cout << "�������100������������´��롣" << endl;
	}
}

//����˻���ȡ���
//����s��ȡ����˻�
void ATM::dropMoney(SAccount& s)
{
	while (1) {
		cout << "������ȡ�����";
		int smoney;
		cin >> smoney;

		//���������޶��������
		if (smoney > s.getEachLimit()) {
			cout << "ȡ���ÿ���޶���������롣" << endl;
			continue;
		}

		//���������޶��������
		if (smoney > s.getDayLimit()) {
			cout << "ȡ��������޶���������롣" << endl;
			continue;
		}

		//����100����������������
		if (smoney % 100 != 0) {
			cout << "ȡ������100����������������롣" << endl;
			continue;
		}

		//��������������
		if (s.getSMoney() - smoney < 0) {
			cout << "���㣬���������롣" << endl;
			continue;
		}

		//����ȡ�����
		s.dropMoney(smoney); // ����ȥȡ���
		cout << "ȡ��" << smoney << "Ԫ�ɹ�! ʣ�����Ϊ" << s.getSMoney()<< "Ԫ��" << endl;
		break;
	}

}

//����˻���ȡ���
//����l��ȡ����˻�
void ATM::dropMoney(LAccount& l)
{
	while (1) {
		cout << "������ȡ�����" << endl;
		int smoney;
		cin >> smoney;

		//���������޶��������
		if (smoney > l.getEachLimit()) {
			cout << "ȡ���ÿ���޶���������롣" << endl;
			continue;
		}

		//���������޶��������
		if (smoney > l.getDayLimit()) {
			cout << "ȡ��������޶���������롣" << endl;
			continue;
		}

		//����100����������������
		if (smoney % 100 != 0) {
			cout << "ȡ������100����������������롣" << endl;
			continue;
		}

		//�������ö�ȣ���������
		if (smoney > l.getCreditLimit()) {
			cout << "ȡ�����ȣ����������롣" << endl;
			continue;
		}

		//����ȡ�����
		l.dropMoney(smoney); // ����ȥȡ���
		cout << "ȡ��" << smoney << "Ԫ�ɹ�! ��ǰǷ��Ϊ" << l.getLMoney() << "Ԫ��" << endl;
		break;
	}
}

//�������뺯��
//����s����Ҫ������˻�
//����ֵ��bool���� �Ƿ�ͨ��������֤
bool ATM::checkPassword(BaseAccount& s)
{
	string p;
	int wrongCount = 0;
	while (1) {
		if (s.getStatus()) {
			cout << "��������λ�������룺";
			cin >> p;
			if (s.ComparePassword(p)) {
				// �����������
				wrongCount = 0;
				cout << "��½�ɹ���" << endl;
				return true;
			}
			else {
				// �����������
				wrongCount++;
				// �����󳬹����Σ������˺�
				cout << "����������������룡" << endl;
				if (wrongCount >= 3)
					s.setStatus(false);
			}
		}
		else {
			cout << "����������࣬����˺��ѱ����ᡣ" << endl;
			return false;
		}
	}
}

//�޸����뺯��
//����s����Ҫ�޸ĵ��˻�
void ATM::changePassword(BaseAccount& s)
{
	string newpassword;
	while (1) {
		cout << "�����������룺";
		int flag = 1;
		cin >> newpassword;
		//�ж������Ƿ�������
		for (int i = 0; i < newpassword.size(); i++)
		{
			int tmp = (int)newpassword[i];
			if (newpassword.size() == 6 && tmp >= 48 && tmp <= 57)
			{
				continue;
			}
			else
			{
				cout << "�������Ϊ��λ����,�������������룡" << endl;
				flag = 0;
				break;
			}
		}

		//����״����������ͨ�����飬����еڶ�����֤
		//�ж����������Ƿ�һ��
		if (flag) {
			cout << "���ٴ����������룺";
			string newpassword2;
			cin >> newpassword2;
			if (newpassword2 == newpassword) {
				s.setPassword(newpassword);
				cout << "�����޸ĳɹ���" << endl;
				break;
			}
			else
				cout << "�����������벻һ�£����������룡" << endl;
		}
	}
}

//����˻��Ĺ�����壬�����û����ܵ�ѡ��
void ATM::SAccount_progress(SAccount &s)
{
	//��������
	if (!checkPassword(s))
		return;
	int n;
	cout << "�� ӭ ʹ �� ATM �� �� �� ȡ �� ��" << endl;
	cout << endl;
	cout << "   ��������Ӧ����ѡ�������" << endl;
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "-    0  �˿�              -" << endl;
	cout << "-    1  ��ѯ���          -" << endl;
	cout << "-    2  ���              -" << endl;
	cout << "-    3  ȡ��              -" << endl;
	cout << "-    4  ת��              -" << endl;
	cout << "-    5  �޸�����          -" << endl;
	cout << "----------------------------" << endl;
	cout << endl;
	while (1) {
		cout << "�����������";
		cin >> n;
		//switchѡ����
		switch (n)
		{
		case 0:
			Save_to_file("LAccount.txt", "SAccount.txt"); //�˳�ʱ�����ļ�
			cout << "�˿��ɹ������պÿ�Ƭ����ӭ�����´�ʹ��~" << endl;
			return;
		case 1:
			cout << "������ѯ��"  << endl;
			cout << "�������Ϊ��" << s.getSMoney() << endl;
			break;
		case 2:
			cout << "����" << endl;
			saveMoney(s);
			break;
		case 3:
			cout << "��ȡ�" << endl;
			dropMoney(s);
			break;
		case 4:
			cout << "��ת�ˡ�" << endl;
			transfer(s);
			break;
		case 5:
			cout << "���޸����롿" << endl;
			changePassword(s);
			break;
		default:
			cout << "��������������ѡ��"<<endl;
			break;
		}
	}

}

//����˻��Ĺ�����壬�����û����ܵ�ѡ��
void ATM::LAccount_progress(LAccount &l)
{
	//�������
	checkPassword(l);
	int n;
	cout << "�� ӭ ʹ �� ATM �� �� �� ȡ �� ��" << endl;
	cout << endl;
	cout << "   ��������Ӧ����ѡ�������" << endl;
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "-    0  �˿�              -" << endl;
	cout << "-    1  ��ѯǷ��          -" << endl;
	cout << "-    2  ����              -" << endl;
	cout << "-    3  ȡ��              -" << endl;
	cout << "-    4  �޸�����          -" << endl;
	cout << "----------------------------" << endl;
	cout << endl;
	while (1) {
		cout << "�����������";
		cin >> n;
		//switchѡ����
		switch (n)
		{
		case 0:
			Save_to_file("LAccount.txt","SAccount.txt");
			cout << "�˿��ɹ������պÿ�Ƭ����ӭ�����´�ʹ��~" << endl;
			return;
		case 1:
			cout << "��Ƿ���ѯ��" << endl;
			cout << "����Ƿ��Ϊ��" << l.getLMoney() << endl;
			cout << "ʣ����Ϊ��" << l.getCreditLimit()<<endl;
			break;
		case 2:
			cout << "�����" << endl;
			saveMoney(l);
			break;
		case 3:
			cout << "��ȡǮ��" << endl;
			dropMoney(l);
			break;
		case 4:
			cout << "���޸����롿" << endl;
			changePassword(l);
			break;
		default:
			cout << "��������������ѡ��";
			break;
		}
	}

}

//ATM��ʼ���У�����忨�����ж��˻�����
void ATM::start()
{
	while (1) {
		cout << "����������ӭʹ�ñ�����ATM��ȡ��������������" << endl;
		int n = -1;
		string p;
		while (n == -1) {
			cout << "���������Ŀ���(����q�˳�):";
			cin >> p;
			//�����q���˳�����
			if (p == "q") {
				exit(0);
			}
			//�ҵ��˻��ı��n
			n = findaccount(p);
		}
		//���Ǵ������ش��������棬����������ÿ�����
		if (p.at(0) == '6')
			SAccount_progress(SAccount_list.at(n));
		else
			LAccount_progress(LAccount_list.at(n));
	}
}



