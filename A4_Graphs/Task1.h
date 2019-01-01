#include <stdio.h>
#include <stdlib.h>
#define MAX 50 

typedef struct Node Node;
struct Node{
    int vertex;
    Node* next;
};
typedef struct Graph Graph;
struct Graph{
    int numVertices;
    int* visited;
    Node** array; // 2d array basically
};
typedef struct Queue Queue;
struct Queue{
    int items[MAX];
    int front;
    int rear;
};

Node* createNode(int name);
Graph* createGraph(int nVertices);
void initialiseGraph(Graph* graph);
void insertEdge(Graph* graph, int source, int dest );
void printGraph(Graph* graph);
void depthFirstSearch(Graph* graph, int vertex);
Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int isEmpty(Queue* q);
void setNotVisited(Graph* graph);
void breadthFirstSearch(Graph* graph, int vertex);
