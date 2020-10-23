#include"LineEditor.h"
#include <iostream>

int main() {
	char infName[20], outfName[20];
	cout << "请输入输入文件名: ";
	cin >> infName;
	cout << "请输入输出文件名: ";
	cin >> outfName;

	LineEditor Editor(infName, outfName);
	Editor.Run();

	return 0;
}