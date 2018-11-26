#include "Task2.h"


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

    // I want to be able to access my array with the chars so
    for(int i= 'A'; i < ('A' + nVertices); i++){
        graph->array[i] = NULL;
        graph->visited[i] = 0; // set visited to false
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
    newNode->next = graph->array[source];
    graph->array[source] = newNode;

    // Since this graph is undirected
    // Create edge from dest to source also
    newNode = createNode(source, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;

}

void printGraph(Graph* graph){

     for(int i= 'A'; i<('A' + graph->numVertices); i++){
        Node* temp = graph->array[i];
        printf("%c : ", i);
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

void setNotVisited(Graph* graph){
    for(int i= 'A'; i<('A' + graph->numVertices); i++)
        graph->visited[i] = 0;
}

// MinHeapNode* createMinHeapNode(int vertex, int distance){
//     MinHeapNode* new = malloc(sizeof(MinHeapNode));
//     new->distance = distance;
//     new->vertex = vertex;
//     return new;
// }
// MinHeap* createMinHeap(int capacity){

// }

void dijkstra(Graph* graph, int source, int dest){

}