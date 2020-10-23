#include "LineEditor.h"
#include <iostream>

LineEditor::LineEditor(char infName[], char outfName[]) {
	inFile.open(infName, ios::in);
	while (inFile.fail()) {
		cout << "输入文件打开失败，检查是否存在该文件！" << endl;
		cout << "请输入输入文件名：";
		cin >> infName;
		inFile.open(infName, ios::in);
	}
	strcpy_s(this->infName, infName);
	outFile.open(outfName, ios::out);
}

void LineEditor::Run() {
	char userCommand;

	Help();

	do {
		string curLine;

		if (curLineNo != 0) {
			curLine = textBuffer.getElem(curLineNo);
			cout << "-----------------当前行-------------------" << endl;
			cout << curLineNo << " : " << curLine << endl;
		}
		else
			cout << "文件缓冲区为空(命令r可将文件读入缓冲区)" << endl;

		cin >> userCommand;
		userCommand = tolower(userCommand);

		switch (userCommand) {
		case 'b'://begin 到第一行
			if (!textBuffer.Empty())
				curLineNo = 1;
			else
				cout << "文件缓冲区为空!" << endl;
			break;
		case 'c'://change 替换某个子串
			if (!textBuffer.Empty())
				Change();
			else
				cout << "文件缓冲区为空！" << endl;
			break;
		case 'd'://delete 删除一行
			if (!textBuffer.Empty())
				Delete();
			else
				cout << "文件缓冲区为空！" << endl;
			break;
		case 'e'://end 到最后一行
			if (!textBuffer.Empty())
				curLineNo = textBuffer.getCount();
			else
				cout << "文件缓冲区为空！" << endl;
			break;
		case 'f'://find 查找指定的某个子串
			if (!textBuffer.Empty())
				Find();
			else
				cout << "文件缓冲区为空！" << endl;
			break;
		case 'g'://goto 到指定的某一行
			if (!textBuffer.Empty())
				Goto();
			else
				cout << "文件缓冲区为空！" << endl;
			break;
		case 'h'://help 帮助
			Help();
			break;
		case 'i'://insert 插入一行
			Insert();
			break;
		case 'l'://length 统计文件行数及字符数
			Length();
			break;
		case 'n'://next 到下一行
			if (curLineNo < textBuffer.getCount())
				curLineNo++;
			else
				cout << "已经是最后一行！" << endl;
			break;
		case 'p'://previous 到前一行
			if (curLineNo > 1)
				curLineNo--;
			else
				cout << "已经是第一行！" << endl;
			break;
		case 'q':
			break;
		case 'r'://read 重新读入文件
			Read();
			break;
		case 's'://substitute 替换当前行
			Substitute();
			break;
		case 'v'://view 显示当前文件内容
			if (!textBuffer.Empty())
				View();
			else
				cout << "文件为空！" << endl;
			break;
		case 'w'://write 保存当前文件
			if (!textBuffer.Empty())
				Write();
			else
				cout << "文件为空！" << endl;
			break;
		default://输入的命令不存在，触发提示
			cout << "您输入的命令不存在，输入h获得命令提示" << endl;
		}
	} while (userCommand != 'q');
}

void LineEditor::Help() {
	cout << "有效命令有: \nb(egin)\t\tc(hange)\td(el)\t\te(nd)\nf(ind)\t\tg(oto)\t\th(elp)\t\ti(nsert)\nl(ength)\tn(ext)\t\tp(revious)\tq(uit)\nr(ead)\t\ts(ubstitute)\tv(iew)\t\tw(rite)" << endl;
}
//替换某个子串
void LineEditor::Change() {
	char tmp[100];
	string temp = textBuffer.getElem(curLineNo);
	cout << "你想替换当前行哪一个子串 ";
	cin >> tmp;
	string segment = tmp;
	cout << "你想用哪一段文字替换? ";
	cin >> tmp;
	string newSeg = tmp;
	int c = temp.find(segment);
	if (c != -1) {
		temp.replace(c, segment.length(), newSeg);
		textBuffer.setElem(curLineNo, temp);
	}
	else
		cout << "替换失败！被替换文字未找到！" << endl;
}
//删除一行
void LineEditor::Delete() {
	if (curLineNo == 0)
		cout << "删除失败！文件为空，无法执行删除操作！" << endl;
	else
		textBuffer.Delete(curLineNo);
	//更新当前行为删除操作后的最后一行
	curLineNo = textBuffer.getCount();
}
//查找指定的某个子串
void LineEditor::Find() {
	cout << "输入要查找的子串" << endl;
	string target;
	cin >> target;
	bool f = false;
	for (int LineNo = 1; LineNo < textBuffer.getCount(); LineNo++) {
		string temp = textBuffer.getElem(LineNo);
		int c = temp.find(target);
		if (c != -1) {
			if (!f)f = true;
			cout << LineNo << ": " << temp << endl;
		}
	}
	if (!f) cout << "未找到该子串!" << endl;
}
//到指定的某一行
void LineEditor::Goto() {
	cout << "输入跳转的行号：";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount())
		cout << "这一行不存在！" << endl;
	else
		curLineNo = lineNum;
}
//插入一行
void LineEditor::Insert() {
	cout << "输入插入的行号：";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount() + 1)
		cout << "行数越界，你无法在这一行插入！" << endl;
	else {
		cout << "输入你想插入的行：" << endl;
		char temp[100];
		//注意getline要两次
		cin.getline(temp, 100);
		cin.getline(temp, 100);
		textBuffer.Insert(lineNum - 1, temp);
		curLineNo = lineNum;
	}
}
//统计文件行数及字符数
void LineEditor::Length() {
	cout << "文件中一共有 " << textBuffer.getCount() << " 行" << endl;
	int num = 0;
	for (int LineNo = 1; LineNo < textBuffer.getCount(); LineNo ++) {
		num += textBuffer.getElem(LineNo).length();
	}
	cout << "文件中字符总数为 " << num << " 个" << endl;
}
//重新读入文件
void LineEditor::Read() {
	textBuffer.Clean();
	inFile.close();
	inFile.open(infName);
	char temp[100];
	while (!inFile.eof()) {
		inFile.getline(temp, 100);
		string source = temp;
		textBuffer.Insert(textBuffer.getCount(), source);
	}
	inFile.close();
	curLineNo = textBuffer.getCount();
}
//替换当前行
void LineEditor::Substitute() {
	cout << "输入新行：" << endl;
	char temp[100];
	//注意getline要两次
	cin.getline(temp, 100);
	cin.getline(temp, 100);
	textBuffer.Delete(curLineNo);
	textBuffer.Insert(curLineNo - 1, temp);
}
//显示当前文件内容
void LineEditor::View() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount()) {
		cout << textBuffer.getElem(curLine) << endl;
		curLine++;
	}
}
//保存当前文件
void LineEditor::Write() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount())
		outFile << textBuffer.getElem(curLine++) << endl;
}