#pragma once
#include"DbLinkList.h"
#include<fstream>

class LineEditor {
public:
	LineEditor(char[], char[]);
	void Run();
private:
	DbLinkList textBuffer;	//��������һ��˫������
	int curLineNo;			//��ǰ�к�
	ifstream inFile;
	ofstream outFile;
	char infName[20];

	void Help();		//����
	void View();		//��ʾ��ǰ�ļ�����
	void Goto();		//��ָ����ĳһ��
	void Insert();		//����һ��
	void Delete();		//ɾ��һ��
	void Substitute();	//�滻��ǰ��
	void Change();		//�滻ĳ���Ӵ�
	void Find();		//����ָ����ĳ���ִ�
	void Length();		//ͳ���ļ��������ַ���
	void Read();		//���¶����ļ�
	void Write();		//���浱ǰ�ļ�
};