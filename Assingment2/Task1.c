#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 6

void quickSort(int arr[], int left, int right);
int partition(int arr[], int left, int right);
void swap(int arr[], int index1, int index2);
void printArray(int arr[], int size);
void testPerformance();

static int numSwaps=0;
static int numComparisons=0;

int main(){
    int test0[10] = {18,89,65,4,98,32,11,78,41,29};
    int test1[SIZE] = {4, 3, 5, 1, 0, 2};
    int test2[SIZE] = {3, 3, 2, 1, 1, 4};
    int test3[SIZE] = {0, 1, 2, 3, 4, 5};
    int test4[SIZE] = {5, 4, 3, 2, 1, 0};
    int test5[SIZE] = {3, 3, 3, 3, 3, 3};
    
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
    
    int test1[SIZE] = {4, 3, 5, 1, 0, 2};
    int test2[SIZE] = {3, 3, 2, 1, 1, 4};
    int test3[SIZE] = {0, 1, 2, 3, 4, 5};
    int test4[SIZE] = {5, 4, 3, 2, 1, 0};
    int test5[SIZE] = {3, 3, 3, 3, 3, 3};

    numSwaps=0; 
    numComparisons=0;
    printArray(test1, 5);
    quickSort(test1, 0, 5);
    printArray(test1, 5);
    printf("Unique Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test2, 5);
    quickSort(test2, 0, 5);
    printArray(test2, 5);
    printf("Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test3, 5);
    quickSort(test3, 0, 5);
    printArray(test3, 5);
    printf("Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test4, 5);
    quickSort(test4, 0, 5);
    printArray(test4, 5);
    printf("Reverse Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test5, 5);
    quickSort(test5, 0, 5);
    printArray(test5, 5);
    printf("Uniform list \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);
    
}