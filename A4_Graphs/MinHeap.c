/*
* Lots of the code in this file was taken from GeeksForGeeks website
* https://www.geeksforgeeks.org/binary-heap/
* https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
*/

#include "MinHeap.h"

MinHeapNode* createMinHeapNode(int vertex, int distance){
    MinHeapNode* new = malloc(sizeof(MinHeapNode));
    new->distance = distance;
    new->vertex = vertex;
    return new;
}

MinHeap* createMinHeap(int capacity){
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    minHeap->position = (int*)malloc(sizeof(int));
    return minHeap;
}

void swapHeapNode(MinHeapNode** x, MinHeapNode** y){
    MinHeapNode* temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(MinHeap* heap, int index){
    int left = leftChild(index);
    int right= rightChild(index);
    int min = index;

    if(left < heap->size && 
        heap->array[left]->distance < heap->array[min]->distance)
        min = left;

    if(right < heap->size && 
        heap->array[right]->distance < heap->array[min]->distance)
        min = right;

    if(min!= index){
        swapHeapNode(&heap->array[index], &heap->array[min]);
        minHeapify(heap, min);
    }
}

int isHeapEmpty(MinHeap* heap){
    return heap->size == 0; // return true (1) is size is 0
}


MinHeapNode* extractMin(MinHeap* heap){

    if(isHeapEmpty(heap))
        return NULL;
    if(heap->size == 1) { // only one item in the heap
        heap->size--;
        return heap->array[0];
    }

    //store the root and rempve it from the heap
    MinHeapNode* root = heap->array[0];
    // replace the root with the left most leaf
    MinHeapNode* lastNode = heap->array[heap->size -1]; 
    heap->array[0] = lastNode;

    //Update positon of last node
    heap->position[root->vertex - 'A'] = heap->size-1;
    heap->position[lastNode->vertex - 'A'] = 0;
    --heap->size;
    minHeapify(heap, 0);
    return root;
}

int isInMinHeap(MinHeap* heap, int v) 
{ 
   if (heap->position[v] < heap->size) 
        return 1; 
   return 0; 
} 

void printMinHeap(MinHeap* heap){
    for(int i=0; i< heap->size; i++) {
        printf("%c \t %d\n", heap->array[i]->vertex, heap->array[i]->distance);
    }
    printf("\n");
}

void addToHeap(MinHeap* heap, int v, int dist){
    if(heap->size == heap->capacity){
        printf("HEAP FULL. COULD NOT ADD\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    MinHeapNode * new = createMinHeapNode(v, dist);
    heap->array[i] = new;

    // Fix the min heap 
    while(i != 0 && 
            heap->array[parent(i)]->distance > heap->array[i]->distance){
        swapHeapNode(&heap->array[i], &heap->array[parent(i)] );
        i = parent(i);
    }
}

void decreaseDistance(MinHeap* heap, int v, int dist) 
{ 
    heap->array[v]->distance = dist;

    while(v != 0 && heap->array[parent(v)]->distance   
        > heap->array[v]->distance)
        {
            swapHeapNode(&heap->array[v],&heap->array[parent(v)]);
            v = parent(v);
        }
}