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
//˫������
class DbLinkList {
public:
	//����ͷָ��
	DbLinkList(DblNode* h = new DblNode) :head(h) { count = 0; }
	//���ʵ�n������
	string getElem(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		return temp->data;
	}
	//д���n������
	void setElem(int lineNum, string source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		temp->data = source;
	}
	//���˫�������Ƿ�Ϊ��
	bool Empty() { return head->next == NULL; }
	//����˫���������������
	int getCount() { return count; }
	//�������кŵĺ����������
	void Insert(int lineNum, string source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		//���������У��ҽ����е�ǰһ��next����
		temp->next = new DblNode(source, temp, temp->next);
		//����ǲ����뵽���һ�У��ͰѲ����е���һ�е�prev������
		if (temp->next->next != NULL)temp->next->next->prev = temp->next;
		//������һ
		count++;
	}

	//ɾ����n��
	void Delete(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		//���±�ɾ���е�ǰһ�е�next
		temp->prev->next = temp->next;
		//�����ɾ���в������һ�У�����±�ɾ������һ�е�prev
		if (temp->next != NULL)temp->next->prev = temp->prev;
		/*temp->next = temp->prev = NULL;	*/
		delete(temp);
		//������һ
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