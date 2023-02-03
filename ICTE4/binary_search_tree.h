#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node Node;
struct Node {
    int value;
    Node* left;
    Node* right;
};

/* Constructors / Destructors ************************************************/

Node* Node_new(void);
void Node_destroy(Node *root);

void Node_insert(Node**, int);
void Node_delete(Node**);

Node* search(Node* root, int value);

int findMin(Node* root);
int findMax(Node* root);
int isBST(Node* root);

void printInOrder(Node*);
void printPreOrder(Node*);
void printPostOrder(Node*);

#endif
