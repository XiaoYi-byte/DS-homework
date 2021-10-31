#pragma once
//#ifndef GRID_H_
//#define GRID_H_
#include <cmath>
#include <iostream>
using namespace std;

using std::cin;
using std::istream;
using std::ostream;
const int DefaultVertices = 30;

void test();

class Graphmtx {
private:
    int maxVertices; //The max vertices in the graph
    int numEdges; //The numbers of the edges in the graph
    int numVertices; //The numbers of the vertices in the graph
    char* VerticesList; //The list of the vertices
    int** Edge; //Adjacency matrix
public:
    const int maxWeight = INT_MAX; //The maxWeight
    Graphmtx(int sz = DefaultVertices); //Constructor
    ~Graphmtx()
    { //Destructor
        delete[] VerticesList;  
        delete[]Edge;
    }
    bool GraphEmpty() const
    { //Determine if the graph is empty
        if (numEdges == 0)
            return true;
        else
            return false;
    }
    bool GraphFull() const
    { //Determine if the graph is full
        if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
            return true;
        else
            return false;
    }
    int getVertexPos(char vertex)
    { //Give the positions of vertex
        for (int i = 0; i < numVertices; i++)
            if (VerticesList[i] == vertex)
                return i;
        return -1;
    }
    int NumberOfVertices() { return numVertices; } //Give the numbers of the vertices
    int NumberOfEdgds() { return numEdges; } //Give the numbers of the edges
    int getWeight(int v1, int v2)
    { //Give the edge(v1,v2) weight
        return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
    }
    int getFirstNeighbor(int v); //Give the vertex v's neighbor
    int getNextNeighbor(int v, int w); //Give the next adjacency vertex of the adjacency vertex w of vertex v
    bool InsertVertex(const char& vertex); //Insert the vertex
    bool InsertEdge(int v1, int v2, int cost); //Insert an edge with a weight of cost between v1 and v2
    friend class MinSpanTree;
    friend istream& operator>>(istream& input, Graphmtx& graph); //Overload input function
    void makeEmpty() {
        delete[] VerticesList; 
        delete[]Edge;
    }
};

struct MSTEdgeNode { //The nodes of the minimum spanning tree
    int tail, head, key; //The two vertices of an edge and the weight of the edge
    MSTEdgeNode()
        : tail(-1)
        , head(-1)
        , key(0)
    {
    }
    bool operator<=(MSTEdgeNode& M) { return key <= M.key; }
    bool operator>(MSTEdgeNode& M) { return key > M.key; }
};
class MinSpanTree {
private:
    MSTEdgeNode* edgevalue; // an array of the minimum spanning tree
    int maxsize, n; //The maximum and current capacity of the array
public:
    MinSpanTree(int sz = DefaultVertices)
        : maxsize(sz)
        , n(0)
    { //Constructor
        edgevalue = new MSTEdgeNode[sz];
    }
    ~MinSpanTree() { delete[] edgevalue; } //Destructor
    int Insert(MSTEdgeNode& item); //Insert a node of the minimum spanning tree
    void display(Graphmtx& graph); //Output minimum spanning tree
};

class MinHeap { //Auxiliary heap
private:
    MSTEdgeNode* heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start, int m); //From start to m, adjust to the minimum heap downward
    void siftUp(int start); //From start to 0, adjust to the minimum heap upward
public:
    MinHeap(int sz = DefaultVertices);
    ~MinHeap() { delete[] heap; }
    bool Insert(const MSTEdgeNode& g);
    bool RemoveMin(MSTEdgeNode& g);
    bool IsEmpty() const
    {
        return (currentSize == 0) ? true : false;
    }
    bool IsFull() const
    {
        return (currentSize == maxHeapSize) ? true : false;
    }
};

bool Prim(Graphmtx& G, const char u0, MinSpanTree& MST); //Prim algorithm

//#endif GRID_H_
