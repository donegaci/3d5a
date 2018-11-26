#include "Task2.h"
#define MAX_SIZE 40


int main(){

    // Call this function to allocate memory for the graph
    Graph* graph = createGraph(7);
    // I call this function to create edges and weights in my graph
    initialiseGraph(graph);
    printGraph(graph);


    return 0;
}

Node* createNode(int name, int dist){
    Node* newNode= (Node*)malloc(sizeof(Node*));
    newNode->vertex = name;
    newNode->distance = dist;
    newNode->next = NULL;
    return newNode;
}

// This function will add all the vertices and edges at the start if program
Graph* createGraph(int nVertices){
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = nVertices;
    graph->array = malloc(nVertices * sizeof(Node*));
    graph->visited = malloc(nVertices * sizeof(int));
    graph->previous = malloc(nVertices * sizeof(int));

    // I want to be able to access my array with the chars so
    for(int i= 0; i < nVertices; i++){
        graph->array[i] = NULL;
        graph->visited[i] = 0; // set visited to false
        // graph->previous[i] = -1; // set previous to undefined
    }
    return graph;
}

void initialiseGraph(Graph* graph){
    insertEdge(graph, 'A', 'B', 1);
    insertEdge(graph, 'A', 'C', 3);
    insertEdge(graph, 'A', 'F', 10);
    insertEdge(graph, 'B', 'C', 1);
    insertEdge(graph, 'B', 'E', 5);
    insertEdge(graph, 'B', 'D', 7);
    insertEdge(graph, 'B', 'G', 2);
    insertEdge(graph, 'C', 'D', 9);
    insertEdge(graph, 'C', 'E', 3);
    insertEdge(graph, 'D', 'E', 2);
    insertEdge(graph, 'D', 'F', 1);
    insertEdge(graph, 'D', 'G', 12);
    insertEdge(graph, 'E', 'F', 2);
}

void insertEdge(Graph* graph, int source, int dest, int weight ){
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[toIndex(source)];
    graph->array[toIndex(source)] = newNode;

    // Since this graph is undirected
    // Create edge from dest to source also
    newNode = createNode(source, weight);
    newNode->next = graph->array[toIndex(dest)];
    graph->array[toIndex(dest)] = newNode;

}

void printGraph(Graph* graph){
     for(int i= 0 ; i<graph->numVertices; i++){
        Node* temp = graph->array[i];
        printf("%c : ", toLetter(i));
        while(temp){
            printf(" -> %c", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Recursive function
void depthFirstSearch(Graph* graph, int vertex) {

    Node* temp = graph->array[vertex];
    graph->visited[vertex] = 1;

    printf("%c ", vertex);

    while(temp){
        int edge = temp->vertex;
        if(graph->visited[edge] == 0) // if not visited
            depthFirstSearch(graph, edge);
        temp = temp->next;
    }
}

void resetGraph(Graph* graph){
    for(int i= 'A'; i<('A' + graph->numVertices); i++){
        graph->visited[i] = 0; // set visited to false
        graph->previous[i] = -1; // set previous to undefined
    }
}

// MinHeapNode* createMinHeapNode(int vertex, int distance){
//     MinHeapNode* new = malloc(sizeof(MinHeapNode));
//     new->distance = distance;
//     new->vertex = vertex;
//     return new;
// }

// MinHeap* createMinHeap(int capacity){
//     MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
//     minHeap->size = 0;
//     minHeap->capacity = capacity;
//     minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
//     return minHeap;
// }

// void addToMinHeap(MinHeap* heap, Node* vertex){
//     if(heap->size == heap->capacity){
//         printf("ERROR. HEAP FULL.\n");
//         return;
//     }
//     // Insert the new node at the end
//     MinHeapNode* new = createMinHeapNode(vertex->vertex, vertex->distance);
//     heap->size++;
//     int i = heap->size -1;
//     heap->array[i] = new;

//     // Repair min heap
//     // while youre not at the root item in heap and new is less than parent
//     while(i != 0 && heap->array[parent(i)] > heap->array[i]){ 
//         // swim the new node up
//         swap( &(heap->array[i]), &(heap->array[parent(i)]) );
//         i = parent(i);
//     }
// }

// int isHeapEmpty(MinHeap* heap){
//     return heap->size == 0; // return true (1) is size is 0
// }

// void printMinHeap(MinHeap* heap){
//     for(int i=0; i< heap->size; i++) {
//         int vertex = heap->array[i]->vertex;
//         printf("%c, ", vertex);
//     }
// }

// MinHeapNode* extractMin(MinHeap* heap){
//     if(isHeapEmpty(heap)){
//         printf("ERROR. Heap is empty.");
//         return NULL;
//     }
//     // store the root
//     MinHeapNode* root = heap->array[0];
//     // replace root node with last node
//     MinHeapNode* lastNode = heap->array[heap->size -1];
//     heap->array[0] = lastNode;
    
//     //Update size and repair the heap with heapify()
//     -- heap->size;
//     heapify(heap, 0);

//     return root;
// }

void dijkstra(Graph* graph, int source, int dest){

}