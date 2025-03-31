#include "../include/syntaxer.h"
#include "../../../Safe/Error/include/error.h"
#include <stdio.h>

void printAST(const Node* node) {
    if (node == NULL) {
        printf("printAST: NULL node, return\n");
        return;
    }

    if (node->token == NULL) {
        printf("printAST: node->token is NULL\n");
    } else if (node->token->vec == NULL) {
        printf("printAST: node->token->vec is NULL\n");
    } else {
        printf("Token: %s\n", node->token->vec->data);
    }

    
    if (node->left) {
        printf("Going left...\n");
        printAST(node->left);
    }
    if (node->right) {
        printf("Going right...\n");
        printAST(node->right);
    }
    if (node->next) {
        printf("Going next...\n");
        printAST(node->next);
    }
    if (node->bottom) {
        printf("Going bottom...\n");
        printAST(node->bottom);
    }
}


 Node* addIncludeToken(Node* root, Token** token) {}
//     Node* newNode = createNode();
//     root->right = newNode;
//     newNode->token = *token;
//     *token = (*token)->next;
//     
//     Node* child =  createNode();
//     child->token = *token;
//     newNode->left = child;
//     *token = (*token)->next;
//
//     newNode = createNode();
//     root->next = newNode;
//     newNode->prev = root;
//     return newNode;
// }

Node* addOrdinaryToken(Node* root, Token** token) {
    Node* newNode = createNode();
    newNode->token = *token;
    *token = (*token)->next;

    if (root->type == DATA_NODE) {
        root->next = newNode;
        newNode->prev = root;
        return newNode;
    }
    
    if (root->right == NULL) {
        root->right = newNode;
        newNode->parent = root;
    }
    
    else {
        newNode->left = root->right;
        root->right->parent = newNode;
        root->right = newNode;
        newNode->parent = root;
    }
    return newNode;
}

Node* addOperatorToken(Node* root, Token** token) {
    Node* newNode = createNode();
    newNode->token = *token;
    

    while (root->parent != NULL && root->parent->token != NULL
        && (root->parent->token->type == BIN_OPERATOR || root->parent->token->type == UNAR_OPERATOR)
        && (root->parent->token->order < (*token)->order)) {
        root = root->parent;
    }
    
    *token = (*token)->next;

    if (root->parent != NULL) {
        newNode->left = root;
        root->parent->right = newNode;
        newNode->parent = root->parent;
        root->parent = newNode;
        return newNode;
    }
    else {
        newNode->left = root;
        root->parent = newNode;
        if (root->prev) {
            newNode->prev = root->prev;
            root->prev->next = newNode;
        }
        
        return newNode;
    }
    
}

Node* addKwordToken(Node* root, Token** token) {}

Node* addDelimetrToken(Node* root, Token** token) {
    switch ((*token)->vec->data[0]) {
        case ';': {
            (*token) = (*token)->next;
            while (root->parent != NULL) {
                root = root->parent;
            }
            root = root->prev;
            Node* newNode = createNode();
            newNode->type = DATA_NODE;
            newNode->top = root;
            root->bottom = newNode;
            return newNode;
        }
    }
    
}

Node* addScopeOpenToken(Node* root, Token** token) {
    Node* newNode = createNode();
    root->bottom = newNode;
    newNode->top = root;
    root = root->bottom;

    newNode = createNode();
    root->next = newNode;
    newNode->prev = root;
    newNode->token = *token;
    *token = (*token)->next;
    root = root->next;
    newNode->type = DATA_NODE;
    
    newNode = createNode();
    root->bottom = newNode;
    newNode->top = root;
    newNode->type = DATA_NODE;
    return newNode;
}

Node* addScopeCloseToken(Node* root, Token** token) {
    Node* newRoot = createNode();
    if (newRoot == NULL) {
        return NULL;
    }
    newRoot->token = *token;
    *token = (*token)->next;
    root->bottom = newRoot;
    newRoot->top = root;
    
    while (root != NULL && root->top != NULL) {
        root = root->top;
    }
    if (root->prev != NULL) {
        root = root->prev;
    }
    else {
        printErrorMessage(10);
    }
    newRoot = createNode();
    newRoot->top = root;
    root->bottom = newRoot;
    newRoot->type = DATA_NODE;
    
    return newRoot;
}

Node* addTokenToNode(Node* root, Token** token) {
    switch ((*token)->type) {
        case (INCLUDE):
           return addIncludeToken(root, token);
        case (NUMBER):
        case (NAME):
        case (STRING):
        case (CHAR):
            return addOrdinaryToken(root, token);
        case (BIN_OPERATOR):
        case (UNAR_OPERATOR):
            return addOperatorToken(root, token);
        case (KWORD):
            return addKwordToken(root, token);
        case (DELIMITER):
            return addDelimetrToken(root, token);
        case (SCOPE_OPEN):
            return addScopeOpenToken(root, token);
        case (SCOPE_CLOSE):
            return addScopeCloseToken(root, token);
        default:
            return NULL;
    }
};

Node* createAST(Token* token){
    Node* root = createNode();
    if (root == NULL){
        deleteTokens(token);
        return NULL;
    }
    Node* node = root;
    // root->token = token;
    // token = token->next;
    Token **tok = &token;
    while(token != NULL && node != NULL){
        node = addTokenToNode(node, tok);
    }
    if (root == NULL) {
        return NULL;
    }
    while (root->parent != NULL || root->prev != NULL || root->top != NULL) {
        if (root->parent != NULL) {
            root = root->parent;
            break;
        }
        if (root->prev != NULL) {
            root = root->prev;
            break;
        }
        if (root->top != NULL) {
            root = root->top;
            break;
        }
    }
    return root;
};

