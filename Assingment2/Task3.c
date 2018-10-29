#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFFER 100
#define ARRAY_SIZE 18626

struct Game{
    char title[MAXBUFFER];
    char platform[MAXBUFFER];
    int score;
    int releaseYear;
};

int next_field(FILE *f, char *buf, int max);
void fetchGame(FILE *f, struct Game *game);
void quickSort(struct Game gameArr[], int left, int right);
int partition(struct Game gameArr[], int left, int right);
void swap(struct Game arr[], int index1, int index2);
void initialiseArray(struct Game gameArr[], int size);


int main(){

    FILE *f;
    char buffer[100];
    struct Game gameReviews[ARRAY_SIZE];
    int index = 0;

    initialiseArray(gameReviews, ARRAY_SIZE);

    f = fopen("ign.csv", "r");
    
    if (f) {
        fetchGame(f, &gameReviews[index]); // discard header row
        while (!feof(f)){
            fetchGame(f, &gameReviews[index]);
            index++;
        }  
    }
    else
        printf("Error opening file.\n");

    // /* Print first 10 games */
    // for(int i=0; i<10; i++){
    //     printf("%d, ", gameReviews[i].score);
    //     printf("%s\n", gameReviews[i].title ); 
    // } 

    quickSort(gameReviews, 0, ARRAY_SIZE-1);

    for(int i=0; i<10; i++){
        printf("%d, ", gameReviews[i].score);
        printf("%s, ", gameReviews[i].title ); 
        printf("%d\n", gameReviews[i].releaseYear);
    } 

    fclose(f);
    return 0;
}

void initialiseArray(struct Game gameArr[], int size){
    for(int i=0; i<size; i++){
        strcpy(gameArr[i].title , "");
        strcpy(gameArr[i].platform , "");
        gameArr[i].score = 0;
        gameArr[i].releaseYear = 0; 
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

void fetchGame(FILE *f, struct Game *game){

    char buf[MAXBUFFER];
    next_field(f, game->title, MAXBUFFER);
    next_field(f, game->platform, MAXBUFFER);
    next_field(f, buf, MAXBUFFER);
    game->score = atoi(buf);
    next_field(f, buf, MAXBUFFER);
    game->releaseYear = atoi(buf);
}


void quickSort(struct Game gameArr[], int left, int right){

    if(left >= right)
        return; // finished sorting

    int partIndex = partition(gameArr, left, right);
    /* Sort the two resulting partitions*/
    quickSort(gameArr, left, partIndex -1);
    quickSort(gameArr, partIndex+1, right);
}


/* I want to sort in descending order */
int partition(struct Game gameArr[], int left, int right){

    /* List has only one element */
    if(left == right)
        return left;
    
    int pivot = gameArr[right].score;
    int leftPointer = left;
    int rightPointer = right -1;

    while(1) { // infinite loop

        // while value at left is greater than pivot, move right
        while ((gameArr[leftPointer].score > pivot)){
            leftPointer++;
            //numComparisons++;
        }
        // while value at right is less than the pivot, move left
        while (gameArr[rightPointer].score <= pivot){
            rightPointer--;
            //numComparisons++;
        }
        if (leftPointer >= rightPointer) 
            break;
        else {
            swap(gameArr, leftPointer, rightPointer); 
            //numSwaps++;
            //printArray(arr, 6);
        }
    }
    swap(gameArr, leftPointer, right); // put the pivot in the right place
    //numSwaps++;
    //printArray(arr, 6);
    return leftPointer;
}


void swap(struct Game arr[], int index1, int index2){
    struct Game temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}