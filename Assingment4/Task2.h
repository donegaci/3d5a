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
    int* previous;
    Node** array; // 2d array basically
};
// typedef struct MinHeapNode MinHeapNode;
// struct MinHeapNode{
//     int vertex;
//     int distance;
// };
// typedef struct MinHeap MinHeap;
// struct MinHeap{
//     int capacity;
//     int size; // number of nodes present
//     // int *position;
//     MinHeapNode** array;
// };

Node* createNode(int name, int dist);
Graph* createGraph(int nVertices);
void initialiseGraph(Graph* graph);
void insertEdge(Graph* graph, int source, int dest, int weight);
void printGraph(Graph* graph);
void depthFirstSearch(Graph* graph, int vertex);
void resetGraph(Graph* graph);
// MinHeapNode* createMinHeapNode(int vertex, int distance);
// MinHeap* createMinHeap(int capacity);
// int parent(int i) {return (i-1)/2; }
// int left(int i) {return (2*i + 1); }
// int right(int i) {return (2*i + 2);}
// void addToMinHeap(MinHeap* heap, Node* vertex);
// int isHeapEmpty(MinHeap* heap);
// MinHeapNode* extractMin(MinHeap* heap);
// void printMinHeap(MinHeap* heap);
int toIndex(char i) {return i - 'A';}
char toLetter(int i) {return i + 'A';}
void dijkstra(Graph* graph, int source, int dest);

