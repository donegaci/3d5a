#include "Task1.h"

int main(){

    // Call this function to allocate memory for the graph
    Graph* graph = createGraph(6);
    // I call this function to create edges in my graph
    initialiseGraph(graph);
    
    printGraph(graph);

    printf("DFS: ");
    depthFirstSearch(graph,'A');
    printf("\n");

    printf("BFS: ");
    breadthFirstSearch(graph,'A');
    printf("\n");

    return 0;
}

Node* createNode(int name){
    Node* newNode= (Node*)malloc(sizeof(Node*));
    newNode->vertex = name;
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
    insertEdge(graph, 'A', 'E');
    insertEdge(graph, 'A', 'D');    
    insertEdge(graph, 'A', 'B');
    insertEdge(graph, 'B', 'D');
    insertEdge(graph, 'B', 'C');
    insertEdge(graph, 'C', 'D');
    insertEdge(graph, 'C', 'B');
    insertEdge(graph, 'D', 'F');
    insertEdge(graph, 'E', 'D');
    insertEdge(graph, 'F', 'C');
}

void insertEdge(Graph* graph, int source, int dest ){
    Node* newNode = createNode(dest);
    newNode->next = graph->array[source];
    graph->array[source] = newNode;
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

Queue* createQueue(){
    Queue* q = malloc(sizeof(Queue));
    // initialise pointers to empty
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue* q, int value){
    if(q->rear == MAX -1)
        printf("Queue is full \n");
    else{
        if(q->front == -1) // if it was empty
            q->front =0; // show that there is something in it
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty");
        return -1;
    }
    else{
        int value = q->items[q->front];
        q->front++;
        if(q->front > q->rear) // if there is nothing left
            q->front = q->rear = -1;
        return value;
    }
}

int isEmpty(Queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void setNotVisited(Graph* graph){
    for(int i= 'A'; i<('A' + graph->numVertices); i++)
        graph->visited[i] = 0;
}

void breadthFirstSearch(Graph* graph, int vertex){
    Queue* q = createQueue();

    setNotVisited(graph);

    graph->visited[vertex] = 1; // set current to visited
    enqueue(q, vertex);

    while(!isEmpty(q)){ // while not empty
        int current = dequeue(q);
        printf("%c ", current);

        Node* temp = graph->array[current];

        while(temp){
            int nextVertex = temp->vertex;

            if(graph->visited[nextVertex] == 0){ // if not already visited
                graph->visited[nextVertex] = 1;
                enqueue(q, nextVertex);
            }
            temp = temp->next;
        }
    }
}
