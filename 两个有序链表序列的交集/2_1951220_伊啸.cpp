#include <iostream>
#include"Intersection.h"
#define maxsize 50
using namespace std;

bool judge_negative = false;                                           //Determine if the input data is negative

int main()
{
    test();
    system("pause");
    return 0;
}
void test() {
    char answer[maxsize];
    cout << "Do you want to enter the intersection test?(y or n)" << endl;
    cin >> answer;
    while (1) {                                                        //Determine if the input is valid
        if (answer[0] != 'y' && answer[0] != 'Y' && answer[0] != 'n' && answer[0] != 'N') {
            cout << "Invalid input! Please enter y or n!" << endl;
            cin >> answer[0];
        }
        else
            break;
    }
    while (1) {
        if (answer[0] == 'y' || answer[0] == 'Y') {
            cout << "Please enter data for both lists！" << endl;
            LinkList* List1 = new LinkList;
            List1->input();                                           //Enter the first linked list data
            while (judge_negative) {                                  //Determine if a nagative number has been entered
                cout << "Illegal input, negative number exists, please re-enter this list!" << endl;
                judge_negative = false;
                List1->input();
            }
            LinkList* List2 = new LinkList;
            List2->input();
            while (judge_negative) {                                  //Enter the second linked list data
                cout << "Illegal input, negative number exists, please re-enter this list!" << endl;
                judge_negative = false;
                List2->input();
            } 
            LinkList* inter_list = List1->Intersection(List1, List2); //Find the intersection of two linked lists
            inter_list->display();
            cout << endl;
            cout << "Do you want to enter the intersection test?(y or n)" << endl;
            cin >> answer;
            while (1) {
                if (answer[0] != 'y' && answer[0] != 'Y' && answer[0] != 'n' && answer[0] != 'N') {
                    cout << "Invalid input! Please enter y or n!" << endl;
                    cin >> answer[0];
                }
                else
                    break;
            }
        }
        else
            break;
    }
}

LinkList::LinkList() {
    head = new LinkNode(-1);
    if (head == NULL) {
        cerr << "storage allocation error!" << endl;
        exit(1);
    }
}
LinkList* LinkList::Intersection(LinkList* list1, LinkList* list2)
{
    LinkList* newlist = new LinkList;
    LinkNode* p = list1->head;
    LinkNode* q = list2->head;
    LinkNode* r = newlist->head;
    while (p != NULL && q != NULL) {
        if (p->data > q->data)
            q = q->link;
        else if (q->data == p->data) {
            LinkNode* newnode = new LinkNode(p->data); //Create a new node with p->data and point the r link to it to get the node into the list
            r->link = newnode;
            r = r->link;
            p = p->link;
            q = q->link;
        }
        else
            p = p->link;
    }
    LinkNode* m = newlist->head;
    newlist->head = newlist->head->link;       //The data is stored at the next node of the node from scratch
    delete m;
    m = NULL;                                 //delete the head node of the newlist
    return newlist;
}

void LinkList::input() {
    int num;
    while (1) {                              //Determine if the input is a number
        cin >> num;
        if (cin.good() == false) {
            cout << "Input error!" << endl;
            while (getchar() != '\n')
                ;
            cin.clear();
            cout << "Please enter this list again:";
        }
        else
            break;
    }
    if (num == -1)
        return;
    if (num <= 0)
        judge_negative = true;
    LinkNode* p = new LinkNode(num);
    if (p == NULL) {
        cerr << "Storage allocation error!\n";
        exit(1);
    }
    head = p;
    while (1) {
        cin >> num;
        if (cin.good() == false) {
            cout << "Input error!" << endl;
            while (getchar() != '\n')
                ;
            cin.clear();
            cout << "Please enter this list again:";
        }
        else
            break;
    }
    while ( num != -1) {
        if (num <= 0)
            judge_negative = true;
        LinkNode* q = new LinkNode(num);
        p->link = q;
        p = p->link;
        while (1) {
            cin >> num;
            if (cin.good() == false) {
                cout << "Input error!" << endl;
                while (getchar() != '\n')
                    ;
                cin.clear();
                cout << "Please enter this list again:";
            }
            else
                break;
        }
    }
    return;
}

void LinkList::display() {
    LinkNode* p = head;
    if (p == NULL)
        cout << "NULL" << endl;
    while (p != NULL && p->link != NULL) {//Make sure there is no extra space at the end
        cout << p->data << " ";
        p = p->link;
    }
    if (p && p->link == NULL)
        cout << p->data;
}