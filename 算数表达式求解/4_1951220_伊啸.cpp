#include<iostream>
#include<cstring>
#include"4_1951220_伊啸.h"


using namespace std;

int isp(char);
int icp(char);


int main() {
	test();
	system("pause");
	return 0;
}

void test() {
	char ch;
	while (1) {
		cout << "Please enter the expression:";
		Calculator Calc(50);
		char element;
		queue queue_postfix;
		if (!queue_postfix.postfix()) {
			while (getchar() != '\n')
				;
			cin.clear();
			continue;
		}
		while (queue_postfix.IsEmpty() == false) {
			queue_postfix.Dequeue(element);
			if (isdigit(element))
				Calc.AddOperand(element - 48);  //Convert char type data into int type
			else {
				if (element != '=')
					Calc.DoOperator(element);   //Operate in operands
				else
					break;
			}
		}
		Calc.show();
		Calc.Clear();
		queue_postfix.makeEmpty();
		int target = 0;
		cout << "\nDo you want to continue?(y or n)";
		while (cin >> ch) {
			if (ch == 'n' || ch == 'N') {
				target = 1;
				break;
			}
			else if (ch == 'y' || ch == 'Y')
				break;
			else
				cout << "Please enter y or n!" << endl;
		}
		if (target == 1)
			break;
	}
}
queue::queue(int sz) :front(0), rear(0), maxsize(sz) {
	element = new char[maxsize];
	if (element == NULL) {
		cerr << "Storage allocation error!" << endl;
		exit(1);
	}
}//Constructor
bool queue::Enqueue(const char& x) {
	if (IsFull() == true) {
		cout << "The queue is full and can't be enqueued!" << endl;
		return false;
	}
	element[rear] = x;
	rear++;
	return true;
}//If the queue is not full,enqueue x and return true,else return false
bool queue::Dequeue(char& x) {
	if (IsEmpty() == true) {
		cout << "The queue is empty and can't dequeue!" << endl;
		return false;
	}
	x = element[front];
	front++;
	return true;
}//If the queue is not empty,dequeue the head element and return true,else return false
bool queue::getFront(char& x) {
	if (IsEmpty() == true) {
		return false;
	}
	x = element[front];
	return true;
}//Return the head element of the queue by x


