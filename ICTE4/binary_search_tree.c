#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* public functions **********************************************************/

Node* Node_new(void){
    Node *root = (Node *) malloc(sizeof(Node));
    return root;
}

void Node_destroy(Node* root){
    free(root);
    return;
}

void Node_insert(Node** root, int value) {
    if(*root == NULL){
        *root = (Node*)malloc(sizeof(Node));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }else if(value < (*root)->value){
        Node_insert(&((*root)->left), value);
    }else{
        Node_insert(&((*root)->right), value);
    }
}

void Node_delete(Node** root, int value){
    if(*root == NULL) return;
    if(value < (*root)->value){
        Node_delete(&((*root)->left), value);
    }else if(value > (*root)->value){
        Node_delete(&((*root)->right), value);
    }else{
        if((*root)->left == NULL && (*root)->right == NULL){
            free(*root);
            *root = NULL;
        }else if((*root)->left == NULL){
            Node* temp = *root;
            *root = (*root)->right;
            free(temp);
        }else if((*root)->right == NULL){
            Node* temp = *root;
            *root = (*root)->left;
            free(temp);
        }
    }
}

struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->value == value)
        return root;
    if (root->value > value)
        return search(root->left, value);
    return search(root->right, value);
}

int findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root->value;
}

int findMax(struct Node* root) {
    while (root->right != NULL)
        root = root->right;
    return root->value;
}

int isBST(struct Node* root) {
    if (root == NULL)
        return 1;
    if (root->left != NULL
        && findMax(root->left) > root->value)
        return 0;
    if (root->right != NULL
        && findMin(root->right) < root->value)
        return 0;
    if (!isBST(root->left) || !isBST(root->right))
        return 0;
    return 1;
}

void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

void printPreOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPostOrder(struct Node* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->value);
    }
}
