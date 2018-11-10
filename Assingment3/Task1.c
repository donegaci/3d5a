#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode {
    TreeNode *leftChild, *rightChild;
    char data;
};

void insertNode(TreeNode **root, char data);
TreeNode* searchTree(TreeNode *root, char data);
void printTree (TreeNode *root);
TreeNode* newNode(char data);
void deleteTree(TreeNode *node);


int main(){
    TreeNode *root = NULL;
    char treeData[] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I',
         'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T', 'I', 'O', 'N'};
    
    for (int i=0; i< strlen(treeData); i++)
        insertNode(&root, treeData[i]);

    printTree(root);
    printf("\n");

    char userInput;
    printf("Enter char to search for in tree\n");
    scanf("%c", &userInput);
    searchTree(root, userInput);

    deleteTree(root);
    root = NULL;

    return 0;
}


/* This function returns a tree node with both children NULL */
TreeNode* newNode(char data){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->leftChild = node->rightChild = NULL;
    return node;
}


/* This function inserts a node in the correct position of BST */
void insertNode(TreeNode **root, char data){
    /* Empty */
    if (*root == NULL){
        *root = newNode(data);
        return;
    }

    TreeNode** prev = NULL;
    TreeNode** current = root;

    /* This will loop through the BST to find a leaf that will be made parent of new node */
    while(*current){
        prev = current;
        if(data < (*current)->data)
            current = &(*current)->leftChild;
        else
            current = &(*current)->rightChild;
    }
    /* If the new value is less than parent node, insert left child */
    if(data < (*prev)->data)
        (*prev)->leftChild = newNode(data);
    else
    /* Otherwise, insert right child */
        (*prev)->rightChild = newNode(data);
}


TreeNode* searchTree(TreeNode *root, char data){
    if (root == NULL){
        printf("Tree is empty! \n");
        return NULL;
    }
    TreeNode *current = root;

    while(current){
        if(data == current->data){ // current value is what we're searching for
            printf("Found %c \n", data);
            return current;
        }
        else if(data < current->data) // current value is greater, go to left child
            current = current->leftChild;
        else                        // current value is less, go to right child
            current = current->rightChild;
    }
    printf("%c not in tree \n", data); //if we reach this point, the value isn't in the tree
    return NULL;
}


/* Perform in-order traversal to get elements in sorted order */
void printTree (TreeNode *root){
    if(root == NULL)
        return;
    printTree(root->leftChild); //Traverse left subtree
    printf("%c ", root->data); //Print node 
    printTree(root->rightChild); //Traverse right subtree
}


/* Perform post-order traversal recursively to delete tree*/
void deleteTree(TreeNode *node){
    if (node != NULL){
        deleteTree(node->leftChild);
        deleteTree(node->rightChild);
        free(node);
    }
}