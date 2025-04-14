#include "../include/node.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

//function to allocate memory for Node
//return pointer to new Node or NULL if allocation can not be done
//makes all fields equal to 0 or NULL
Node* createNode(){
    Node* node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    node->token = NULL;
    node->top = NULL;
    node->bottom = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->type = NULL_NODE;
    node->generated = 0;
    node->function = NULL;
    return node;
};

//function to deallocate memory allocated for Node tree
//recursively call itself for children of a Node
//free memory for node
//do not free memory for token
void freeNode(Node* node) {
    if (node != NULL) {
        freeNode(node->left);
        freeNode(node->right);
        freeNode(node->next);
        freeNode(node->bottom);
        free(node);   
    }
}



