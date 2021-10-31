#include<iostream>
#include"System.h"

using namespace std;

int main()
{
	int numbers, operations;
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请输入考生人数：" << endl;
	cin >> numbers;
	while (numbers <= 0) {
		cout << "输入非法！请输入一个正整数！" << endl;
		cin >> numbers;
	}
	NodeList nodelist;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	for (int i = 0; i < numbers; i++) {
		InfoNode* info = new InfoNode;
		cin >> info->num >> info->name >> info->sex >> info->age >> info->category;
		nodelist.Insert(info, i + 1);
	}//建立考生系统
	cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
	nodelist.showlist(nodelist);
	cout << "请选择您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)：" << endl;
	while (cin >> operations) {
		switch (operations) {
		case 0: {
			return 0;
		}
		case 1: {
			InfoNode* infonode = new InfoNode;
			int pos;
			cout << "请输入你要插入考生的位置：" << endl;
			cin >> pos;
			if (pos <= 0 || pos > nodelist.rlen() + 1) {
				cout << "要插入的位置非法，请重新选择要进行的操作！" << endl;
				break;
			}
			cout << "请依次输入要插入考生的考号，姓名，性别，年龄及报考类别：" << endl;
			cin >> infonode->num >> infonode->name >> infonode->sex >> infonode->age >> infonode->category;
			nodelist.Insert(infonode, pos);
			cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
			nodelist.showlist(nodelist);
			break;
		}//插入新的考生信息
		case 2: {
			string stu, judge;
			int n = 0;
			cout << "请输入要删除的考生的考号：" << endl;
			cin >> stu;
			InfoNode* p = nodelist.Search(stu);
			if (p == nullptr) {
				cout << "未查找到该对象！" << endl;
				break;
			}
			else {
				cout << "你要删除的考生的信息是：";
				nodelist.show(p);
				cout << "请确认是否是你要删除的考生信息（y or n）：";
				while (cin >> judge) {
					if (judge == "y" || judge == "Y") {
						nodelist.Delete(stu);
						cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
						nodelist.showlist(nodelist);
						n = 1;
						break;
					}
					else if (judge == "n" || judge == "N") {
						n = 1;
						break;
					}
					else
						cout << "请输入y/Y或n/N" << endl;
					if (n == 1)
						break;//用n的值标记是否退出while循环
				}
				break;
			}
		}
		case 3: {
			string stu;
			cout << "请输入要查找的考生的考号：" << endl;
			cin >> stu;
			InfoNode* p = nodelist.Search(stu);
			if (p == nullptr) {
				cout << "未查找到该对象！" << endl;
				break;
			}
			else {
				cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
				nodelist.show(p);
				break;
			}
		}
		case 4: {
			string stu;
			cout << "请输入要修改的考生的考号：" << endl;
			cin >> stu;
			InfoNode* p = nodelist.Search(stu);
			if (p == nullptr) {
				cout << "未查找到该对象！" << endl;
				break;
			}
			else {
				cout << "你要修改的考生的信息是：";
				nodelist.show(p);
				nodelist.Modify(stu);
				cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
				nodelist.showlist(nodelist);
				break;
			}
		}
		case 5:
			cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
			nodelist.showlist(nodelist);
			break;
		default:
			cout << "输入的操作非法，请重新输入！" << endl;
			break;
		}
		cout << "请选择您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)：" << endl;
	}
}


InfoNode::InfoNode() {
	num = "";
	name = "";
	age = "";
	sex = "";
	category = "";
	next = NULL;
}
NodeList::NodeList() {
	head = new InfoNode;
	if (head == NULL) {
		cerr << "存储分配错误！" << endl;
		exit(1);
	}
	else {
		head->num = "";
		head->name = "";
		head->age = "";
		head->sex = "";
		head->category = "";
		head->next = nullptr;
		len = 0;
	}
}
int NodeList::rlen() {
	return len;
}//返回len值
InfoNode* NodeList::Insert(InfoNode* infonode, int position) {
	if (position <= 0 || position > len + 1) {
		cout << "要插入的位置非法，请重新选择要进行的操作！" << endl;
		return nullptr;
	}
	else if (head == nullptr) {
		head = infonode;
		head->next = nullptr;
		len++;
		return head;
	}
	else {
		InfoNode* p = head;
		for (int i = 0; i < position - 1; i++) {
			p = p->next;
		}
		if (p != nullptr && p->next != nullptr) {
			infonode->next = p->next;
			p->next = infonode;
			len++;
			return head;
		}
		else if (p != nullptr) {
			infonode->next = nullptr;
			p->next = infonode;
			len++;
			return head;
		}
	}
	return nullptr;
}//实现插入功能
InfoNode* NodeList::Delete(string student_number) {
	if (head == nullptr)
		return nullptr;
	InfoNode* p = head;
	InfoNode* q = head->next;
	if (student_number == p->num) {
		len--;
		return q;
	}
	while (q) {
		if (student_number == q->num) {
			p->next = q->next;
			len--;
			return head;
		}
		else {
			p = p->next;
			q = q->next;
		}
	}
	cout << "未查找到要删除的对象！" << endl;
	return nullptr;
}//实现删除功能
InfoNode* NodeList::Search(string student_number) {
	InfoNode* p = head;
	while (p) {
		if (student_number == p->num)
			return p;
		else
			p = p->next;
	}
	if (p != nullptr && p->next == nullptr) {
		return nullptr;
	}
	return nullptr;
}//实现查找功能
InfoNode* NodeList::Modify(string student_number) {
	InfoNode* p = head;
	while (p) {
		if (p->num == student_number) {
			string information;
			cout << "请输入要修改考生的信息：（考号，姓名，性别，年龄，报考类别）" << endl;
			while (cin >> information) {
				if (information == "考号") {
					string new_num;
					cout << "请输入修改后的新考号：" << endl;
					cin >> new_num;
					p->num = new_num;
					return head;
				}
				else if (information == "姓名") {
					string new_name;
					cout << "请输入修改后的新姓名：" << endl;
					cin >> new_name;
					p->name = new_name;
					return head;
				}
				else if (information == "性别") {
					string new_sex;
					cout << "请输入修改后的新性别：" << endl;
					cin >> new_sex;
					p->sex = new_sex;
					return head;
				}
				else if (information == "年龄") {
					string new_age;
					cout << "请输入修改后的新年龄：" << endl;
					cin >> new_age;
					p->age = new_age;
					return head;
				}
				else if (information == "报考类别") {
					string new_category;
					cout << "请输入修改后的新报考类别：" << endl;
					cin >> new_category;
					p->category = new_category;
					return head;
				}
				else {
					cout << "不存在这样的考生信息!" << endl;
					cout << "请输入要修改考生的信息：（考号，姓名，性别，年龄，报考类别）" << endl;
				}
			}
		}
		else
			p = p->next;
	}
	cout << "未找到要修改的对象！" << endl;
	return nullptr;
}//实现修改功能
void NodeList::show(const InfoNode* infonode) {
	if (infonode != nullptr)
		cout << infonode->num << "       " << infonode->name << "    " << infonode->sex << "      " << infonode->age << "      " << infonode->category << endl;
}//输出单个节点
void NodeList::showlist(const NodeList& nodelist) {
	InfoNode* p = nodelist.head;
	while (p) {
		show(p);
		p = p->next;
	}
}//输出整个链表