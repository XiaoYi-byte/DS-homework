#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include"9_1951220_伊啸.h"


using namespace std;

int main() {
	Graphlnk graph;
	graph.readFile();
	graph.Topological();
	cout << "课表已经排好了，写入的文本文件在文件夹中！" << endl;
	system("pause");
	return 0;
}
Course::Course(ScheduledTime scheduled_time, string number, string name, string advanced_course1, string advanced_course2, int hours, Edge* edge) {
	//Course的构造函数
	scheduledTime = scheduled_time;
	courseNumber = number;
	courseName = name;
	advancedCourse1 = advanced_course1;
	advancedCourse2 = advanced_course2;
	courseHours = hours;
	adj = edge;
}
Graphlnk::Graphlnk(int sz) {
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Course[maxVertices];
	TopologicalArray = new Course[maxVertices];
	if (NodeTable == NULL) {
		cerr << "storage allocation error!" << endl;
		exit(1);
	}
	if (TopologicalArray == NULL) {
		cerr << "storage allocation error!" << endl;
		exit(1);
	}
}
Graphlnk::~Graphlnk() {
	for (int i = 0; i < numVertices; i++) {
		Edge* p = NodeTable[i].adj;
		Edge* q = TopologicalArray[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
		while (q != NULL) {
			TopologicalArray[i].adj = q->link;
			delete q;
			q = TopologicalArray[i].adj;
		}
	}
	delete[]NodeTable;
	delete[]TopologicalArray;
}

void Graphlnk::readFile() {
	ifstream infile("C:\\Users\\yixiao\\Desktop\\9_1951220_伊啸\\courseInformation.txt", ios::in);
	//The file content
  /*c01			程序设计基础	5			0
	c02			离散数学		6			0					c01
	c03			数据结构算法	4			0					c01 c02
	c04			汇编语言		5			0					c01
	c05			算法设计		4			0					c03 c04
	c06			计算机组成原理	6			0
	c07			微机原理		4			0					c03
	c08			单片机应用		3			0					c03
	c09			编译原理		5			0					c03
	c10			操作系统原理	4			0					c03
	c11			数据库原理		5			0					c03
	c12			高等数学		6			0
	c13			线性代数		6			0
	c14			数值分析		6			0					c12
	c15			普通物理		4			0					c12
	c16			计算机文化		3			0
	c17			计算机系统结构	6			0					c06
	c18			计算机网络		5			0					c03
	c19			数据通信		6			0
	c20			面向对象程序设计 3			0					c01 c03
	c21			Java				3			0					c01 c03
	c22			C#.net			5			0					c01 c03
	c23			PowerBuilder		5			0					c01 c03
	c24			VC++			3			0					c01 c03
	c25			ASP程序设计		5			0					c01 c03
	c26			JSP程序设计		5			0					c01 c03
	c27			VB.net			5			0					c01 c03
	c28			Delphi			5			0					c01 c03
	c29			C++Builder		5			0					c01 c03
	c30			英语			5			1
	c31			英语			5			2
	c32			英语			5			3
	c33			英语			5			4
	c34			英语			5			5
	c35			英语			5			6
	c36			英语			5			7
	c37			英语			5			8
	c38			大学语文		3			1                                  */
	if (!infile.is_open()) {
		cout << "File opening failed" << endl;
		return;
	}
	string line;
	while (getline(infile, line)) { //一行一行读文件
		string courseNumber, courseName, advancedCourse1, advancedCourse2;
		int courseHours, courseSemester;
		istringstream iss(line);
		iss >> courseNumber >> courseName >> courseHours >> courseSemester >> advancedCourse1 >> advancedCourse2;
		ScheduledTime scheduledtime(courseSemester);
		Course course(scheduledtime, courseNumber, courseName, advancedCourse1, advancedCourse2, courseHours);//构造课程节点
		insertVertex(course);//插入课程节点
		if (advancedCourse1 != "") {
			int position1 = getVertexPos(advancedCourse1);
			insertEdge(position1, numVertices - 1);      //插入边
			NodeTable[numVertices - 1].count++;
			NodeTable[numVertices - 1].counter++;
		}
		if (advancedCourse2 != "") {
			int position2 = getVertexPos(advancedCourse2);
			insertEdge(position2, numVertices - 1);
			NodeTable[numVertices - 1].count++;
			NodeTable[numVertices - 1].counter++;
		}
	}
	infile.close();
	return;
}
bool Graphlnk::insertVertex(const Course& course) {
	if (numVertices == maxVertices) {
		return false;
	}
	NodeTable[numVertices] = course;
	numVertices++;
	return true;
}
int Graphlnk::getFirstNeightbor(int v) {
	if (v != -1) {
		Edge* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}
int Graphlnk::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
			p = p->link;
		if (p != NULL && p->link != NULL) {
			return p->link->dest;
		}
	}
	return -1;
}