template<class T>
stack<T>::stack(int sz) :top(-1), maxsize(sz) {
	elements = new T[maxsize];
	if (elements == NULL) {
		cerr << "Storage allocation error!" << endl;
		exit(1);
	}
}//Constructor
template<class T>
bool stack<T>::Push(const T& x) {
	if (IsFull()) {
		return false;
	}
	elements[++top] = x;
	return true;
}//Push the element x
template<class T>
bool stack<T>::Pop(T& x) {
	if (IsEmpty()) {
		return false;
	}
	x = elements[top--];
	return true;
}//Pop,and the poped element returned by x
template<class T>
bool stack<T>::getTop(T& x) {
	if (IsEmpty())
		return false;
	x = elements[top];
	return true;
}//Return the top element of the stack by x
void Calculator::Clear() {
	st.MakeEmpty();
}
void Calculator::AddOperand(int value) {
	st.Push(value);
}
bool Calculator::get2Operands(int& left, int& right) {
	if (st.Pop(right)) {
		if (st.Pop(left))
			return true;
	}
	return false;
}
void Calculator::DoOperator(char op) {
	int left, right, value;
	if (get2Operands(left, right) == true) {
		switch (op) {
		case'+': {
			value = left + right;
			st.Push(value);
			break;
		}
		case'-': {
			value = left - right;
			st.Push(value);
			break;
		}
		case'*': {
			value = left * right;
			st.Push(value);
			break;
		}
		case'/': {
			if (right != 0) {
				value = left / right;
				st.Push(value);
				break;
			}
			else {
				cout << "Divided by 0!" << endl;
				break;
			}
		}
		case'%': {
			if (right != 0) {
				value = left % right;
				st.Push(value);
				break;
			}
			else {
				cout << "Divided by 0!" << endl;
				break;
			}
		}
		case'^': {
			if (right == 0 && left == 0) {
				cout << "This operation is meaningless!";
				break;
			}
			else if (right < 0) {
				int val = 1;
				for (int i = 0; i < -right; i++)
					val *= left;
				value = 1 / val;
				st.Push(value);
				break;
			}
			else if (right >= 0) {
				int value = 1;
				for (int i = 0; i < right; i++)
					value *= left;
				st.Push(value);
				break;
			}
		}
		default:
			cout << "Operator error!" << endl;
			break;
		}
	}
	else
		cout << "Error getting operands!";
}
void Calculator::show() {
	int answer;
	if (st.getTop(answer))
		cout << answer;
}
bool queue::postfix()   //Convert the infix expression into a postfix expression and save it in the queue
{
	queue infix;
	stack<char> st_ch;
	char ch = '=', ch1, op;
	char ch_infix[20];
	st_ch.Push(ch);
	int i = 0;
	cin >> ch_infix[i];
	while (ch_infix[i] != '=') {
		if (ch_infix[i] == '+' || ch_infix[i] == '-' || ch_infix[i] == '*' || ch_infix[i] == '/' || ch_infix[i] == '^'
			|| ch_infix[i] == '%' || isdigit(ch_infix[i]) || ch_infix[i] == '(' || ch_infix[i] == ')') {
			infix.Enqueue(ch_infix[i]);
			i++;
			cin >> ch_infix[i];
		}
		else {
			cout << "The expression you entered contains error characters!" << endl;
			return false;
		}
	}
	infix = unary_operator(infix);//Operate unary operator
	if (!judge_infix(ch_infix)) {  //Determine whether the stack is full
		cout << "The infix expression is incorrect!" << endl;
		return false;
	}
	infix.Enqueue(ch);
	infix.Dequeue(ch);
	while (st_ch.IsEmpty() == false && ch != '=') {
		if (isdigit(ch)) {
			if (Enqueue(ch))
				infix.Dequeue(ch);
		}
		else {
			if (st_ch.getTop(ch1)) {
				if (isp(ch1) < icp(ch)) { //New input operator has high priority
					st_ch.Push(ch);
					infix.Dequeue(ch);
				}
				else if (isp(ch1) > icp(ch)) { //New input operator has low priority
					st_ch.Pop(op);
					Enqueue(op);
				}
				else {
					st_ch.Pop(op);
					if (op == '(')
						//The priority of the new input operator is the same as the priority of the operator at the top of the stack
						infix.Dequeue(ch);
				}
			}
		}
	}
	while (st_ch.IsEmpty() == false) {
		st_ch.Pop(ch1);
		Enqueue(ch1);
	}
	return true;
}
int isp(char ch)
{
	if (ch == '=')
		return 0;
	else if (ch == '(')
		return 1;
	else if (ch == '+' || ch == '-')
		return 3;
	else if (ch == '*' || ch == '/' || ch == '%')
		return 5;
	else if (ch == '^')
		return 7;
	else if (ch == ')')
		return 8;
	else
		return -1;
}
int icp(char ch)
{
	if (ch == '=')
		return 0;
	else if (ch == '(')
		return 8;
	else if (ch == '+' || ch == '-')
		return 2;
	else if (ch == '*' || ch == '/' || ch == '%')
		return 4;
	else if (ch == '^')
		return 6;
	else if (ch == ')')
		return 1;
	else
		return -1;
}
bool queue::judge_infix(char ch[]) {
	int temp = 0;                  //Determine if the parentheses match
	if (ch[0] == '*' || ch[0] == '/' || ch[0] == '%' || ch[0] == '^')//Determine if the first character is correct
		return false;
	for (int i = 0; i < strlen(ch); i++) {
		if (ch[i] == '(') {//Determine if the characters before and after the left parenthesis are correct
			if (ch[i + 1] == '/' || ch[i + 1] == '*' || ch[i + 1] == '%' || ch[i + 1] == '^')
				return false;
			else if (ch[i - 1] >= '0' && ch[i - 1] <= '9')
				return false;
			temp++;
		}
		else if (ch[i] == ')') {//Determine if the characters before and after the right parenthesis are correct
			if (i == 0)
				return false;
			else if (ch[i - 1] == '+' || ch[i - 1] == '-' || ch[i - 1] == '*' || ch[i - 1] == '/' || ch[i - 1] == '%' || ch[i - 1] == '^')
				return false;
			else if (ch[i + 1] >= '0' && ch[i + 1] <= '9')
				return false;
			temp--;
		}
	}
	if (temp == 0)
		return true;
	return false;
}
queue unary_operator(queue& Queue) {
	char elem, next_elem;
	queue unary;
	Queue.getFront(elem);
	if (elem == '+' || elem == '-') {    //If the first character is ‘+’ or ‘-’
		Queue.Dequeue(elem);
		Queue.getFront(next_elem);
		if (next_elem >= '0' && next_elem <= '9') {
			unary.Enqueue('0');          //Add the character ‘0’ to the queue so that the unary operator becomes a binary operator
			unary.Enqueue(elem);
		}
	}
	while (!Queue.IsEmpty()) {
		Queue.Dequeue(elem);
		if (Queue.getFront(next_elem)) {
			if ((next_elem == '+' || next_elem == '-') && (elem == '(')) {//The unary operator is preceded by parentheses
				unary.Enqueue('0');
			}
		}
		unary.Enqueue(elem);
	}
	return unary;
}