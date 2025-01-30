#include "../include/Node.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

Node* createNode(){
    Node* node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        printErrorMessage(7);
        return NULL;
    }
    return node;
};

int addChild(Node* parent, Node* child) {
    if(parent == NULL) {
        printErrorMessage(8);
    }
    else {
        parent->numChildren += 1;
        Node** tmp = (Node**)malloc(sizeof(Node*) * parent->numChildren);
        if (tmp == NULL) {
            printErrorMessage(7);
            return 0;
        }
        for (int i = 0; i < parent->numChildren - 1; i++) {
            tmp[i] = parent->children[i];
        }
        tmp[parent->numChildren - 1] = child;
        free(parent->children);
        parent->children = tmp;
        return parent->numChildren;
    }
}