bool Graphlnk::insertEdge(int v, int w) {
	if (v >= 0 && v < numVertices && w >= 0 && w < numVertices) {
		Edge* p = NodeTable[v].adj;
		while (p != NULL) {
			if (p->dest == w)
				return false;
			p = p->link;
		}
		Edge* newEdge = new Edge(w);   //在v和w之间构造一条新边，终点为w
		newEdge->link = NodeTable[v].adj;  //插入v的邻接表
		NodeTable[v].adj = newEdge;
		numEdges++;
		return true;
	}
	return false;
}
void Graphlnk::Topological() {
	int i, w, v;
	int number = 0;
	int top = -1;                                       //初始化一个入口度为零的顶点
	int n = numVertices;                                //网络中顶点的数量
	Course* TopologicalArray = new Course[maxVertices];   //用于储存拓扑排序结果的数组
	for (i = 0; i < n; i++) {                           //入度为零的顶点入栈
		if (NodeTable[i].count == 0) {
			NodeTable[i].count = top;
			top = i;
		}
	}
	for (i = 0; i < n; i++) {                           //循环n次，n课程总的数量
		if (top == -1) {                                //中途栈空
			cout << "There are loops in the network!" << endl;
			return;
		}
		else {
			v = top;
			top = NodeTable[top].count;                 //退栈
			TopologicalArray[number] = NodeTable[v];    //存入拓扑数组
			number++;
			w = getFirstNeightbor(v);                    //取v的第一个邻接顶点
			while (w != -1) {
				if (--NodeTable[w].count == 0) {        //扫描出边表
					NodeTable[w].count = top;
					top = w;                            //入度为零的节点入栈
				}
				w = getNextNeighbor(v, w);
			}
		}
	}
	for (i = 0; i < n; i++) {                            //标记安排好学期的节点
		if (TopologicalArray[i].scheduledTime.Semester != 0)
			TopologicalArray[i].scheduledTime.target = 1;
	}
	for (int term = 1; term < 9; term++) {
		/*按拓扑数组的顺序对counter为0的课程节点安排好学期、工作日、时间段，若counter为0但该学期已经安排不下该课程时，
		使其counter++，并入下一个学期进行安排*/
		int Time[5][4] = { 0 };                          //每个学期的工作日和时间段
		for (i = 0; i < n; i++) {
			if (TopologicalArray[i].counter == 0 && TopologicalArray[i].scheduledTime.target == 0) {
				TopologicalArray[i].scheduledTime.Semester = term;//先给未安排学期且counter为0的节点安排其学期为term
			}
		}
		for (i = 0; i < n; i++) {                        //排每个学期的课
			int k = 0, j = 0, l = 0;
			if (TopologicalArray[i].scheduledTime.Semester == term) {
				TopologicalArray[i].scheduledTime.target = 1;  //标记该节点已经安排好了学期
				switch (TopologicalArray[i].courseHours) {
				case 3: {
					for (j = 0; j < 5; j++) {
						for (k = 0; k < 4; k++) {
							if (Time[j][k] == 0 && k % 2 == 1) {
								Time[j][k] = 1;
								TopologicalArray[i]._Weekday1 = j;//记录工作日和时间段
								TopologicalArray[i]._Time1 = k;
								break;
							}
						}
						if (k < 4)
							break;
					}
					break;
				}
				case 4: {
					int count = 0, target = 0, record_j = -1, record_k = -1;
					for (j = 0;; j++) {
						if (j > 4) {
							j = j - 5;
							target++;
						}
						for (k = 0; k < 4; k++) {
							if (Time[j][k] == 0 && k % 2 == 0) {//k为奇数时为3节课，偶数时为2节课
								if (!count) {
									Time[j][k] = 1;
									record_k = k;
									record_j = j;
									count++;
									break;
								}
								else {
									Time[j][k] = 1;
									count++;
									break;
								}
							}
						}
						if (count == 1) {
							for (l = 0; l < 4; l++) {
								int t = ((j + 2 - 5) >= 0) ? (j + 2 - 5) : (j + 2);//检查隔一天后是否有空余时间段安排该课程
								if (Time[t][l] == 0 && l % 2)
									break;
							}
							if (l == 4) {
								count--;
								Time[j][k] = 0;
							}
						}
						if (count == 1)
							j++;//通过循环使j变为两天后
						if (target > 2) {               //循环3遍仍然没有结果，说明这个学期已经安排不下了
							Time[record_j][record_k] = 0;
							TopologicalArray[i].scheduledTime.Semester++;//该课程学期加一
							TopologicalArray[i].scheduledTime.target = 0;//target变为0，说明其学期未安排好
							break;
						}
						if (count == 2) {               //已经安排好了两天的课程，记录两个工作日和时间段
							TopologicalArray[i]._Weekday1 = record_j;
							TopologicalArray[i]._Time1 = record_k;
							TopologicalArray[i]._Weekday2 = j;
							TopologicalArray[i]._Time2 = k;
							break;
						}
					}
					break;
				}
				case 5: {  //思路同4，不同之处为学时为2+3或3+2
					int count = 0, target = 0, record_j = -1, record_k = -1;
					for (j = 0;; j++) {
						if (j > 4) {
							j = j - 5;
							target++;
						}
						for (k = 0; k < 4; k++) {
							if (Time[j][k] == 0) {
								if (!count) {
									Time[j][k] = 1;
									record_k = k;
									record_j = j;
									count++;
									break;
								}
								else {
									if (record_k % 2) {
										if (k % 2 == 0) {
											Time[j][k] = 1;
											count++;
											break;
										}
									}
									else {
										if (k % 2 == 1) {
											Time[j][k] = 1;
											count++;
											break;
										}
									}
								}
							}
						}
						if (count == 1) {
							for (l = 0; l < 4; l++) {
								int t = ((j + 2 - 5) >= 0) ? (j + 2 - 5) : (j + 2);
								if (Time[t][l] == 0 && l % 2 != record_k % 2)
									break;
							}
							if (l == 4) {
								count--;
								Time[j][k] = 0;
							}
						}
						if (count == 1)
							j++;
						if (target > 2) {
							Time[record_j][record_k] = 0;
							TopologicalArray[i].scheduledTime.Semester++;
							TopologicalArray[i].scheduledTime.target = 0;
							break;
						}
						if (count == 2) {
							TopologicalArray[i]._Weekday1 = record_j;
							TopologicalArray[i]._Time1 = record_k;
							TopologicalArray[i]._Weekday2 = j;
							TopologicalArray[i]._Time2 = k;
							break;
						}
					}
					break;
				}
				case 6: { //思路同4，学时为3+3
					int count = 0, target = 0, record_j = -1, record_k = -1;
					for (j = 0;; j++) {
						if (j > 4) {
							j = j - 5;
							target++;
						}
						for (k = 0; k < 4; k++) {
							if (Time[j][k] == 0 && k % 2) {
								if (!count) {
									Time[j][k] = 1;
									record_k = k;
									record_j = j;
									count++;
									break;
								}
								else {
									Time[j][k] = 1;
									count++;
									break;
								}
							}
						}
						if (count == 1) {
							for (l = 0; l < 4; l++) {
								int t = ((j + 2 - 5) >= 0) ? (j + 2 - 5) : (j + 2);
								if (Time[t][l] == 0 && l % 2)
									break;
							}
							if (l == 4) {
								count--;
								Time[j][k] = 0;
							}
						}
						if (count == 1)
							j++;
						if (target > 2) {
							Time[record_j][record_k] = 0;
							TopologicalArray[i].scheduledTime.Semester++;
							TopologicalArray[i].scheduledTime.target = 0;
							break;
						}
						if (count == 2) {
							TopologicalArray[i]._Weekday1 = record_j;
							TopologicalArray[i]._Time1 = record_k;
							TopologicalArray[i]._Weekday2 = j;
							TopologicalArray[i]._Time2 = k;
							break;
						}
					}
					break;
				}
				}
				if (TopologicalArray[i].scheduledTime.target == 1) {//以该课程为先修课的counter-1
					for (int m = 0; m < n; m++) {
						if (TopologicalArray[m].advancedCourse1 == TopologicalArray[i].courseNumber ||
							TopologicalArray[m].advancedCourse2 == TopologicalArray[i].courseNumber) {
							TopologicalArray[m].counter--;
						}
					}
				}
			}
		}
	}
	ofstream outfile("C:\\Users\\yixiao\\Desktop\\9_1951220_伊啸\\timeTable.txt", ios::out);
	for (i = 0; i < numVertices; i++) {//把所有课程节点的排课信息存入timeTable数组中，对应的为课程名称
		string Name = TopologicalArray[i].courseName;
		int weekday1 = TopologicalArray[i]._Weekday1;
		int _Class_time1 = TopologicalArray[i]._Time1;
		int weekday2 = TopologicalArray[i]._Weekday2;
		int _Class_time2 = TopologicalArray[i]._Time2;
		int semester = TopologicalArray[i].scheduledTime.Semester;
		if (semester > 0)
			timeTable[semester - 1][weekday1][_Class_time1] = Name;
		if (weekday2 > -1 && _Class_time2 > -1 && semester > 0)
			timeTable[semester - 1][weekday2][_Class_time2] = Name;
	}
	for (i = 0; i < 8; i++) { //输出timeTable
		outfile << right << setw(45) << "第" << i + 1 << "学期" << endl;
		outfile << setw(18) << "周一" << setw(22) << "周二" << setw(22) << "周三" << setw(22) << "周四" << setw(22) << "周五" << endl;
		for (int k = 0; k < 4; k++) {
			outfile << setw(10) << classTime[k] << "  : ";
			for (int j = 0; j < 5; j++) {
				if (timeTable[i][j][k] != "") {
					outfile << left << setw(22) << timeTable[i][j][k];
				}
				else
					outfile << "                    ";
			}
			outfile << endl;
		}
		outfile << endl;
	}
}