#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

void mergeSort(int arr[], int first, int last);
void merge (int arr[], int first, int mid, int last);
void printArray (int arr[], int first, int last);
void testPerformance();
void createTestArrays(int a1[], int a2[], int a3[], int a4[], int a5[]);
void shuffle(int *array, size_t n);

static int numSwaps=0;
static int numComparisons=0;


int main(){
    int test0[10] = {18,89,65,4,98,32,11,78,41,29};

    // printArray(test0, 0, 9);
    // mergeSort(test0, 0, 9);
    // printArray(test0, 0, 9);

    testPerformance();

    return 0;
}


void mergeSort(int arr[], int first, int last){
    
    if (last > first) {// More than 1 element to sort
        int middle = (first+last) / 2; //split the array in half 
        mergeSort(arr, first, middle);
        mergeSort(arr, middle+1, last);
        merge(arr, first, middle, last);
    }
}


void merge (int arr[], int first, int mid, int last){
    int size1 = (mid-first)+1;
    int size2 = last-mid;
    int i,j,k;
    /* Create temp arrays*/
    int array1[size1];
    int array2[size2];

    /* Copy into temp array */
    for (i=0; i< size1; i++){
        array1[i] = arr[first +i];
    }
    for (j=0; j<size2; j++){
        array2[j] = arr[(mid+1)+j];
    }

    /* Merge back into original */
    i = j = 0; // These will itterate over each array
    k = first;


    while (i< size1 && j < size2){
        if (array1[i] <= array2[j]){
            arr[k] = array1[i];
            i++;
            numSwaps++;
            numComparisons++;
        }
        else {
            arr[k] = array2[j];
            j++;
            numSwaps++;
        }
        k++;
    }
    /* Copy leftovers of array1 */
    while (i < size1){
        arr[k] = array1[i];
        i++;
        k++;
        numSwaps++;
        numComparisons++;
    }
    /* Copy leftovers of array2 */
    while (j < size2){
        arr[k] = array2[j];
        j++;
        k++;
        numSwaps++;
        numComparisons++;
    }
}


void printArray(int arr[], int first, int last){
    if (last !=0){
        for (int i=first; i<=last; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}


void testPerformance(){
    
    int test1[SIZE];
    int test2[SIZE];
    int test3[SIZE];
    int test4[SIZE];
    int test5[SIZE];

    createTestArrays(test1, test2, test3, test4, test5);

    numSwaps=0; 
    numComparisons=0;
    printArray(test1, 0, 5);
    mergeSort(test1, 0, SIZE-1);
    printArray(test1, 0, 5);
    printf("Unique Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test2, 0, 5);
    mergeSort(test2, 0, SIZE-1);
    printArray(test2, 0, 5);
    printf("Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test3, 0, 5);
    mergeSort(test3, 0, SIZE-1);
    printArray(test3, 0, 5);
    printf("Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test4, 0, 5);
    mergeSort(test4, 0, SIZE-1);
    printArray(test4, 0, 5);
    printf("Reverse Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test5, 0, 5);
    mergeSort(test5, 0, SIZE-1);
    printArray(test5, 0, 5);
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
      a2[i] = rand()%SIZE;
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