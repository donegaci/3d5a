#ifndef MIN_HEAP
#define MIN_HEAP
#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeapNode MinHeapNode;
struct MinHeapNode{
    int vertex;
    int distance;
};
typedef struct MinHeap MinHeap;
struct MinHeap{
    int capacity;
    int size; // number of nodes present
    int *position;
    MinHeapNode** array;
};

MinHeapNode* createMinHeapNode(int vertex, int distance);
MinHeap* createMinHeap(int capacity);
void swap(MinHeapNode** x, MinHeapNode** y);
void minHeapify(MinHeap* heap, int index);
int isHeapEmpty(MinHeap* heap);
MinHeapNode* extractMin(MinHeap* heap);
void addToHeap(MinHeap* heap, int v, int dist);
int parent(int i) {return (i-1)/2; }
int leftChild(int i) { return (2*i +1); } 
int rightChild(int i) {return (2*i+2); }
int isInMinHeap(MinHeap* heap, int v);
void decreaseDistance(MinHeap* heap, int v, int dist);
void printMinHeap(MinHeap* heap);

#endif