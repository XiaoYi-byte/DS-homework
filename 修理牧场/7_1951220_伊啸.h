#pragma once
#ifndef FARM_H_
#define FARM_H_
#define DefaultSize 10000

void test();
typedef struct LinkNode {
    int data;
    LinkNode* link;
    LinkNode()
        : data(0)
        , link(nullptr)
    {
    } //Constructor
    LinkNode(int elem)
        : data(elem)
        , link(nullptr)
    {
    } //Constructor
    ~LinkNode() {}; //Destructor
} LinkNode; //The node of the link

typedef struct LinkList {
    LinkNode* head; //The head node
    LinkList(); //Constructor
    ~LinkList() {}; //Destructor
    bool Initial(int); //Initialization function.Input data is stored in a linked list
    void Insert(const int& x); //Inserts a node with a value of x to the tail node
    void Delete(int& x); //Deletes the node with the value of x
    void Search(int& x); //Search the list and make x the minimum element in the list
} LinkList;
typedef struct HuffmanNode {
    int data;
    HuffmanNode *left, *right, *parent; //The left child node, the right child node and the parent node
    HuffmanNode()
        : data(0)
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
    {
    } //Constructor
    HuffmanNode(int elem, HuffmanNode* leftchild = nullptr, HuffmanNode* rightchild = nullptr, HuffmanNode* pr = nullptr)
        : data(elem)
        , left(leftchild)
        , right(rightchild)
        , parent(pr)
    {
    } //Constructor
    bool operator<=(HuffmanNode*& R) { return data <= R->data; } //Overload <=
    bool operator>(HuffmanNode*& R) { return data > R->data; } //Overload >
} HuffmanNode;

class HuffmanTree {
private:
    HuffmanNode* root; //The root node
public:
    HuffmanTree()
        : root(nullptr)
    {
    } //Constructor
    HuffmanTree(LinkList list, int n); //Constructor, the parameter is the data stored in the linked list
    ~HuffmanTree() { } //Destructor
    void mergeTree(HuffmanNode*& ht1, HuffmanNode*& ht2, HuffmanNode*& parent); //Merge the two nodes
    int Minlength(int); //Find the minimum weight of the Huffman tree
};

class stack {
private:
    HuffmanNode** element; //An array that stores pointers to Huffman tree nodes
    int top;
    int maxsize;

public:
    stack(int sz = DefaultSize); //Constructor
    ~stack() { delete[] element; } //Destructor
    bool Push(HuffmanNode*& x); //Push x into the stack
    bool Pop(HuffmanNode*& x); //Pop x
    bool IsEmpty() const { return (top == -1) ? true : false; }
    bool IsFull() const { return (top == maxsize - 1) ? true : false; }
};
#endif // !FARM_H_#pragma once
