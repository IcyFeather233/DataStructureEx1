#include "LineEditor.h"
#include <iostream>

LineEditor::LineEditor(char infName[], char outfName[]) {
	inFile.open(infName, ios::in);
	while (inFile.fail()) {
		cout << "�����ļ���ʧ�ܣ�����Ƿ���ڸ��ļ���" << endl;
		cout << "�����������ļ�����";
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
			cout << "-----------------��ǰ��-------------------" << endl;
			cout << curLineNo << " : " << curLine << endl;
		}
		else
			cout << "�ļ�������Ϊ��(����r�ɽ��ļ����뻺����)" << endl;

		cin >> userCommand;
		userCommand = tolower(userCommand);

		switch (userCommand) {
		case 'b'://begin ����һ��
			if (!textBuffer.Empty())
				curLineNo = 1;
			else
				cout << "�ļ�������Ϊ��!" << endl;
			break;
		case 'c'://change �滻ĳ���Ӵ�
			if (!textBuffer.Empty())
				Change();
			else
				cout << "�ļ�������Ϊ�գ�" << endl;
			break;
		case 'd'://delete ɾ��һ��
			if (!textBuffer.Empty())
				Delete();
			else
				cout << "�ļ�������Ϊ�գ�" << endl;
			break;
		case 'e'://end �����һ��
			if (!textBuffer.Empty())
				curLineNo = textBuffer.getCount();
			else
				cout << "�ļ�������Ϊ�գ�" << endl;
			break;
		case 'f'://find ����ָ����ĳ���Ӵ�
			if (!textBuffer.Empty())
				Find();
			else
				cout << "�ļ�������Ϊ�գ�" << endl;
			break;
		case 'g'://goto ��ָ����ĳһ��
			if (!textBuffer.Empty())
				Goto();
			else
				cout << "�ļ�������Ϊ�գ�" << endl;
			break;
		case 'h'://help ����
			Help();
			break;
		case 'i'://insert ����һ��
			Insert();
			break;
		case 'l'://length ͳ���ļ��������ַ���
			Length();
			break;
		case 'n'://next ����һ��
			if (curLineNo < textBuffer.getCount())
				curLineNo++;
			else
				cout << "�Ѿ������һ�У�" << endl;
			break;
		case 'p'://previous ��ǰһ��
			if (curLineNo > 1)
				curLineNo--;
			else
				cout << "�Ѿ��ǵ�һ�У�" << endl;
			break;
		case 'q':
			break;
		case 'r'://read ���¶����ļ�
			Read();
			break;
		case 's'://substitute �滻��ǰ��
			Substitute();
			break;
		case 'v'://view ��ʾ��ǰ�ļ�����
			if (!textBuffer.Empty())
				View();
			else
				cout << "�ļ�Ϊ�գ�" << endl;
			break;
		case 'w'://write ���浱ǰ�ļ�
			if (!textBuffer.Empty())
				Write();
			else
				cout << "�ļ�Ϊ�գ�" << endl;
			break;
		default://�����������ڣ�������ʾ
			cout << "�������������ڣ�����h���������ʾ" << endl;
		}
	} while (userCommand != 'q');
}

void LineEditor::Help() {
	cout << "��Ч������: \nb(egin)\t\tc(hange)\td(el)\t\te(nd)\nf(ind)\t\tg(oto)\t\th(elp)\t\ti(nsert)\nl(ength)\tn(ext)\t\tp(revious)\tq(uit)\nr(ead)\t\ts(ubstitute)\tv(iew)\t\tw(rite)" << endl;
}
//�滻ĳ���Ӵ�
void LineEditor::Change() {
	char tmp[100];
	string temp = textBuffer.getElem(curLineNo);
	cout << "�����滻��ǰ����һ���Ӵ� ";
	cin >> tmp;
	string segment = tmp;
	cout << "��������һ�������滻? ";
	cin >> tmp;
	string newSeg = tmp;
	int c = temp.find(segment);
	if (c != -1) {
		temp.replace(c, segment.length(), newSeg);
		textBuffer.setElem(curLineNo, temp);
	}
	else
		cout << "�滻ʧ�ܣ����滻����δ�ҵ���" << endl;
}
//ɾ��һ��
void LineEditor::Delete() {
	if (curLineNo == 0)
		cout << "ɾ��ʧ�ܣ��ļ�Ϊ�գ��޷�ִ��ɾ��������" << endl;
	else
		textBuffer.Delete(curLineNo);
	//���µ�ǰ��Ϊɾ������������һ��
	curLineNo = textBuffer.getCount();
}
//����ָ����ĳ���Ӵ�
void LineEditor::Find() {
	cout << "����Ҫ���ҵ��Ӵ�" << endl;
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
	if (!f) cout << "δ�ҵ����Ӵ�!" << endl;
}
//��ָ����ĳһ��
void LineEditor::Goto() {
	cout << "������ת���кţ�";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount())
		cout << "��һ�в����ڣ�" << endl;
	else
		curLineNo = lineNum;
}
//����һ��
void LineEditor::Insert() {
	cout << "���������кţ�";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount() + 1)
		cout << "����Խ�磬���޷�����һ�в��룡" << endl;
	else {
		cout << "�������������У�" << endl;
		char temp[100];
		//ע��getlineҪ����
		cin.getline(temp, 100);
		cin.getline(temp, 100);
		textBuffer.Insert(lineNum - 1, temp);
		curLineNo = lineNum;
	}
}
//ͳ���ļ��������ַ���
void LineEditor::Length() {
	cout << "�ļ���һ���� " << textBuffer.getCount() << " ��" << endl;
	int num = 0;
	for (int LineNo = 1; LineNo < textBuffer.getCount(); LineNo ++) {
		num += textBuffer.getElem(LineNo).length();
	}
	cout << "�ļ����ַ�����Ϊ " << num << " ��" << endl;
}
//���¶����ļ�
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
//�滻��ǰ��
void LineEditor::Substitute() {
	cout << "�������У�" << endl;
	char temp[100];
	//ע��getlineҪ����
	cin.getline(temp, 100);
	cin.getline(temp, 100);
	textBuffer.Delete(curLineNo);
	textBuffer.Insert(curLineNo - 1, temp);
}
//��ʾ��ǰ�ļ�����
void LineEditor::View() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount()) {
		cout << textBuffer.getElem(curLine) << endl;
		curLine++;
	}
}
//���浱ǰ�ļ�
void LineEditor::Write() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount())
		outFile << textBuffer.getElem(curLine++) << endl;
}