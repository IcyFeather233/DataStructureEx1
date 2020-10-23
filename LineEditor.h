#pragma once
#include"DbLinkList.h"
#include<fstream>

class LineEditor {
public:
	LineEditor(char[], char[]);
	void Run();
private:
	DbLinkList textBuffer;	//缓冲区是一个双向链表
	int curLineNo;			//当前行号
	ifstream inFile;
	ofstream outFile;
	char infName[20];

	void Help();		//帮助
	void View();		//显示当前文件内容
	void Goto();		//到指定的某一行
	void Insert();		//插入一行
	void Delete();		//删除一行
	void Substitute();	//替换当前行
	void Change();		//替换某个子串
	void Find();		//查找指定的某个字串
	void Length();		//统计文件行数及字符数
	void Read();		//重新读入文件
	void Write();		//保存当前文件
};