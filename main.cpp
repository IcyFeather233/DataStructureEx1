#include"LineEditor.h"
#include <iostream>

int main() {
	char infName[20], outfName[20];
	cout << "�����������ļ���: ";
	cin >> infName;
	cout << "����������ļ���: ";
	cin >> outfName;

	LineEditor Editor(infName, outfName);
	Editor.Run();

	return 0;
}