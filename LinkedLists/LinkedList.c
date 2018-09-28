#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
struct Node {
    char data;
    Node *next;
};


void addNode(Node** list, char data);
void printList(Node* list);

Node *head = NULL;

int main(){

    addNode(&head, 'A');
    addNode(&head, 'B');
    addNode(&head, 'C');
    addNode(&head, 'D');
    printList(head);

    return 0;

}


void addNode(Node** list, char data){
    if (head == NULL){ // the list is empty
        head = (Node*)malloc( sizeof( Node ) );
        head->data = data;
        head->next = NULL;
    }
    else{
        Node *oldHead = head;
        head = (Node*)malloc( sizeof( Node ) );
        head->data = data;
        head->next = oldHead;

    }
}

void printList(Node* list){
    Node *current = head;

    while( current != NULL){
        printf("%c\n", current->data);
        current = current->next;
    }
}