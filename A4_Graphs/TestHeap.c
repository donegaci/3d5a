#include "MinHeap.c"

int main(){

    int SIZE = 10;
    MinHeap* heap = createMinHeap(SIZE);

    addToHeap(heap, 'A', 10);
    addToHeap(heap, 'B', 1);
    addToHeap(heap, 'C', 7);
    addToHeap(heap, 'D', 0);
    addToHeap(heap, 'E', 50);
    printMinHeap(heap);

    for(int i=0; i<heap->size;i++){
        MinHeapNode* min = extractMin(heap);
        printf("%c \t %d \n", min->vertex, min->distance);
    }
}