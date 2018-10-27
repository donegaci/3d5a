#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int HASH_TABLE_SIZE  = 53;
const int MAX_BUFFER = 40;

typedef struct chainNode chainNode;
struct chainNode{
    char firstname[40];
    chainNode* next;
};

typedef struct Hash Hash;
struct Hash{
    char surname[40];
    chainNode* head;

};
//Person ID,Deposition ID,Surname,Forename,Age,Person Type,Gender,Nationality,Religion,Occupation
//13191,838198r247,"McGee","Bryan",28,"Deponent","Male","Unknown","Unknown","Husbandman"


void initialiseTable(Hash *hashTable);
int hash2(char *s);
int hash3(char *s);
int addToHashTable(char *surname, char* firstname,  Hash *hashTable);
int next_field(FILE *f, char *buf, int max);
void userSearch(Hash *hashTable);
void printHashTable(Hash *hashTable, int size);
void printTableStats(Hash *hashTable, int size,  int numCollisions, int numTerms );
void freeHashTable(Hash *hashTable, int size);


int main()
{
    FILE *f;
    char buffer[MAX_BUFFER];
    Hash hashTable[HASH_TABLE_SIZE];
    int totalCollisions = 0;
    int numTerms = 0;
    char surname[MAX_BUFFER];
    char forename[MAX_BUFFER];
    

    initialiseTable(hashTable);

    f = fopen("truncated.csv", "r");
    if (f) {
        while (!feof(f)){
            for(int i=0; i<3; i++){
                next_field(f, buffer, MAX_BUFFER);
            }
            strcpy(surname, buffer);
            //printf("Surname: %s\n", buffer);
            next_field(f, buffer, MAX_BUFFER);
            strcpy(forename, buffer);

            totalCollisions = totalCollisions + addToHashTable(surname, forename, hashTable);
            //printf("Forename: %s\n\n", buffer);
            for(int i=0; i<6; i++){
                next_field(f, buffer, MAX_BUFFER);
            }
            // int returnValue = next_field(f, buffer, MAX_BUFFER);
            // if (returnValue == 0){
            //     printf("%s\n", buffer);
            //     // totalCollisions = totalCollisions + addToHashTable(buffer, hashTable);
            //     // numTerms++;
            // }
        }
    }
    else
        printf("Error opening file.\n");


    printTableStats(hashTable, HASH_TABLE_SIZE, totalCollisions, numTerms);
    printHashTable(hashTable, HASH_TABLE_SIZE);
    userSearch(hashTable);
    freeHashTable(hashTable, HASH_TABLE_SIZE);
    return 0;
}


void initialiseTable(Hash *hashTable){
    for (int i=0; i<HASH_TABLE_SIZE; i++){
    strcpy(hashTable[i].surname, "");
    hashTable[i].head = NULL;
    }
}


int hash2(char *s){
    int hash = 0;
    int count = 1;
    while (*s) {
        hash = hash + (*s * count*10);
        s++;
        count++;
    }
    return (hash % HASH_TABLE_SIZE);
}


int hash3(char *s){
    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    hash = 1 + (hash % (HASH_TABLE_SIZE - 1));
    return hash;
}


/* This function will return the number of collisions that occured */
int addToHashTable(char *surname, char* firstname,  Hash *hashTable){
    int index = hash2(surname);
    int numCollisions = 0;

    /* Check that the cell in hash table is either empty or contains the same surname */
    if (strcmp(hashTable[index].surname, surname) == 0 || hashTable[index].head == NULL){

        /* Add the first node in the chain*/
        if(hashTable[index].head == NULL){
            strcpy(hashTable[index].surname, surname);
            chainNode *newNode= (chainNode*)malloc(sizeof(chainNode));
            hashTable[index].head = newNode;
            strcpy(newNode->firstname, firstname);
            newNode->next = NULL;
        }
    
        /*Add a node to an already exsisting chain */
        else{
            /* Traverse chain until you reach last node */
            chainNode *current =  hashTable[index].head;
            while (current->next != NULL){
                current = current->next;
            }
            chainNode *newNode= (chainNode*)malloc(sizeof(chainNode));
            current->next = newNode;
            strcpy(newNode->firstname, firstname);
            newNode->next = NULL;
        }
        
    }
    /* Deal with collision */
    else { 
        /* Loop to find a free cell or a cell with the same key */
        while (hashTable[index].head != NULL){ // || strcmp(hashTable[index].surname, surname) ){ 
            /* Ensure we don't go out of bounds of array */
            if ((index + hash3(surname)) < HASH_TABLE_SIZE)
                index += hash3(surname);
            else
                index = (index + hash3(surname)) - HASH_TABLE_SIZE;
            numCollisions++;
        }
        strcpy(hashTable[index].surname, surname);
        chainNode *newNode= (chainNode*)malloc(sizeof(chainNode));
        hashTable[index].head = newNode;
        strcpy(newNode->firstname, firstname);
        newNode->next = NULL;
    }
    return numCollisions;
}


int next_field(FILE *f, char *buf, int max){
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


void userSearch(Hash *hashTable) {
    char userInput[MAX_BUFFER];
    int index;
    
    /* Allow user to search for a surname in the table */
    printf("\nEnter surname to get firstnames or type 'quit' to escape \n");
    while (1) {
        scanf("%s", userInput);
        if (strcmp(userInput, "quit") == 0)
            break;
        index = hash2(userInput);
        if (hashTable[index].head != NULL){
            printf(">> %s ", hashTable[index].surname);
            chainNode *current = hashTable[index].head;
            while(current != NULL){
                printf(">> firstname: %s, ", current->firstname);
                current = current->next;
            }
            printf("\n");
        } 
        else
            printf("%s is not in the hash table\n", userInput);
    }
}


void printHashTable(Hash *hashTable, int size){
    for(int i=0; i<size; i++){
        printf("surname: %s ", hashTable[i].surname);
        
        chainNode *current = hashTable[i].head;
        while(current != NULL){
            printf(">> firstname: %s, ", current->firstname);
            current = current->next;
        }
        printf("\n");
    }
}


void printTableStats(Hash *hashTable,int size,  int numCollisions , int numTerms  ){
    int numCells = 0;

    /* Cound the number of occupied cells in hash table */
    for (int i=0; i<HASH_TABLE_SIZE; i++){
        if (hashTable[i].head != NULL)
            numCells ++;
    }

    printf("\nCapacity: %d\n", size);
    printf("Number of Terms: %d\n", numTerms);
    printf("Number of cells occupied: %d\n", numCells);
    printf("Collisions: %d\n", numCollisions);
    printf("Load: %.3f\n", ((double)numCells / (double)HASH_TABLE_SIZE) );
}


void freeHashTable(Hash *hashTable, int size){
    chainNode *current, *next;

    for(int i=0; i<size; i++){
        if(hashTable[i].head != NULL){
            current = hashTable[i].head;
            while(current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
        }
        hashTable[i].head = NULL;
    }
}