#include "7_1951220_伊啸.h"
#include <iostream>

using namespace std;

int main()
{
    test();
    system("pause");
    return 0;
}

void test()
{
    int size, minlength;
    cout << "Please enter the number of pieces you want to saw the wood into:";
    while (1) { //Make the input valid
        cin >> size;
        if (cin.good() == false) {
            cout << "Error input! Please enter again:";
            while (getchar() != '\n')
                ;
            cin.clear();
        } else {
            break;
        }
    }
    while (size < 1) {
        cout << "The amount of wood must be greater than 0!" << endl;
        cout << "Please enter the number of pieces you want to saw the wood into again:";
        while (1) { //Make the input valid
            cin >> size;
            if (cin.good() == false) {
                cout << "Error input! Please enter again:";
                while (getchar() != '\n')
                    ;
                cin.clear();
            } else {
                break;
            }
        }
    }
    cout << "Please enter the length of each wood:";
    LinkList list;
    while (1) {
        if (list.Initial(size)) {
            if (size == 1) {
                cout << list.head->link->data << endl;
                break;
            } else {
                HuffmanTree HT(list, size);
                minlength = HT.Minlength(size);
                cout << minlength << endl;
                break;
            }
        } else {
            cout << "The data you entered is illegal. Please enter positive integers!" << endl;
            cout << "Please re-enter the length of each wood:";
            while (getchar() != '\n')
                ;
            cin.clear();
        }
    }
}

LinkList::LinkList()
{
    head = new LinkNode;
    if (head == NULL) {
        cerr << "storage allocation error!" << endl;
        exit(1);
    }
}
bool LinkList::Initial(int numbers)
{
    int length;
    LinkNode* p = head;
    for (int i = 0; i < numbers; i++) {
        cin >> length;
        if (length <= 0 || cin.good() == false)
            return false;
        LinkNode* newnode = new LinkNode(length);
        newnode->link = NULL;
        p->link = newnode;
        p = p->link;
    }
    return true;
}
void LinkList::Insert(const int& x)
{
    LinkNode* newnode = new LinkNode(x);
    newnode->link = head->link;
    head->link = newnode;
}
void LinkList::Delete(int& x)
{
    LinkNode* p = head->link;
    LinkNode* q = head;
    while (p) {
        if (p->data != x) {
            q = p;
            p = p->link;
        } else
            break;
    }
    if (p != NULL)
        q->link = p->link;
    delete p;
}
void LinkList::Search(int& x)
{
    int min = 0;
    LinkNode* p = head->link;
    if (p != NULL) {
        min = p->data;
        p = p->link;
    }
    while (p != NULL) {
        if (p->data < min)
            min = p->data;
        p = p->link;
    }
    x = min;
}
stack::stack(int sz)
    : maxsize(sz)
    , top(-1)
{
    element = new HuffmanNode*[DefaultSize];
    if (element == NULL) {
        cerr << "storage allocation error!" << endl;
        exit(1);
    }
}
bool stack::Push(HuffmanNode*& x)
{
    if (IsFull()) {
        cerr << "The stack is full!" << endl;
        return false;
    }
    element[++top] = x;
    return true;
}
bool stack::Pop(HuffmanNode*& x)
{
    if (IsEmpty()) {
        cerr << "The stack is empty!" << endl;
        return false;
    }
    x = element[top--];
    return true;
}
HuffmanTree::HuffmanTree(LinkList list, int n)
{
    int first, second;
    LinkNode* p = list.head->link;
    HuffmanNode* parent = new HuffmanNode;
    HuffmanNode* arr = new HuffmanNode[n];
    for (int i = 0; i < n - 1; i++) {
        list.Search(first);
        list.Delete(first);
        list.Search(second);
        list.Delete(second);
        HuffmanNode* firstNode = new HuffmanNode(first);
        HuffmanNode* secondNode = new HuffmanNode(second); //Find two minimum values and then construct two Huffman tree nodes
        mergeTree(firstNode, secondNode, parent);
        arr[i] = *parent;
        list.Insert(first + second);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            if (arr[i].data == arr[j].left->data) {
                arr[i].parent = &arr[j];
                arr[j].left = &arr[i];
            } else if (arr[i].data == arr[j].right->data) {
                arr[i].parent = &arr[j];
                arr[j].right = &arr[i];
            }
        }
    } //Connect all the nodes into a Huffman tree
    root = &arr[n - 2];
}
void HuffmanTree::mergeTree(HuffmanNode*& ht1, HuffmanNode*& ht2, HuffmanNode*& parent)
{
    parent->left = ht1;
    parent->right = ht2;
    parent->data = ht1->data + ht2->data;
    ht1->parent = ht2->parent = parent;
}
int HuffmanTree::Minlength(int size)
{
    stack st(size);
    int sum = 0;
    HuffmanNode* p = root;
    HuffmanNode* q = NULL;
    st.Push(q);
    while (p != q) {
        if (p->right != NULL) {
            st.Push(p->right);
        }
        if (p->left != NULL) {
            sum += p->data;
            p = p->left;
        } else
            st.Pop(p);
    } //Calculate the values for all non-leaf nodes
    return sum;
}