#pragma once
#ifndef BANK_H_
#define BANK_H_
class queue {
private:
	int rear, front;//Queue header and tail pointer
	int* element;//Queue array
	int maxsize;//The maximum number of elements a queue can hold
public:
	queue(int sz);//Constructor
	~queue() {};//Destructor
	bool Enqueue(const int& x);//If the queue is not full,enqueue x and return true,else return false
	bool Dequeue(int& x);//If the queue is not empty,dequeue the head element and return true,else return false
	bool getFront(int& x);//Return the head element of the queue by x
	void makeEmpty() { front = rear = 0; }//Make the queue empty
	bool IsEmpty()const { return (rear == front) ? true : false; }//Determine whether the queue is empty
	bool IsFull()const { return rear == maxsize ? true : false; }//Determine whether the queue is full
	int getSize()const { return rear - front; }//Return the size of the queue
};
typedef struct node {
	int data;
	node* link;
	node() :data(0), link(NULL) {}
	node(int number) :data(number), link(NULL) {}
}node;//Link node
struct linklist {
private:
	node* head;
public:
	linklist();
	~linklist() {};
	void Insert(int position, int number);//Insert number in the position
	void Bank_business(int);//Achieve the banking business function
	void display();
};
#endif