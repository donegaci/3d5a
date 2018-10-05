#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hash Hash;
struct Hash{
    int frequency;
    char name[50]; // tidy up this
};

const int MAX_SIZE = 2000;
const int MAX_BUFFER = 40;
int hash(char *s);
void addToHashTable(char *s, struct Hash *hashTable);
int next_field(FILE *f, char *buf, int max);
void printHashTable(struct Hash *hashTable, int size);


int main()
{
    FILE *f;
    char buffer[MAX_BUFFER];
    char userInput[MAX_BUFFER];
    Hash hashTable[MAX_SIZE];

    for (int i=0; i<MAX_SIZE; i++){
        hashTable[i].frequency = 0;
    }

    f = fopen("names.csv", "r");

    if (f) {
        while (!feof(f)){
            int returnValue = next_field(f, buffer, MAX_BUFFER);

            if (returnValue == 1){
                //printf("%s\n", buffer);
                addToHashTable(buffer, hashTable);
                //printf("%s\n", buffer);
            }
        }
    }
    else
        printf("Error opening file.\n");

    printHashTable(hashTable, MAX_SIZE);

    // printf("Enter term to get frequency or type 'quit' to escape \n");

    // scanf("%s", userInput);
    // while (userInput != "quit"){
    //     scanf("%s", userInput);
    // }

    //printf("Hash is %d\n", hash(array));
    return 0;
}


int hash(char *s){
    int hash = 0;
    while (*s) {
        hash = hash + *s;
        s++;
    }
    return hash;
}


void addToHashTable(char *s, Hash *hashTable){
    int index = hash(s);

    if (strcmp(hashTable[index].name, s) == 0 || hashTable[index].frequency == 0){
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment the frequency by 1
    }
    else{
        printf("COLLISION for %s \n\n", s);

        while (hashTable[index].frequency != 0){
            index++;
        }
        strcpy(hashTable[index].name, s);
        hashTable[index].frequency = (hashTable[index].frequency + 1); // increment the frequency by 1
    }

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

// void printTableStats(Hash *hashTable, int size){
//     printf("Max Capacity: ", size);

// }