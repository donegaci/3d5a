#include "MinHeap.c"
#include <string.h>
#define NUMBER_VERTICES 7667 // there aren't this many stops but it easier 
#define MAX_BUFFER 50

// typedef struct Node Node;
// struct Node{
//     int stopID;
//     int weight;
//     Node* next;
// };
typedef struct Node Node;
struct Node{
    int stopID;
    char name[MAX_BUFFER];
    int latitude;
    int longitude;
    int weight;
    Node* next;
};
typedef struct Graph Graph;
struct Graph{
    int numVertices;
    int previous[NUMBER_VERTICES];
    Node* array[NUMBER_VERTICES]; 
};


void initialiseGraph(Graph* graph);
void loadNode(FILE* f, Graph* graph);
void printGraph(Graph* graph);
int nextField(FILE* f, char *buf, int max);
void loadEdges(Graph* graph);
void insertEdge(FILE* f, Graph* graph);
Node* createNode(Graph* g, int destinaton, int weight);



int main(){
    
    Graph * graph = malloc(sizeof(Graph));
    initialiseGraph(graph);
    loadEdges(graph);

    printGraph(graph);

    return 0;
}


void initialiseGraph(Graph* graph){
    FILE* f;
    // Initialise the array to NULL
    for(int i= 0; i < NUMBER_VERTICES; i++){
        graph->array[i] = NULL;
    }

    f =fopen("vertices.csv", "r");

    if (f) {
        loadNode(f, graph); // discard header row
        while (!feof(f)){
            loadNode(f, graph);
        }  
    }
    else
        printf("Error opening VERTICES file.\n");
    fclose(f);
}


void loadNode(FILE *f, Graph* graph){
    char buffer [MAX_BUFFER];
    
    Node* newNode= (Node*)malloc(sizeof(Node*));

    nextField(f, buffer, MAX_BUFFER);
    newNode->stopID = atoi(buffer);
    nextField(f, newNode->name, MAX_BUFFER);
    nextField(f, buffer, MAX_BUFFER);
    newNode->latitude = atoi(buffer);
    nextField(f, buffer, MAX_BUFFER);
    newNode->longitude = atoi(buffer);
    newNode->next = NULL;

    // load the new Node into the array of Nodes
    graph->array[newNode->stopID] = newNode;
}


void printGraph(Graph* graph){
    printf("StopID \t Name\n");
     for(int i= 0 ; i<NUMBER_VERTICES; i++){
        Node* temp = graph->array[i];
        if (temp){
            printf("%d \t %s ->", temp->stopID, temp->name);
            // temp = temp->next;
            // while(temp){
            //     printf("%d \t %s ->", temp->stopID, temp->name);
            //     temp = temp->next;
            // }
        }
        printf("\n");
    }
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

Node* createNode(Graph* g, int destinaton, int weight){
    Node* newNode= (Node*)malloc(sizeof(Node*));
    newNode->stopID = destinaton;
    newNode->weight = weight;
    newNode->next = NULL;
    strcpy(newNode->name, g->array[destinaton]->name);
    newNode->latitude = g->array[destinaton]->latitude;
    newNode->longitude = g->array[destinaton]->longitude;
    return newNode;
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

    Node* newNode = createNode(graph, dest, weight);

    // Node* current = graph->array[source]->next;
    // Node* prev = graph->array[source]->next;

    // while(current != NULL ){
    //     prev = current;
    //     current = current->next;
    // }

    // prev->next = newNode;

    // newNode->next = graph->array[source];
    // graph->array[source]->next = newNode;
}