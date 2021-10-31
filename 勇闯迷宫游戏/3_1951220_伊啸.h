#pragma once
#ifndef MAZE_H_
#define MAZE_H_

struct offsets {
	int a;
	int b;
};
offsets _move[4] = { {-1,0} ,{0, -1},{1,0}, {0,1} };//Displacement in the upper, right and lower directions

void test();//Run a maze test
void Initial(int maxsize, int* Maze[]);//Initializes the maze map
int Path(int size, int* maze[], int* mark[], int x, int y);//Find the path of the maze

#endif MAZE_H_
