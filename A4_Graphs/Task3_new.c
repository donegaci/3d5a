#include <stdio.h>
#include <stdlib.h>
#include "MinHeap.c"
#include <limits.h>
#define INFINTY INT_MAX
#define SIZE 7670
#define MAX_BUFFER 50

typedef struct Node Node;
struct Node{
    int vertex;
    int distance;
    Node* next;
};
typedef struct Graph Graph;
struct Graph{
    int numVertices;
    int* previous;
    Node** array; // 2d array basically
};


Node* createNode(int name, int weight);
Graph* createGraph(int nVertices);
void insertEdge(FILE* f, Graph* graph);
void loadEdges(Graph* graph);
int nextField(FILE *f, char *buf, int max);
void printGraph(Graph* graph);
void printPath(int source, int dist[], int prev[], int n) ;
void dijkstra(Graph* graph, int source, int dest);




int main(){

    // Call this function to allocate memory for the graph
    Graph* graph = createGraph(SIZE);
    // I call this function to create edges and weights in my graph
    //initialiseGraph(graph);
    loadEdges(graph);
    printGraph(graph);

    dijkstra(graph, 300, 253);

    return 0;
}

Node* createNode(int name, int weight){
    Node* newNode= (Node*)malloc(sizeof(Node*));
    newNode->vertex = name;
    newNode->distance = weight;
    newNode->next = NULL;
    return newNode;
}

// This function will add all the vertices and edges at the start if program
Graph* createGraph(int nVertices){
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = nVertices;
    graph->array = malloc(nVertices * sizeof(Node*));
    graph->previous = malloc(nVertices * sizeof(int));

    // I want to be able to access my array with the chars so
    for(int i= 0; i < nVertices; i++){
        graph->array[i] = NULL;
    }
    return graph;
}


void loadEdges(Graph* graph){
    FILE* f;

    f =fopen("edges.csv", "r");

    if (f) {
        insertEdge(f, graph); // discard header row
        while (!feof(f)){
            insertEdge(f, graph);
        }  
    }
    else
        printf("Error opening  EDGES file.\n");

    fclose(f);
}

void insertEdge(FILE* f, Graph* graph){
    char buffer [MAX_BUFFER];
    int source, dest, weight;

    nextField(f, buffer, MAX_BUFFER);
    source = atoi(buffer);
    nextField(f, buffer, MAX_BUFFER);
    dest = atoi(buffer);
    nextField(f, buffer, MAX_BUFFER);
    weight = atoi(buffer);

    Node* newNode = createNode(dest, weight);

    newNode->next = graph->array[source];
    graph->array[source] = newNode;
}

int nextField(FILE *f, char *buf, int max){
    int i = 0, end = 0, quoted = 0;

    for (;;){
        buf[i] = fgetc(f); // fetch the next character from file
        // if we encounter quotes then flip our state and immediately fetch next char
        if (buf[i] == '"') {
            quoted = !quoted;
            buf[i] = fgetc(f);
        }
        // end of field on comma if we're not inside quotes
        if (buf[i] == ',' && !quoted)
            break;
        // end record on newline or end of file
        if (feof(f) || buf[i] == '\n'){
            end = 1;
            break;
        }
        // truncate fields that would overflow the buffer
        if (i < max - 1)
            ++i;
    }
    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}

void printGraph(Graph* graph){
     for(int i= 0 ; i<graph->numVertices; i++){
        Node* temp = graph->array[i];
        printf("%d : ", i);
        while(temp){
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


void printPath(int source, int dist[], int prev[], int n) { 
    printf("Vertex \tDistance \tPath\n"); 
    int j;
    for (int i = 0; i < n; ++i) {        
    printf("%c \t %d \t\t", i, dist[i]); 
        j = i;
        while(j!= -1){
            printf("%c <- ", j);
            j = prev[j];
        }
        printf("\n");
    }
} 


/* Pseudo code for dijkstra
*
*   for each vertex v in Graph:
*       distance[v] = infinty
*       previous[v] = undefined
*   distance[source] = 0
*   Q = all the vertices in the graph
*   while Q is not empty:
*       u = min in Q
*       extract u from Q
*   for each neighbour v of u:
*       alternative = distance[u] + distance_between(u, v)
*       if alternative < distance[v]
*            distance[v] = alternative
*            previous[v] = u
*/

void dijkstra(Graph* graph, int source, int dest){

    int size = graph->numVertices;
    // array to hold the minimum distance to each vertex from source
    int distance[size];
    // array to hold the previous vertex of each vertex
    int previous[size];

    // array to store the order that the ndoes were made permanent in
    int permanent[size];
    int count = 0;

    MinHeap* heap = createMinHeap(size);

    for(int v=0; v<size; v++){
        distance[v] = INFINTY; // Distances to unvisited vertices are infinite
        addToHeap(heap, v, distance[v]);
        previous[v] = -1; // previous is undefined 
    }
    // Distance from source to source is 0
    distance[source] = 0;
    // mark distance of source in the heap as 0 so it is extracted first
    heap->position[source] = source;
    decreaseDistance(heap, source, 0);
    

    while(!isHeapEmpty(heap)){
        MinHeapNode* min = extractMin(heap);
        int u = min->vertex;
        permanent[count] = u;
        count++;

        // Traverse through all adjacent vertices of u and update 
        // their distance from source
        Node* temp = graph->array[u];
        while(temp){
            int v = temp->vertex;

            // If the distance to v is not permanent yet
            // and distance to v through u is less than previous

            if(isInMinHeap(heap, v) && distance[u] != INFINTY
                && (temp->distance + distance[u]) < distance[v])
                {
                    distance[v] = distance[u] + temp->distance;
                    decreaseDistance(heap, v, distance[v]);
                    previous[v] = u;
                }

            temp = temp->next;
        }
    } 
    printPath(source, distance, previous, size);

    printf("Order made permanent\n");
    for(int i=0; i<size; i++)
        printf("%c ", permanent[i]);
    printf("\n");
}
