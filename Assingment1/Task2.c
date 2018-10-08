#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int HASH_TABLE_SIZE  = 73;
const int MAX_BUFFER = 40;

typedef struct Hash Hash;
struct Hash{
    int frequency;
    char name[40];
};

int hash(char *s);
int addToHashTable(char *s, struct Hash *hashTable);
int next_field(FILE *f, char *buf, int max);
void printHashTable(struct Hash *hashTable, int size);


int main()
{
    FILE *f;
    char buffer[MAX_BUFFER];
    char userInput[MAX_BUFFER];
    Hash hashTable[HASH_TABLE_SIZE];
    int totalCollisions = 0;
    int numTerms = 0;
    int numCells = 0;
    int index;

    /* Initialise name and frequency in hash table */
    for (int i=0; i<HASH_TABLE_SIZE; i++){
        strcpy(hashTable[i].name, "");
        hashTable[i].frequency = 0;
    }

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

    /* Cound the number of occupied cells in hash table */
    for (int i=0; i<HASH_TABLE_SIZE; i++){
        if (hashTable[i].frequency != 0)
            numCells ++;
    }

    //printHashTable(hashTable, HASH_TABLE_SIZE );

    printf("\nCapacity: %d\n", HASH_TABLE_SIZE);
    printf("Number of Terms: %d\n", numTerms);
    printf("Number of cells occupied: %d\n", numCells);
    printf("Collisions: %d\n", totalCollisions);
    printf("Load: %.3f\n", ((double)numCells / (double)HASH_TABLE_SIZE) );

    /* Allow user to search for a name in the table */
    printf("\nEnter term to get frequency or type 'quit' to escape \n");
    while (strcmp(userInput, "quit") != 0) {
        scanf("%s", userInput);
        index = hash(userInput);
        if (hashTable[index].frequency != 0)
            printf(">> %s %d\n", hashTable[index].name, hashTable[index].frequency);
        else
            printf("%s is not in the hash table\n", userInput);
    }

    return 0;
}


int hash(char *s){
    int hash = 0;
    int count = 1;
    while (*s) {
        hash = hash + (*s * count*10);
        s++;
        count++;
    }
    return (hash % HASH_TABLE_SIZE);
}





/* This function will return the number of collisions that occured */
int addToHashTable(char *s, Hash *hashTable){
    int index = hash(s);
    int numCollisions = 0;

    // TODO FIX THIS
    if (index >= HASH_TABLE_SIZE)
        index=0; 
    /* Check that the cell in hash table is either empty or contains the same name */
    if (strcmp(hashTable[index].name, s) == 0 || hashTable[index].frequency == 0){
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment frequency by 1
    }
    /* Deal with collision */
    else { 
        /* Loop to find a free cell */
        while (hashTable[index].frequency != 0){ 
            /* If we reach the end of the array, loop back to the first element */
            if (index >= (HASH_TABLE_SIZE-1))
                index = 0;
            else
                index++;
            numCollisions++;
        }
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment frequency by 1
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
        if (buf[i] == ',' && !quoted) {
            break;
        }
        // end record on newline or end of file
        if (feof(f) || buf[i] == '\n'){
            end = 1;
            break;
        }
        // truncate fields that would overflow the buffer
        if (i < max - 1){
            ++i;
        }
    }
    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}


void printHashTable(Hash *hashTable, int size){
    for(int i=0; i<size; i++){
        printf("Name: %s, Frequency: %d \n", hashTable[i].name, hashTable[i].frequency);
    }
}