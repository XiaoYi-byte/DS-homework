#pragma once
#ifndef COURSEARRANGING
#define COURSEARRANGING
#include<string>


using namespace std;

const int DefaultVertices = 50;
string classTime[4] = { "1-2节课","3-5节课","6-7节课","8-10节课" };
string timeTable[8][5][4] = { "" };//课表三维数组，储存课程的名字，8表示8个学期，5表示5个工作日，4表示4个上课时间段


typedef struct Edge {        //表示邻接表的的边
	int dest;                //边指向的终点
	Edge* link;              //指向的下一条边
	Edge() {                  //构造函数
		dest = -1;
		link = NULL;
	}
	Edge(int num) :dest(num), link(NULL) {}//构造函数
}Edge;

typedef struct ScheduledTime {
	int Semester;                        //课程的所在学期             
	int target;                          //表示课程是否已经被安排好了学期，1表示安排好了，0表示未安排好
	ScheduledTime() :Semester(0), target(0) {}//构造函数
	ScheduledTime(int courseSemester) :Semester(courseSemester), target(0) {};//构造函数
}ScheduledTime;


typedef struct Course {
	int _Weekday1 = -1;                   //课程的第一个所在工作日
	int _Time1 = -1;                      //课程的第一个所在时间段
	int _Weekday2 = -1;                   //课程的第二个所在工作日（有些课程有，有些没有）
	int _Time2 = -1;                      //课程的第二个所在时间段
	int count = 0;                        //入度数组兼入度为零顶点栈，即该课程的先修课程数量，用于拓扑排序
	int counter = 0;                      //值和count相同，但用于安排课程，因为count在拓扑排序时值已经改变
	string courseNumber;                  //课程序号
	string courseName;                    //课程名称
	string advancedCourse1, advancedCourse2;//先修课名称，若没有则为""
	int courseHours;                       //课时
	ScheduledTime scheduledTime;           //ScheduledTime类型，用于存储课程学期
	Edge* adj;                             //邻接表的头指针
	Course() :courseHours(0), adj(NULL) {}    //构造函数
	Course(ScheduledTime scheduled_time, string number = "NULL", string name = "NULL", string advanced_course1 = "NULL",
		string advanced_course2 = "NULL", int hours = 0, Edge* edge = NULL);//构造函数
	Course(const Course& vertex) {         //复制构造函数
		courseNumber = vertex.courseNumber;
		courseName = vertex.courseName;
		advancedCourse1 = vertex.advancedCourse1;
		advancedCourse2 = vertex.advancedCourse2;
		courseHours = vertex.courseHours;
		adj = vertex.adj;
		adj->dest = vertex.adj->dest;
		adj->link = vertex.adj->link;
		scheduledTime = vertex.scheduledTime;
	}
	bool operator==(const Course& vertex) {//判断两课程节点是否相同
		return courseNumber == vertex.courseNumber ? true : false;
	}
}Course;

class Graphlnk {                           //图，用邻接表存储
private:
	int maxVertices;                       //最大节点数量
	int numEdges;                          //边数量
	int numVertices;                       //节点数量
	Course* NodeTable;                     //存储各个课程的数组
	Course* TopologicalArray;              //拓扑排序后存储拓扑序列的数组
	int getVertexPos(const string number) {//通过课程序号得到课程在NodeTable数组中的位置
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].courseNumber == number)
				return i;
		return -1;
	}
public:
	Graphlnk(int sz = DefaultVertices);     //构造函数
	~Graphlnk();                            //析构函数
	void readFile();                        //读文件并
	bool insertVertex(const Course& course);//插入新课程节点
	bool insertEdge(int v, int w);           //在两课程节点间插入边，由v指向w
	int getFirstNeightbor(int v);           //取下标为v课程的邻接表的第一个节点的下标
	int getNextNeighbor(int v, int w);       //取下标为v课程的邻接表的除w以外的第一个节点的下标
	void Topological();                     //进行拓扑排序并安排课表，写入文本文件
};


#endif // !COURSEARRANGING
