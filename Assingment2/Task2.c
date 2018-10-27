#include <stdio.h>

void mergeSort(int arr[], int first, int last);
void merge (int arr[], int first, int mid, int last);
void printArray (int arr[], int first, int last);
void testPerformance();

static int numSwaps, numComparisons;
#define SIZE 6


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
    
    int test1[SIZE] = {4, 3, 5, 1, 0, 2};
    int test2[SIZE] = {3, 3, 2, 1, 1, 4};
    int test3[SIZE] = {0, 1, 2, 3, 4, 5};
    int test4[SIZE] = {5, 4, 3, 2, 1, 0};
    int test5[SIZE] = {3, 3, 3, 3, 3, 3};

    numSwaps=0; 
    numComparisons=0;
    printArray(test1, 0, 5);
    mergeSort(test1, 0, 5);
    printArray(test1, 0, 5);
    printf("Unique Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test2, 0, 5);
    mergeSort(test2, 0, 5);
    printArray(test2, 0, 5);
    printf("Random Values \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test3, 0, 5);
    mergeSort(test3, 0, 5);
    printArray(test3, 0, 5);
    printf("Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test4, 0, 5);
    mergeSort(test4, 0, 5);
    printArray(test4, 0, 5);
    printf("Reverse Sorted Array \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);

    numSwaps=0; 
    numComparisons=0;
    printArray(test5, 0, 5);
    mergeSort(test5, 0, 5);
    printArray(test5, 0, 5);
    printf("Uniform list \n#Swaps: %d\n", numSwaps);
    printf("#Comparisons: %d\n\n", numComparisons);
    
}