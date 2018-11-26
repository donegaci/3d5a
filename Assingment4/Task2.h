#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
    int vertex;
    int distance;
    Node* next;
};
typedef struct Graph Graph;
struct Graph{
    int numVertices;
    int* visited;
    Node** array; // 2d array basically
};
typedef struct MinHeapNode MinHeapNode;
struct MinHeapNode{
    int vertex;
    int distance;
};
typedef struct MinHeap MinHeap;
struct MinHeap{
    int capacity;
    int occupied; // number of nodes present
    int *position;
    MinHeapNode** array;
};

Node* createNode(int name, int dist);
Graph* createGraph(int nVertices);
void initialiseGraph(Graph* graph);
void insertEdge(Graph* graph, int source, int dest, int weight);
void printGraph(Graph* graph);
void depthFirstSearch(Graph* graph, int vertex);
void setNotVisited(Graph* graph);
// MinHeapNode* createMinHeapNode(int vertex, int distance);
// MinHeap* createMinHeap(int capacity);
// int isMinHeapEmpty(MinHeap* heap);
void dijkstra(Graph* graph, int source, int dest);
