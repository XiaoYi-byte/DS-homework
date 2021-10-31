#pragma once
#ifndef SYSTEM_H_
#define SYSTEM_H_


#include<iostream>
using namespace std;


struct InfoNode {
	string num;//表示学生学号
	string name;//表示学生姓名
	string sex;//表示学生性别
	string age;//表示学生年龄
	string category;//表示学生报考类别
	InfoNode* next;
	InfoNode();
};//整个InfoNode作为NodeList的一个节点
struct NodeList {
private:
	int len;
	InfoNode* head;
public:
	NodeList();
	~NodeList() { };

	int rlen();//返回len值
	InfoNode* Insert(InfoNode* infonode, int position);//实现插入功能
	InfoNode* Delete(string student_number);//实现删除功能
	InfoNode* Search(string student_number);//实现查找功能
	InfoNode* Modify(string student_number);//实现修改功能

	void show(const InfoNode* infonode);//输出单个节点
	void showlist(const NodeList& nodelist);//输出整个链表
};
#endif // !SYSTEM_H_
