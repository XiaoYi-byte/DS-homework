#include<iostream>
#include"5_1951220_伊啸.h"
using namespace std;
#define Maxsize 1000


int main() {
	cout << "Would you like to do the bank business?(y or n)";
	char answer[50];
	while (cin >> answer) {
		if ((answer[0] == 'y' || answer[0] == 'Y')) {
			cout << "Please enter the customer numbers:";
			int cust_numbers;
			while (1) {                      //Make sure you enter valid int variable data
				cin >> cust_numbers;
				if (cin.good() == false|| cust_numbers <= 0)
				{
					cout << "The number of customers is a positive integer, please enter valid data!" << endl;
					while (getchar() != '\n')
						;
					cin.clear();
				}
				else
					break;
			}
			while (cust_numbers <= 0) {
				cout << "The numbers of customers you enter should be a negative number. Please enter again:";
				while (1) {                      //Make sure you enter valid int variable data
					cin >> cust_numbers;
					if (cin.good() == false|| cust_numbers <= 0)
					{
						cout << "The number of customers should be a positive integer, please enter valid data!" << endl;
						while (getchar() != '\n')
							;
						cin.clear();
					}
					else
						break;
				}
			}
			linklist cust_link;
			int target;                  //Mark if there is a negative number
			for (int i = 0; i < cust_numbers; i++) {
				target = 0;
				int number = 0;
				cin >> number;
				if (cin.good() == false|| number <= 0) {
					cout << "The number should be a positive integer, please enter valid data!" << endl;
					target = 1;
					break;
				}
				else
					cust_link.Insert(i, number);
			}
			if (target == 0)
				cust_link.Bank_business(cust_numbers);
			while (getchar() != '\n') //Clear the input
				;
			cin.clear();
			cout << "Would you like to continue to do the bank business?(y or n)";
		}
		else if ((answer[0] == 'n' || answer[0] == 'N')) {
			system("pause");
			return 0;
		}
		else 
			cout << "Error input! Please enter y or n:";
	}
}

queue::queue(int sz = Maxsize) :rear(0), front(0), maxsize(sz) {
	element = new int[maxsize];
	if (element == NULL) {
		cerr << "Storage allocation error!" << endl;
		exit(1);
	}
}

bool queue::Enqueue(const int& x) {
	if (IsFull() == true) {
		return false;
	}
	element[rear] = x;
	rear++;
	return true;
}

bool queue::Dequeue(int& x) {
	if (IsEmpty() == true) {
		return false;
	}
	x = element[front];
	front++;
	return true;
}

bool queue::getFront(int& x) {
	if (IsEmpty() == true) {
		return false;
	}
	x = element[front];
	return true;
}

linklist::linklist() {
	head = new node;
	if (head == NULL) {
		cerr << "Storage allocation error!" << endl;
		exit(1);
	}
}

void linklist::Insert(int position, int number) {
	node* p = head;
	for (int i = 0; i < position; i++)
		p = p->link;
	node* newnode = new node(number);
	newnode->link = p->link;
	p->link = newnode;
}

void linklist::Bank_business(int numbers) {
	queue bank_queue_A, bank_queue_B;
	linklist* list = new linklist;
	node* p = head->link;
	node* q = list->head;
	while (p) {
		if (p->data % 2 == 1)
			bank_queue_A.Enqueue(p->data);//Odd numbers to queue A
		else
			bank_queue_B.Enqueue(p->data);//Even numbers to queue B
		p = p->link;
	}
	for (int i = 0; i < numbers; i++) {
		int Afirst, Asecond, Bfirst;
		if (!bank_queue_A.IsEmpty()) {    
			    //A processes two customers and A gives priority to output when Bprocesses one customer
			bank_queue_A.Dequeue(Afirst);
			node* newnode = new node(Afirst);
			newnode->link = q->link;           //Data is inserted into a new linked list
			q->link = newnode;
			q = q->link;
		}
		if (!bank_queue_A.IsEmpty()) {
			bank_queue_A.Dequeue(Asecond);
			node* newnode = new node(Asecond);
			newnode->link = q->link;
			q->link = newnode;
			q = q->link;
		}
		if (!bank_queue_B.IsEmpty()) {
			bank_queue_B.Dequeue(Bfirst);
			node* newnode = new node(Bfirst);
			newnode->link = q->link;
			q->link = newnode;
			q = q->link;
		}
	}
	list->display();
}

void linklist::display() {
	node* p = head->link;
	while (p->link) {
		cout << p->data << " ";
		p = p->link;
	}
	cout << p->data << endl;
}