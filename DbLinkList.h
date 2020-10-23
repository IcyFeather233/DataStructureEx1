#pragma once
#include <string>
using namespace std;

struct DblNode {
	DblNode() { prev = next = NULL; }
	DblNode(string temp, DblNode* p, DblNode* n) {
		data = temp;
		prev = p;
		next = n;
	}
	string data;
	DblNode* prev;
	DblNode* next;
};
//双向链表
class DbLinkList {
public:
	//建立头指针
	DbLinkList(DblNode* h = new DblNode) :head(h) { count = 0; }
	//访问第n行内容
	string getElem(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		return temp->data;
	}
	//写入第n行内容
	void setElem(int lineNum, string source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		temp->data = source;
	}
	//检测双向链表是否为空
	bool Empty() { return head->next == NULL; }
	//返回双向链表的内容行数
	int getCount() { return count; }
	//在输入行号的后面插入新行
	void Insert(int lineNum, string source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		//创建了新行，且将新行的前一行next更新
		temp->next = new DblNode(source, temp, temp->next);
		//如果是不插入到最后一行，就把插入行的下一行的prev给更新
		if (temp->next->next != NULL)temp->next->next->prev = temp->next;
		//行数加一
		count++;
	}

	//删除第n行
	void Delete(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		//更新被删除行的前一行的next
		temp->prev->next = temp->next;
		//如果被删除行不是最后一行，则更新被删除行下一行的prev
		if (temp->next != NULL)temp->next->prev = temp->prev;
		/*temp->next = temp->prev = NULL;	*/
		delete(temp);
		//行数减一
		count--;
	}
	void Clean() {
		int num = getCount();
		for (int LineNo = num; LineNo >= 1; LineNo --) {
			Delete(LineNo);
		}
	}
private:
	int count;
	DblNode* head;
};