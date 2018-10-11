#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int HASH_TABLE_SIZE  = 83;
const int MAX_BUFFER = 40;

typedef struct Hash Hash;
struct Hash{
    int frequency;
    char name[40];
};

void initialiseTable(Hash *hashTable);
int hash(char *s);
int addToHashTable(char *s, struct Hash *hashTable);
int next_field(FILE *f, char *buf, int max);
void printHashTable(struct Hash *hashTable, int size);
void userSearch(Hash *hashTable);
void printTableStats(Hash *hashTable, int size, int numCollisions, int numTerms);


int main() {
    FILE *f;
    char buffer[MAX_BUFFER];
    char userInput[MAX_BUFFER];
    Hash hashTable[HASH_TABLE_SIZE];
    int totalCollisions = 0;
    int numTerms = 0;
    int index;

    initialiseTable(hashTable);

    f = fopen("names.csv", "r");
    if (f) {
        while (!feof(f)){
            int returnValue = next_field(f, buffer, MAX_BUFFER);
            if (returnValue == 1){
                totalCollisions = totalCollisions + addToHashTable(buffer, hashTable);
                numTerms++;
            }
        }
    }
    else
        printf("Error opening file.\n");

    //printHashTable(hashTable, HASH_TABLE_SIZE );
    printTableStats(hashTable, HASH_TABLE_SIZE, totalCollisions, numTerms);
    userSearch(hashTable);
    return 0;
}


void initialiseTable(Hash *hashTable){
    for (int i=0; i<HASH_TABLE_SIZE; i++){
    strcpy(hashTable[i].name, "");
    hashTable[i].frequency = 0;
    }
}


int hash(char *s){
    int hash = 0;
    while (*s) {
        hash = hash + *s;
        s++;
    }
    return hash % HASH_TABLE_SIZE;
}


/* This function will return the number of collisions that occured */
int addToHashTable(char *s, Hash *hashTable){
    int index = hash(s);
    int numCollisions = 0;

    /* Check that the cell in hash table is either empty or contains the same name */
    if (hashTable[index].frequency == 0){
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment frequency by 1
    }
    else if (strcmp(hashTable[index].name, s) == 0 )
        hashTable[index].frequency = (hashTable[index].frequency + 1);
    /* Deal with collision */
    else { 
        /* Loop to find a free cell */
        while ( hashTable[index].frequency != 0 ){ 
            
            /* If we reach the end of the array, loop back to the first element */
            if(strcmp(hashTable[index].name, s) == 0 )
                break;
            if (index >= (HASH_TABLE_SIZE-1))
                index = 0;
            else
                index++;
        }
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment frequency by 1
        numCollisions++;
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


void printHashTable(Hash *hashTable, int size){
    for(int i=0; i<size; i++){
        printf("[%d] %s %d \n", i, hashTable[i].name, hashTable[i].frequency);
    }
}


/* Allow user to search for a name in the table */
void userSearch(Hash *hashTable) {
    char userInput[MAX_BUFFER];
    int index;
    
    printf("\nEnter name to get frequency or type 'quit' to escape \n");
    while (1) {
        scanf("%s", userInput);
        if (strcmp(userInput, "quit") == 0)
            break;
        index = hash(userInput);
        if (hashTable[index].frequency != 0)
            if (strcmp(hashTable[index].name, userInput) == 0)
                printf(">> %s %d\n", hashTable[index].name, hashTable[index].frequency);
            else{ 
                while(strcmp(hashTable[index].name, userInput) != 0) {
                    if (hashTable[index].frequency == 0)
                        break;
                    if (index >= (HASH_TABLE_SIZE-1))
                        index = 0;
                    else
                        index++;
                }
                printf(">> %s %d\n", hashTable[index].name, hashTable[index].frequency);
            }
        else
            printf("%s is not in the hash table\n", userInput);
    }
}

void printTableStats(Hash *hashTable, int size, int numCollisions, int numTerms){
    int numCells = 0;

    /* Cound the number of occupied cells in hash table */
    for (int i=0; i<HASH_TABLE_SIZE; i++){
        if (hashTable[i].frequency != 0)
            numCells ++;
    }

    printf("\nCapacity: %d\n", size);
    printf("Number of Terms: %d\n", numTerms);
    printf("Number of cells occupied: %d\n", numCells);
    printf("Collisions: %d\n", numCollisions);
    printf("Load: %.3f\n", ((double)numCells / (double)HASH_TABLE_SIZE) );
}