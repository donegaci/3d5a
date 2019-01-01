#include "bstdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct TreeNode TreeNode;
struct TreeNode{
	char *name;
	int word_count;
	int id;
	TreeNode *leftChild, *rightChild;
};

int initialiseArray(int size);
TreeNode* newNode(char *name, int word_count);
TreeNode* searchTree (int id);
void deleteTree(TreeNode *node);
int treeHeight(TreeNode* node);
int countNodes(TreeNode* node);
int max(int a, int b);

// Globals 
TreeNode* ROOT = NULL; // Initialise root of tree
static int * UNIQUE_ARRAY = NULL;
static int ARRAY_INDEX = 0;
const int ARRAY_SIZE = 150000;
static int NUM_NODES = 0;
static int NUM_SEARCHES = 0;


int bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Function should return 1 if initialization was successful 
	// and 0 if something went wrong.

	time_t t; // this will be the seed for random number generator
    // Intializes random number generator 
	srand((unsigned) time(&t));

	if (initialiseArray(ARRAY_SIZE)){
		return 1;
	}
	else
		return 0;

}


int initialiseArray(int size) {
	// This function take an array size and creates an array of given size.
	// It then fills the array with integer numbers 0, 1, 2,  ... size-1
	// Finally it shuffles the array to produce an array of unique random values

    if (size >= 0) {
        if (UNIQUE_ARRAY != NULL) // if the memory is already occupied
            free (UNIQUE_ARRAY);
        if ((UNIQUE_ARRAY = malloc (sizeof(int) * size)) == NULL)
            return 0; // something went wrong
        for (int i = 0; i  < size; i++)
            UNIQUE_ARRAY[i] = i;

		//shuffle
		for (int i = 0; i < size - 1; i++) {
          int j = i + rand() / (RAND_MAX / (size - i) + 1);
          int t = UNIQUE_ARRAY[j];
          UNIQUE_ARRAY[j] = UNIQUE_ARRAY[i];
          UNIQUE_ARRAY[i] = t;
        }
		return 1;
    }
	return 0; // something went wrong
}


TreeNode *newNode(char *name, int word_count) {
	// This function allocates the memory for a new node, sets the name, word count
	// and unique id of node and returns pointer to node with both children set to NULL

	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

	// malloc can fail, so make sure node is pointing to something 
	if (node) {
		node->word_count = word_count;
		node->leftChild = node->rightChild = NULL;
		
		node->id = UNIQUE_ARRAY[ARRAY_INDEX];
		ARRAY_INDEX++;

		int lengthName = strlen(name) + 1;
		node->name = calloc(lengthName, sizeof(char));

		if (node->name) {
			// if calloc was successful, copy the filename into the node
			strcpy(node->name, name);
			return node;
		}
		else {
			// if calloc failed, release any memory that was allocated and
			// report an error by returning NULL
			free(node);
			node = NULL;
			return NULL;
		}
	}
	return NULL; // something went wrong
}


int bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	TreeNode* new = newNode(name, word_count);

	if(new == NULL) // somwthing went wrong
		return -1;

	if (ROOT == NULL){ // The tree is empty
		ROOT = new;
		return ROOT->id;
	}

	TreeNode* prev = NULL;
    TreeNode* current = ROOT;
	
	// This will loop through the BST to find a leaf that will be made parent of new node 
    while(current){
        prev = current;
        if(new->id < current->id)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    // If the new value is less than parent node, insert left child 
    if(new->id < prev->id){
        prev->leftChild = new;
		//printf("%d\n", new->id);
		return new->id;
	}
	// If the new value is greater than parent, insert right child 
    else if (new->id > prev->id) {
        prev->rightChild = new;
		return new->id;
	}
	else // something went wrong
		return -1;
}

int bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	TreeNode* node = searchTree(doc_id);

	if(node != NULL)
		return node->word_count;

	return -1;
}

char* bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0

	TreeNode* node = searchTree(doc_id);

	if(node != NULL)
		return node->name;

	return 0;
}


TreeNode* searchTree (int id){

	NUM_SEARCHES++; // Count how many times function is called

	if (ROOT == NULL){ // Tree is empty
        return NULL;
    }

    TreeNode *current = ROOT;

    while(current){
        if(id == current->id){ // current value is what we're searching for
            return current;
        }
        else if (id < current->id){ // current value is greater, go to left child
            current = current->leftChild;
        }
        else                      // current value is less, go to right child
            current = current->rightChild;
		NUM_NODES++;
	}
	//if we reach this point, the value isn't in the tree
    return NULL;
}


void bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	int nodesPerSearch = NUM_NODES/NUM_SEARCHES;
	printf("Average number of nodes per search: %d\n", nodesPerSearch );

	// Get height of left and right sub-trees
	printf("Height of left sub-tree: %d\n", treeHeight(ROOT->leftChild));
	printf("Height of right sub-tree: %d\n", treeHeight(ROOT->rightChild));

	// Get num of nodes in left and right sub-tree
	printf("Num nodes in left sub tree: %d\n", countNodes(ROOT->leftChild));
	printf("Num nodes in right sub tree: %d\n", countNodes(ROOT->rightChild));
}


void bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	deleteTree(ROOT);
	free(UNIQUE_ARRAY);
}


void deleteTree(TreeNode *node){
    if (node != NULL){
        deleteTree(node->leftChild);
        deleteTree(node->rightChild);
        free(node);
    }
}


int treeHeight(TreeNode* node){

	if(node == NULL){ // tree is empty
		return 0;
	}
	// If tree is not empty then height = 1 + max of left 
	// height and right heights
   	return 1 + max(treeHeight(node->leftChild), treeHeight(node->rightChild)); 
}


int max(int a, int b) { 
  return (a >= b)? a: b; 
} 


int countNodes(TreeNode* node){
	if(node == NULL){ // tree is empty
		return 0;
	}
	int i;
	i = 1 + countNodes(node->leftChild) + countNodes(node->rightChild);
	return i;
}