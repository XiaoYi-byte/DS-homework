#pragma once
#ifndef FAMILYTREE_H_
#define FAMILYTREE_H_
#include <string>

using std::string;
const int maxSize = 50;

typedef struct TreeNode { //树的节点，采用长子-兄弟表示法，加入双亲节点的指针便于找到双亲节点
    string name;
    TreeNode *firstChild, *nextSibling, *parent;
    TreeNode(string value = "NULL", TreeNode* fc = NULL, TreeNode* ns = NULL, TreeNode* pa = NULL)
        : name(value)
        , firstChild(fc)
        , nextSibling(ns)
        , parent(pa)
    {
    } //构造函数
} TreeNode;

class Tree {
private:
    TreeNode *root, *current; //根节点和当前节点，设置当前节点以便于进行各种操作
public:
    Tree() { root = current = NULL; } //构造函数
    ~Tree() { } //析构函数
    void Initial(); //初始化界面以及根节点
    bool Root(); //使当前节点为根节点
    bool IsEmpty() { return root == NULL; } //判断当前节点是否为空
    bool FirstChild(); //使当前节点为当前节点的第一个子女节点
    bool NextSibling(); //使当前节点为当前节点的下一个兄弟节点
    bool Parent(); //使当前节点为当前节点的双亲节点
    bool Find(string Target); //前序遍历查找名字为Target的节点
    bool RemovesubTree(); //移除某个节点以及其所有的子女节点
    bool Add(); //给某个节点添加若干个子女
    bool Insert(); //给某个节点添加一个子女
    bool Change_Name(); //改变某个节点的名字
    bool Search(); //查找某个节点的双亲节点以及所有的子节点
};

class Stack {
private:
    TreeNode** elements; //用于存储TreeNode*的数组
    int top; //栈顶指针
    int maxsize; //栈的最大容量
public:
    Stack(int sz = 50); //构造函数
    ~Stack() { delete[] elements; } //析构函数
    bool Push(TreeNode*& x); //入栈
    bool Pop(TreeNode*& x); //出栈
    bool getTop(TreeNode*& x); //取栈顶的元素
    bool IsEmpty() const { return top == -1 ? true : false; } //判空
    bool IsFull() const { return top == maxsize - 1 ? true : false; } //判满
};
#endif // !FAMILYTREE_H_
