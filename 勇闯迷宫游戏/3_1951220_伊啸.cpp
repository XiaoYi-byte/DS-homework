#include<iostream>
#include<ctime>
#include"3_1951220_伊啸.h"
using namespace std;
int main() {
	cout << "A brief description of the maze map: " << endl;
	cout << "\nMaze map is composed of 0 and 1, 0 means can go through, 1 means obstacle, can't go through!" << endl;
	cout << "\nThe maze map is randomly generated!" << endl;
	cout << "\nIf there is a complete path from start to finish, it prints the path, or it fails!" << endl;
	cout << "=======================================================================================\n" << endl;
	test();
	system("pause");
	return 0;
}
void test() {
	int maxsize;
	cout << "Please enter a number N to make it an N by N maze(n>3&&n<14): ";
	while (1) {
		cin >> maxsize;
		if (cin.good() == false || maxsize <= 3 || maxsize >= 14) {
			while (getchar() != '\n')
				;
			cin.clear();
			cout << "The data you entered is not a positive integer. Please re-enter:(n>3&&n<14): ";
		}
		else
			break;
	}
	int** Maze = new int* [maxsize];                //The map of the maze
	for (int i = 0; i < maxsize; i++) {
		Maze[i] = new int[maxsize];
	}
	int** mark = new int* [maxsize];                 //A secondary array that identifies the path traveled, the path traveled is marked as 1.
	for (int i = 0; i < maxsize; i++) {
		mark[i] = new int[maxsize];
	}
	for (int i = 0; i < maxsize; i++) {               //The mark array all starts at 0
		for (int j = 0; j < maxsize; j++) {
			mark[i][j] = 0;
		}
	}
	Initial(maxsize, Maze);
	cout << "The path of the maze:\n" << endl;
	Path(maxsize, Maze, mark, maxsize - 2, maxsize - 1);//For a forward output path, start at the end and toward the beginning
	if (mark[1][1])                                      //If the maze goes through
		cout << "<" << maxsize - 2 << "," << maxsize - 1 << ">" << endl;
	for (int i = 0; i < maxsize; i++) {
		delete[]Maze[i];
		delete[]mark[i];
	}
	delete[]mark;
	delete[]Maze;
}
void Initial(int maxsize, int* Maze[]) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < maxsize; i++) {
		for (int j = 0; j < maxsize; j++) {
			int target = rand() % 3;
			if (target == 0)
				Maze[i][j] = 1;
			else
				Maze[i][j] = 0;
		}
	}
	for (int i = 0; i < maxsize; i++) {
		Maze[0][i] = 1;
		Maze[maxsize - 1][i] = 1;
		Maze[i][0] = 1;
		Maze[i][maxsize - 1] = 1;
	}
	Maze[1][0] = Maze[1][1] = 0;                                        //Avoid being blocked at the entrance
	Maze[maxsize - 2][maxsize - 2] = Maze[maxsize - 2][maxsize - 1] = 0;//Avoid being blocked at the exit
	cout << "The maze map：" << endl;
	cout << "          Col 0   ";
	for (int i = 1; i < maxsize; i++) {
		cout << "Col " << i << "   ";
	}
	cout << endl;
	for (int i = 0; i < maxsize; i++) {
		cout << "\nRow " << i << "     ";
		for (int j = 0; j < maxsize; j++) {
			cout << Maze[i][j] << "       ";
		}
		cout << endl;
	}
	cout << endl;
}
int Path(int size, int* maze[], int* mark[], int x, int y) {
	int g, h;
	if (x == 1 && y == 0)                              //Reach the entrance
		return 1;
	for (int i = 0; i < 4; i++) {                      //Four directions:Up,down,left and right. Cycle four times
		g = x + _move[i].a;
		h = y + _move[i].b;
		if (maze[g][h] == 0 && mark[g][h] == 0) {
			mark[g][h] = 1;                            //Mark as having passed
			if (Path(size, maze, mark, g, h)) {
				cout << "<" << g << "," << h << "> ---> ";
				return 1;
			}
		}
	}
	if (x == size - 2 && y == size - 2)                    //If go back to the end
		cout << "No path in the maze!" << endl;
	return 0;
}