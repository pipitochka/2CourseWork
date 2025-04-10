#include "../include/node.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

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

void freeNode(Node* node) {
    if (node != NULL) {
        freeNode(node->left);
        freeNode(node->right);
        freeNode(node->next);
        freeNode(node->bottom);
        free(node);   
    }
}



