#include "Task2.h"
#include <limits.h>
#define INFINTY INT_MAX


int main(){

    // Call this function to allocate memory for the graph
    Graph* graph = createGraph(7);
    // I call this function to create edges and weights in my graph
    initialiseGraph(graph);
    printGraph(graph);

    dijkstra(graph, 'A', 'B');

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


void printPath(int source, int dist[], int prev[], int n) { 
    printf("Vertex \tDistance \tPath\n"); 
    int j;
    for (int i = 0; i < n; ++i) {        
    printf("%c \t %d \t\t", toLetter(i), dist[i]); 
        j = i;
        while(j!= toIndex(-1)){
            printf("%c <- ", toLetter(j));
            j = toIndex(prev[j]);
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
        addToHeap(heap, toLetter(v), distance[v]);
        previous[v] = -1; // previous is undefined 
    }
    // Distance from source to source is 0
    distance[toIndex(source)] = 0;
    // mark distance of source in the heap as 0 so it is extracted first
    heap->position[source] = source;
    decreaseDistance(heap, toIndex(source), 0);
    

    while(!isHeapEmpty(heap)){
        MinHeapNode* min = extractMin(heap);
        int u = min->vertex;
        permanent[count] = u;
        count++;

        // Traverse through all adjacent vertices of u and update 
        // their distance from source
        Node* temp = graph->array[toIndex(u)];
        while(temp){
            int v = temp->vertex;

            // If the distance to v is not permanent yet
            // and distance to v through u is less than previous

            if(isInMinHeap(heap, v) && distance[toIndex(u)] != INFINTY
                && (temp->distance + distance[toIndex(u)]) < distance[toIndex(v)])
                {
                    distance[toIndex(v)] = distance[toIndex(u)] + temp->distance;
                    decreaseDistance(heap, v, distance[toIndex(v)]);
                    previous[toIndex(v)] = u;
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
