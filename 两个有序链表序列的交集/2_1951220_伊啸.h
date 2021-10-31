#pragma once
#ifndef INTERSECTION_H_
#define INTERSECTION_H_

void test();
typedef struct LinkNode {
    int data;
    LinkNode* link;
    LinkNode(int num): data(num),link(NULL){ }
    ~LinkNode() { }
}LinkNode;                                        //The linked list node

class LinkList {
private:
    LinkNode* head;

public:
    LinkList();                                   //Constructor
    ~LinkList() { delete[]head; }                 //Destructor
    LinkNode* rhead() { return head; }
    LinkList* Intersection(LinkList*, LinkList*); //Find the intersection of two linked lists
    void input();                                 //The input function
    void display();                               //Output linked list node
};

#endif // !INTERSECTION_H_
