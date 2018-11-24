#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // to use function tolower()

typedef struct Node Node;
struct Node{
    int vertex; // I will represent ascii characters as integers
    Node* next;
};

// typedef struct AdjList AdjList;
// struct AdjList{
//     Node* head;
// };

typedef struct Graph Graph;
struct Graph{
    int numVertices;
    Node** array;
};

Node* createNode(char name);
Graph* createGraph(int nVertices);
void initialiseGraph(Graph* graph);
void insertEdge(Graph* graph, char source, char dest );
void printGraph(Graph* graph);


int main(){

    // Call this function to allocate memory for the graph
    Graph* graph = createGraph(6);
    // I call this function to create edges in my graph
    initialiseGraph(graph);
    
    printGraph(graph);

    return 0;
}


Node* createNode(char name){
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

    for(int i=0; i<nVertices; i++)
        graph->array[i] = NULL;

    return graph;
}


void initialiseGraph(Graph* graph){
    insertEdge(graph, 'A', 'B');
    insertEdge(graph, 'A', 'E');
    insertEdge(graph, 'A', 'D');
    insertEdge(graph, 'B', 'C');
    insertEdge(graph, 'C', 'B');
    insertEdge(graph, 'B', 'D');
    insertEdge(graph, 'C', 'D');
    insertEdge(graph, 'D', 'F');
    insertEdge(graph, 'F', 'C');
    insertEdge(graph, 'E', 'D');
}


void insertEdge(Graph* graph, char source, char dest ){
    // Covert all chars to lower case and subtract the ascii value of 'a'
    // so that a=0, b=1, c=2, ... etc.
    int srcIndex = tolower(source) - 'a';

    Node* newNode = createNode(dest);
    newNode->next = graph->array[srcIndex];
    graph->array[srcIndex] = newNode;

}

void printGraph(Graph* graph){

    for(int i=0; i<graph->numVertices; i++){
        Node* temp = graph->array[i];
        printf("%c : ", (i+'A'));
        while(temp){
            printf(" -> %c", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

}