#include "6_1951220_伊啸.h"
#include <iostream>

using namespace std;

int main()
{
    char option[20];
    string str;
    Tree FamilyTree;
    FamilyTree.Initial();
    while (1) {
        cout << endl;
        cout << "请选择要执行的操作：";
        cin >> option[0];
        switch (option[0]) {
        case 'A':
            FamilyTree.Add();
            break;
        case 'B':
            FamilyTree.Insert();
            break;
        case 'C':
            FamilyTree.RemovesubTree();
            break;
        case 'D':
            FamilyTree.Change_Name();
            break;
        case 'E':
            FamilyTree.Search();
            break;
        case 'F':
            system("pause");
            return 0;
        default:
            cout << "输入非法！请输入合适的选项！" << endl;
            break;
        }
    }
}

void Tree::Initial()
{
    string ancestor;
    cout << "**                 家谱管理系统                 **" << endl;
    cout << "==================================================" << endl;
    cout << "**                 请输入要进行的操作：         **" << endl;
    cout << "**                 A---完善家谱                 **" << endl;
    cout << "**                 B---添加家庭成员             **" << endl;
    cout << "**                 C---解散局部家庭             **" << endl;
    cout << "**                 D---更改家庭成员姓名         **" << endl;
    cout << "**                 E---查找家庭成员的父亲子女   **" << endl;
    cout << "**                 F---退出程序                 **" << endl;
    cout << "==================================================" << endl;
    cout << endl;
    cout << "首先建立一个家谱！" << endl;
    cout << "请输入祖先的名字：";
    cin >> ancestor;
    TreeNode* anc = new TreeNode(ancestor);
    root = anc;
    if (Root())
        cout << "此家谱的祖先是：" << ancestor;
}

bool Tree::Root()
{
    if (root == NULL) {
        current = NULL;
        return false;
    } else {
        current = root;
        return true;
    }
}

bool Tree::Parent()
{
    if (current != NULL && current->parent != NULL) {
        current = current->parent;
        return true;
    }
    current = NULL;
    return false;
}

bool Tree::FirstChild()
{
    if (current != NULL && current->firstChild != NULL) {
        current = current->firstChild;
        return true;
    }
    current = NULL;
    return false;
}

bool Tree::NextSibling()
{
    if (current != NULL && current->nextSibling != NULL) {
        current = current->nextSibling;
        return true;
    }
    current = NULL;
    return false;
}

bool Tree::Find(string Target)
{ //前序遍历，非递归
    if (IsEmpty())
        return false;
    TreeNode* q = NULL;
    TreeNode* p = root;
    if (root->name == Target) {
        current = root;
        return true;
    }
    current = root;
    if (FirstChild()) { //从根节点的长子节点开始
        p = current;
        Stack S;
        S.Push(q);
        while (p != NULL) {
            if (p->name == Target) {
                current = p;
                return true;
            }
            if (p->nextSibling != NULL)
                S.Push(p->nextSibling); //兄弟节点入栈
            if (p->firstChild != NULL)
                p = p->firstChild;
            else
                S.Pop(p);
        }
        return false;
    } else
        return false;
}

bool Tree::RemovesubTree()
{
    string par;
    cout << "请输入要解散的家庭的人的姓名：";
    cin >> par;
    if (!Find(par)) {
        cout << "要解散的家庭的人不存在!" << endl;
        return false;
    }
    cout << "要解散家庭的人的姓名是：" << par << endl;
    TreeNode* p = current;
    cout << par << "的第一代子孙是：";
    if (FirstChild()) {
        p = p->firstChild;
        cout << p->name << " ";
        while (p->nextSibling != NULL) {
            p = p->nextSibling;
            cout << p->name << " ";
        }
    } else
        cout << "无！" << endl;
    if (Find(par)) { //令current指针再次指向名字为par的节点
        if (current == root) {
            root->firstChild = NULL;
            root = NULL;
            current = NULL;
            delete root;
            return true;
        }
        if (Parent()) { //current指针指向目标节点的双亲节点
            TreeNode* q = current->firstChild;
            if (q->name == par) { //删除长子节点
                current->firstChild = q->nextSibling;
                q->parent = NULL;
                q->nextSibling = NULL;
                delete q;
                return true;
            }
            TreeNode* r = q->nextSibling;
            while (r) { //在兄弟链表中删除该节点
                if (r->name == par) {
                    q->nextSibling = r->nextSibling;
                    r->nextSibling = NULL;
                    r->parent = NULL;
                    delete r;
                    return true;
                }
                q = r;
                r = r->nextSibling;
            }
        }
    }
}

