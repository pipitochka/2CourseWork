#include "../include/node.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

Node* createNode(){
    Node* node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        printErrorMessage(7);
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



//
// int addChild(Node* parent, Node* child) {
//     if (parent == NULL) {
//         printErrorMessage(8);
//         return 0;
//     }
//     else {
//         parent->numChildren += 1;
//         Node** tmp = (Node**)malloc(sizeof(Node*) * parent->numChildren);
//         if (tmp == NULL) {
//             printErrorMessage(7);
//             return 0;
//         }
//         for (int i = 0; i + 1 < parent->numChildren; i++) {
//             tmp[i] = parent->children[i];
//         }
//         tmp[parent->numChildren - 1] = child;
//         free(parent->children);
//         parent->children = tmp;
//         return parent->numChildren;
//     }
// }

// void deleteNode(Node* node) {
//     free(node);
// }
//
// void changeChild(Node* parent, Node* from, Node* to) {
//     for (int i = 0; i < parent->numChildren; i++) {
//         if (parent->children[i] == from) {
//             parent->children[i] = to;
//             return;
//         }
//     }
// }