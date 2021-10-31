#pragma once
#ifndef CALCULATOR_H_
#define CALCULATOR_H_


void test();
class queue {
private:
	int rear, front;//Queue header and tail pointer
	char* element;//Queue array
	int maxsize;//The maximum number of elements a queue can hold
public:
	queue(int sz = 50);//Constructor
	~queue() {};//Destructor
	bool Enqueue(const char& x);//If the queue is not full,enqueue x and return true,else return false
	bool Dequeue(char& x);//If the queue is not empty,dequeue the head element and return true,else return false
	bool getFront(char& x);//Return the head element of the queue by x
	void makeEmpty() { front = rear = 0; }//Make the queue empty
	bool IsEmpty()const { return (rear == front) ? true : false; }//Determine whether the queue is empty
	bool IsFull()const { return rear == maxsize ? true : false; }//Determine whether the queue is full
	int getSize()const { return rear - front; }//Return the size of the stack
	bool postfix();//Convert an infix expression to a postfix expression
	bool judge_infix(char ch[]);//Determine the correctness of the infix expression
};
template<class T>
class stack {
private:
	T* elements;//Stack array
	int top;//A pointer to the top of the stack
	int maxsize;//The maxsize of the stack
public:
	stack(int sz = 50);//Constructor
	~stack() { delete[]elements; }//Destructor
	bool Push(const T& x);//Push the element x
	bool Pop(T& x);//Pop,and the poped element returned by x
	bool getTop(T& x);//Return the top element of the stack by x
	bool IsEmpty()const { return top == -1 ? true : false; }//Determine whether the stack is empty
	bool IsFull()const { return top == maxsize - 1 ? true : false; }//Determine whether the stack is full
	int getSize()const { return top + 1; }//Return the size of the stack
	void MakeEmpty() { top = -1; }//Make the stack empty
};
class Calculator {
private:
	stack<int> st;//Stack object definition
	bool get2Operands(int& left, int& right);//Pop two operands from the stack
public:
	Calculator(int sz) :st(sz) {}//Constructor
	~Calculator() {}//Destructor
	void DoOperator(char op);//Operate on two operands
	void AddOperand(int value);//Push the element value
	void Clear();
	void show();
};

queue unary_operator(queue& Queue);//Operate unary operator


#endif //CALCULATOR_H_
