#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
struct Node {
    char data;
    Node *next;
};


void addNode(Node** list, char data);
void printList(Node* list);
void removeNode(Node **list, char data);
void deleteList(Node **list);
void reverseList(Node **list);


int main(){
    Node *head = NULL;

    addNode(&head, 'A');void reverseList(Node **list);

    addNode(&head, 'B');
    addNode(&head, 'C');
    addNode(&head, 'D');
    printList(head);

    // removeNode(&head, 'D');
    // printList(head);
    // removeNode(&head, 'B');
    // printList(head);
    // removeNode(&head, 'A');
    // printList(head);

    reverseList(&head);

    return 0;
}


void addNode(Node** list, char data){

    Node *new = (Node*)malloc( sizeof( Node ) );
    new->data = data;

    if (*list == NULL){ // the list is empty
        new->next = NULL;
        *list = new;
    }
}


void printList(Node* list){
    Node *current = list;

    while( current != NULL){
        printf("%c\n", current->data);
        current = current->next;
    }
}


void removeNode(Node **list, char data){
    Node *current = *list;
    Node *prev = NULL;
    int found = 0;

    while( current != NULL && !found){
        if (current->data == data){
            found = 1;
            //printf("Found\n");

            if (prev == NULL){ // the head has to be removed
                free(current);
            }
            else{
                prev->next = current-> next;
                free(current);
            }

        }
        prev = current;
        current = current->next;
    }
}


void deleteList(Node **list){
    Node *current = *list;
    Node *next = *list;

    while (current != NULL){
        next = current->next;
        printf("About to delete %c\n", current->data);
        free(current);
        current = next;
    }
}

void reverseList(Node **list){
    Node *current, *prev, *next;
    current = *list;
    prev = NULL; // this will be the tail initiallly

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

}