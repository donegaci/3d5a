#ifndef TASK2
#define TASK2

#include <stdio.h>
#include <stdlib.h>
#include "MinHeap.c"

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


Node* createNode(int name, int dist);
Graph* createGraph(int nVertices);
void initialiseGraph(Graph* graph);
void insertEdge(Graph* graph, int source, int dest, int weight);
void printGraph(Graph* graph);
int toIndex(char i) {return i - 'A';}
char toLetter(int i) {return i + 'A';}
void printPath(int source, int dist[], int prev[], int n) ;
void dijkstra(Graph* graph, int source, int dest);

#endif