bool Tree::Add()
{
    string Parent, child[20];
    int numbers;
    cout << "请输入要建立家庭的人的姓名：";
    cin >> Parent;
    if (!Find(Parent)) {
        cout << "要建立的家庭的人不存在!" << endl;
        return false;
    }
    cout << "请输入" << Parent << "的儿女个数：";
    while (1) //对输入int类型的变量进行校验
    {
        cin >> numbers;
        if (cin.good() == false) {
            while (getchar() != '\n')
                ;
            cin.clear();
            cout << "输入有误！请重新输入" << Parent << "的儿女个数：";
        } else
            break;
    }
    cout << "请依次输入" << Parent << "的儿女的姓名：";
    cin >> child[0];
    TreeNode* first_child = new TreeNode(child[0]); //先插入长子节点
    current->firstChild = first_child;
    first_child->parent = current;
    TreeNode* p = current;
    current = first_child;
    for (int i = 1; i < numbers; i++) { //插入兄弟节点
        cin >> child[i];
        TreeNode* newchild = new TreeNode(child[i]);
        newchild->parent = p;
        current->nextSibling = newchild;
        current = newchild;
    }
    cout << Parent << "的第一代子孙是：";
    p = p->firstChild;
    while (p) {
        cout << p->name << " ";
        p = p->nextSibling;
    }
    return true;
}

bool Tree::Insert()
{
    string Parent, child;
    cout << "请输入要添加儿子（或女儿）的人的姓名：";
    cin >> Parent;
    if (!Find(Parent)) {
        cout << "要添加儿子（或女儿）的人不存在!" << endl;
        return false;
    }
    TreeNode* p = current;
    cout << "请输入" << Parent << "新添加的儿子（或女儿）的姓名：";
    cin >> child;
    if (current->firstChild == NULL) { //无长子就变成长子，否则插入最后一个兄弟节点的末尾
        TreeNode* first_child = new TreeNode(child);
        current->firstChild = first_child;
        first_child->parent = current;
        current = first_child;
    } else {
        current = current->firstChild;
        while (current->nextSibling != NULL)
            current = current->nextSibling;
        TreeNode* next_sibling = new TreeNode(child);
        current->nextSibling = next_sibling;
        next_sibling->parent = p;
    }
    cout << Parent << "的第一代子孙是：";
    p = p->firstChild;
    while (p) {
        cout << p->name << " ";
        p = p->nextSibling;
    }
    return true;
}

bool Tree::Change_Name()
{
    string member, new_name;
    cout << "请输入要更改姓名的人的目前姓名：";
    cin >> member;
    if (!Find(member)) {
        cout << "要更改姓名的人不存在！" << endl;
        return false;
    }
    cout << "请输入更改后的姓名：";
    cin >> new_name;
    current->name = new_name;
    cout << member << "已更名为" << new_name;
    return true;
}

bool Tree::Search()
{
    string member;
    cout << "请输入要查找的人的姓名：";
    cin >> member;
    if (!Find(member)) {
        cout << "要查找的人不存在！" << endl;
        return false;
    }
    TreeNode* p = current;
    if (Parent())
        cout << member << "的父亲（或母亲）是：" << current->name << endl;
    else
        cout << member << "是此家谱的祖先，没有父亲！" << endl;
    if (p->firstChild == NULL)
        cout << member << "没有儿子（或女儿）！" << endl;
    else {
        cout << member << "的儿子（或女儿）是：";
        p = p->firstChild;
        while (p) {
            cout << p->name << " ";
            p = p->nextSibling;
        }
    }
    return true;
}

Stack::Stack(int sz)
    : top(-1)
    , maxsize(sz)
{
    elements = new TreeNode*[maxsize];
    if (elements == NULL) {
        cerr << "内存分配失败！" << endl;
        exit(1);
    }
}

bool Stack::Push(TreeNode*& x)
{
    if (IsFull()) {
        cout << "栈已满，无法入栈！" << endl;
        return false;
    }
    elements[++top] = x;
    return true;
}

bool Stack::Pop(TreeNode*& x)
{
    if (IsEmpty()) {
        cout << "栈为空，无法出栈！" << endl;
        return false;
    }
    x = elements[top--];
    return true;
}

bool Stack::getTop(TreeNode*& x)
{
    if (IsEmpty()) {
        cout << "栈为空，最上层元素不存在！" << endl;
        return false;
    }
    x = elements[top];
    return true;
}