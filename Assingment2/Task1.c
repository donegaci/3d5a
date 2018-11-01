#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 10000

void quickSort(int arr[], int left, int right);
int partition(int arr[], int left, int right);
void swap(int arr[], int index1, int index2);
void printArray(int arr[], int size);
void testPerformance();
void createTestArrays(int a1[], int a2[], int a3[], int a4[], int a5[]);
void shuffle(int *array, size_t n);

static int numSwaps=0;
static int numComparisons=0;


int main(){
    int test0[10] = {18,89,65,4,98,32,11,78,41,29};
    
    // quickSort(test0, 0, 9);
    // // printArray(test0, 10);
    // printf("10 random values \n#Swaps: %d\n", numSwaps);
    // printf("#Comparisons: %d\n\n", numComparisons);

    testPerformance();

    return 0;
}


int partition(int arr[], int left, int right){

    /* List has only one element */
    if(left == right)
        return left;
    
    int pivot = arr[right];
    int leftPointer = left;
    int rightPointer = right -1;

    while(1) { // infinite loop

        // while value at left is less than pivot, move right
        while ((arr[leftPointer] < pivot)){
            leftPointer++;
            numComparisons++;
        }
        // while value at right is greater than the pivot, move left
        while (arr[rightPointer] >= pivot){
            rightPointer--;
            numComparisons++;
        }
        if (leftPointer >= rightPointer) 
            break;
        else {
            swap(arr, leftPointer, rightPointer); 
            numSwaps++;
            //printArray(arr, 6);
        }
    }
    swap(arr, leftPointer, right); // put the pivot in the right place
    numSwaps++;
    //printArray(arr, 6);
    return leftPointer;
}


void swap(int arr[], int index1, int index2){
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}


void printArray(int arr[], int size){

    for(int i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void quickSort(int arr[], int left, int right){

    if(left >= right)
        return; // finished sorting

    int partIndex = partition(arr, left, right);
    /* Sort the two resulting partitions*/
    quickSort(arr, left, partIndex -1);
    quickSort(arr, partIndex+1, right);
}


void testPerformance(){
    int test1[SIZE];
    int test2[SIZE];
    int test3[SIZE];
    int test4[SIZE];
    int test5[SIZE];

    /* Fill the arrays*/
    createTestArrays(test1, test2, test3, test4, test5);
    //printArray(test1, SIZE);

    numSwaps=0; 
    numComparisons=0;
    printArray(test1, 5);
    quickSort(test1, 0, SIZE-1);
    printArray(test1, 5);
    printf("Unique Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test2, 5);
    quickSort(test2, 0, SIZE-1);
    printArray(test2, 5);
    printf("Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test3, 5);
    quickSort(test3, 0, SIZE-1);
    printArray(test3, 5);
    printf("Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test4, 5);
    quickSort(test4, 0, SIZE-1);
    printArray(test4, 5);
    printf("Reverse Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test5, 5);
    quickSort(test5, 0, SIZE-1);
    printArray(test5, 5);
    printf("Uniform list \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);
}


void createTestArrays(int a1[], int a2[], int a3[], int a4[], int a5[]){
    int size = 10000;
    time_t t; // this will be the seed for random number generator
    
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    /* Unique Random value array*/
    /* Fill an array with increasing values than shuffle the array */
    for(int i=0; i<size; i++)
        a1[i] = i;
    shuffle(a1, size);

    /* Random value array*/
    for(int i=0; i<size; i++ ) {
      a2[i] = rand();
    }
    /* Sorted Array*/
    for(int i=0; i<size; i++){
        a3[i] = i;
    }
    /* Reverse Sorted Array*/
    int index = 0;
    for(int i=size-1; i>=0; i--){
        a4[index] = i;
        index++;
    }
    /* Uniform Array*/
    for(int i=0; i<size; i++){
        a5[i] = 5;
    }
}


/* This function is from BEN PFAFF
https://benpfaff.org/writings/clc/shuffle.html
*/
void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}