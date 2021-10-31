#include "8_1951220_伊啸.h"

int main()
{
    test();
    return 0;
}

void test()
{
    cout << "**             电网模拟造价系统                 **" << endl;
    cout << "==================================================" << endl;
    cout << "**             A---创建电网顶点                 **" << endl;
    cout << "**             B---添加电网的边                 **" << endl;
    cout << "**             C---构造最小生成树               **" << endl;
    cout << "**             D---显示最小生成树               **" << endl;
    cout << "**             E---退出程序                     **" << endl;
    cout << "==================================================" << endl;
    Graphmtx graph;
    MinSpanTree MST;
    while (1) {
        cout << "\nPlease select the option : ";
        char option;
        cin >> option;
        while (option < 65 || option > 90) {
            cout << "Illegal input! Please enter the correct option: (A to E) ";
            cin >> option;
        }
        switch (option) {
        case 'A':
            cin >> graph;
            break;
        case 'B': {
            char vertex1, vertex2;
            int u, v, cost, count = 0;
            do {
                cout << "Please enter two vertices and their edges: (Input '?' as a ending symbol) ";
                cin >> vertex1 >> vertex2;
                if (graph.getVertexPos(vertex1) != -1 && graph.getVertexPos(vertex2) != -1) {//Determines whether the input is a positive integer
                    cin >> cost;
                    if (cin.good() == false || cost <= 0 || vertex1 == vertex2) {
                        while (getchar() != '\n')
                            ;
                        cin.clear();
                        cout << "Illegal input! " << endl;
                    }
                    else {
                        count++;
                        u = graph.getVertexPos(vertex1);
                        v = graph.getVertexPos(vertex2);
                        graph.InsertEdge(u, v, cost);
                    }
                }
                else if(vertex1!='?'||vertex2!='?')
                    cout << "The vertex doesn't exist!" << endl;
            } while (vertex1 != '?' && vertex2 != '?');
            int maxEdges = graph.NumberOfVertices() * (graph.NumberOfVertices() - 1) / 2;
            if (count > maxEdges) {
                cout << "Too many edges are entered!" << endl;
                system("pause");
                return;
            }
            break;
        }
        case 'C':
            char vertex;
            cout << "Please enter the starting vertex : ";
            cin >> vertex;
            while (1) {
                if (Prim(graph, vertex, MST)) {
                    cout << "Generate the Prim minimum spanning tree!" << endl;
                    break;
                }
                else {
                    cout << "Please re-enter the starting vertex : ";
                    cin >> vertex;
                }
            }
            break;
        case 'D':
            MST.display(graph);
            break;
        case 'E':
            system("pause");
            return;
        }
    }
}
Graphmtx::Graphmtx(int sz)
{
    maxVertices = sz;
    numEdges = 0;
    numVertices = 0;
    VerticesList = new char[maxVertices];
    Edge = new int* [maxVertices];
    for (int i = 0; i < maxVertices; i++)
        Edge[i] = new int[maxVertices];
    for (int i = 0; i < maxVertices; i++) {
        for (int j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : maxWeight;
    }
}
int Graphmtx::getFirstNeighbor(int v)
{
    if (v != -1) {
        for (int col = 0; col < numVertices; col++)
            if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
                return col;
    }
    return -1;
}
int Graphmtx::getNextNeighbor(int v, int w)
{
    if (v != -1 && w != -1) {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
                return col;
    }
    return -1;
}
bool Graphmtx::InsertVertex(const char& vertex)
{
    if (numVertices == maxVertices)
        return false;
    VerticesList[numVertices++] = vertex;
    return true;
}

bool Graphmtx::InsertEdge(int v1, int v2, int cost)
{
    if (v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight) {
        numEdges++;
        Edge[v1][v2] = Edge[v2][v1] = cost;
        return true;
    }
    else
        return false;
}
istream& operator>>(istream& input, Graphmtx& graph)
{
    cout << "Please enter the numbers of vertices : ";
    int numbers;
    char vertex;
    while (1) {
        input >> numbers;
        if (input.good() == false||numbers<=0) {
            while (getchar() != '\n')
                ;
            input.clear();
            cout << "Incorrect input! Please re-enter a positive integer: ";
        }
        else
            break;
    }
    cout << "Please enter the names of each vertex in turn: ";
    for (int i = 0; i < numbers; i++) {
        input >> vertex;
        graph.InsertVertex(vertex);
    }
    return input;
}

int MinSpanTree::Insert(MSTEdgeNode& item)
{
    if (n == maxsize)
        return 0;
    edgevalue[n++] = item;
    return true;
}
void MinSpanTree::display(Graphmtx& graph)
{
    cout << "The vertices and edges of the minimum spanning tree are: " << endl;
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << graph.VerticesList[edgevalue[i].tail] << "-<" << edgevalue[i].key << ">->" << graph.VerticesList[edgevalue[i].head] << "          ";
    }
    cout << endl;
}

