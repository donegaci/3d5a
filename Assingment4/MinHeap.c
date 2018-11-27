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
    heap->array[0] = heap->array[heap->size -1]; // replace the root with the left most leaf
    heap->size--;
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
    // Get the index of v in  heap array 
    int i = heap->position[v]; 
  
    // Get the node and update its dist value 
    heap->array[i]->distance = dist; 
  
    // Travel up while the complete tree is not hepified. 
    // This is a O(Logn) loop 
    while (i && heap->array[i]->distance < heap->array[(i - 1) / 2]->distance) 
    { 
        // Swap this node with its parent 
        heap->position[heap->array[i]->vertex] = (i-1)/2; 
        heap->position[heap->array[(i-1)/2]->vertex] = i; 
        swapHeapNode(&heap->array[i],  &heap->array[(i - 1) / 2]); 
  
        // move to parent index 
        i = parent(i); 
    } 
}