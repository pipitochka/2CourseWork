#include "../include/syntaxer.h"
#include "../../../Safe/Error/include/error.h"
#include <stdio.h>

void printAST(const Node* node) {
    if (node == NULL) return;
    if (node->token) {
        printf("%s\n", node->token->vec->data);
    }
    if (node->next) {
        printAST(node->next);
    }
    printAST(node->left);
    printAST(node->right);
}

Node* addIncludeToken(Node* root, Token** token) {
    Node* newNode = createNode();
    root->right = newNode;
    newNode->token = *token;
    *token = (*token)->next;
    
    Node* child =  createNode();
    child->token = *token;
    newNode->left = child;
    *token = (*token)->next;

    newNode = createNode();
    root->next = newNode;
    newNode->prev = root;
    return newNode;
}

Node* addOrdinaryToken(Node* root, Token** token) {
    Node* newNode = createNode();
    newNode->token = *token;
    *token = (*token)->next;

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
        return newNode;
    }
    
}

Node* addKwordToken(Node* root, Token** token) {}

Node* addDelimetrToken(Node* root, Token** token) {}

Node* addScopeOpenToken(Node* root, Token** token) {
    Node* newNode = createNode();
    root->right = newNode;

    newNode = createNode();
    newNode->token = *token;
    *token = (*token)->next;

    root->right->next = newNode;
    newNode->prev = root->right;
    return newNode;
}

Node* addScopeCloseToken(Node* root, Token** token) {
    Node* newNode = createNode();
    newNode->token = *token;
    *token = (*token)->next;

    root->right = newNode;
    
    while (root->parent != NULL) {
        root = root->parent;
    }
    return root->prev;
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
    while (root->parent != NULL) {
        root = root->parent;
    }
    return root;
};