MinHeap::MinHeap(int sz)
    : currentSize(0)
{
    maxHeapSize = (sz > DefaultVertices) ? sz : DefaultVertices;
    heap = new MSTEdgeNode[maxHeapSize];
    if (heap == NULL) {
        cerr << "storage allocation error!" << endl;
        exit(1);
    }
}
void MinHeap::siftDown(int start, int m)
{
    int i = start, j = 2 * i + 1;
    MSTEdgeNode temp = heap[i];
    while (j <= m) {
        if (j < m && heap[j] > heap[j + 1])
            j++;
        if (temp <= heap[j])
            break;
        else {
            heap[i] = heap[j];
            i = j;
            j = j * 2 + 1;
        }
        heap[i] = temp;
    }
}
void MinHeap::siftUp(int start)
{
    int j = start, i = (start - 1) / 2;
    MSTEdgeNode temp = heap[j];
    while (j > 0) {
        if (temp > heap[i])
            break;
        else {
            heap[j] = heap[i];
            j = i;
            i = (i - 1) / 2;
        }
        heap[j] = temp;
    }
}
bool MinHeap::Insert(const MSTEdgeNode& g)
{
    if (currentSize == maxHeapSize) {
        cerr << "Heap Full!" << endl;
        return false;
    }
    heap[currentSize] = g;
    siftUp(currentSize);
    currentSize++;
    return true;
}
bool MinHeap::RemoveMin(MSTEdgeNode& g)
{
    if (currentSize == 0) {
        cerr << "Heap Empty!" << endl;
        return false;
    }
    g = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDown(0, currentSize - 1);
    return true;
}

bool Prim(Graphmtx& G, const char u0, MinSpanTree& MST)
{
    MSTEdgeNode ed;
    int count = 1, v;
    int n = G.NumberOfVertices();
    int m = G.NumberOfEdgds();
    int u = G.getVertexPos(u0);
    if (u == -1) {
        cout << "This vertex doesn't exist!" << endl;
        return false;
    }
    MinHeap H(m);
    int* Vmst = new int[n];
    for (int i = 0; i < n; i++)
        Vmst[i] = 0;
    Vmst[u] = 1;
    do {
        v = G.getFirstNeighbor(u);
        while (v != -1) { //Repeatedly detect all adjacent vertices of U
            if (Vmst[v] == 0) { //If v is not in the spanning tree, (u, v) is added to the heap
                ed.tail = u;
                ed.head = v;
                ed.key = G.getWeight(u, v); //tail is in the tree, head is not
                H.Insert(ed);
            }
            v = G.getNextNeighbor(u, v); //Find the next adjacent vertex v of u
        }
        while (!H.IsEmpty() && count < n) {
            H.RemoveMin(ed); //Eject edge ed with minimum weight from the heap
            if (Vmst[ed.head] == 0) {
                MST.Insert(ed); //Add ed to the minimum spanning tree
                u = ed.head;
                Vmst[u] = 1;
                count++;
                break;
            }
        }
    } while (count < n);
    return true;
}