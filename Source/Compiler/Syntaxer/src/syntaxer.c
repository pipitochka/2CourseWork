#include "../include/syntaxer.h"
#include "../../../Safe/Error/include/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isLastOp = 1;

VariableList* variableList;


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

Node* addOrdinaryToken(Node* root, Token** token) {
    isLastOp = 0;
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
    
    if (isLastOp && (*token)->type == BIN_OPERATOR) {
        isLastOp = 1;
        if (token && *token && (strcmp((*token)->vec->data, "*") == 0 || strcmp((*token)->vec->data, "&") == 0)
            || strcmp((*token)->vec->data, "-") == 0) {
            newNode->token->type = UNAR_OPERATOR;
            newNode->token->order = 3;
        }
        else {
            printErrorMessage(14);
            return NULL;
        }
    }
    else {
        isLastOp = 1;
    }

    
    while (root->parent != NULL  &&
        ((root->parent->token != NULL
            && (root->parent->token->type == BIN_OPERATOR || root->parent->token->type == UNAR_OPERATOR)
            && (root->parent->token->order < (*token)->order))
            || (root->parent->type == SCOPE)))  {
        root = root->parent;
    }
    
    

    if ((*token)->type == UNAR_OPERATOR) {
        *token = (*token)->next;
        if (root->type == DATA_NODE) {
            root->next = newNode;
            newNode->prev = root;
            return newNode;
        }
        
        if (root->left == NULL) {
            root->left = newNode;
            newNode->parent = root;
            return newNode;
        }
        else {
            root->right = newNode;
            newNode->parent = root;
            return newNode;
        }
    }
    
    *token = (*token)->next;
    if (root->parent != NULL) {
        newNode->left = root;
        if (root == root->parent->right) {
            root->parent->right = newNode;
        }
        else {
            root->parent->left = newNode;
        }
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
            root->prev = NULL;
        }
        
        return newNode;
    }
}

Node* addKwordToken(Node* root, Token** token) {
    if (strcmp((*token)->vec->data, "int") == 0) {
        Token* label = (*token)->next;
        while (label && !(label->type == DELIMITER && strcmp(label->vec->data, ";") == 0)) {
            if (label && label->type == NAME && label->next && (label->next->type == DELIMITER)) {
                if (strcmp(label->next->vec->data, ",") == 0 || strcmp(label->next->vec->data, ";") == 0) {
                    Variable* newVariable = initVariable(label->vec->data, 4, VAR, 1);
                    addVariable(&variableList, newVariable);
                    if (label && label->next && strcmp(label->next->vec->data, ";") == 0) {
                        break;
                    }
                    label = label->next->next;
                    
                }
                //function
                else if (label->next->vec->data == "(") {
                    
                }
                
            }
            else if (label && label->type == NAME && label->next && (label->next->type == BIN_OPERATOR)) {
                if (strcmp(label->next->vec->data, "[") == 0) {
                    if (label->next->next && label->next->next->type == NUMBER
                        && label->next->next->next && label->next->next->next->type == DELIMITER
                        && strcmp(label->next->next->next->vec->data, "]") == 0
                        && label->next->next->next->next && label->next->next->next->next->type == DELIMITER
                        && (strcmp(label->next->next->next->next->vec->data, ",")
                            || strcmp(label->next->next->next->next->vec->data, ";"))) {
                        int counter = atoi(label->next->next->vec->data);
                        Variable* newVariable = initVariable(label->vec->data, 4, MAS, counter);
                        addVariable(&variableList, newVariable);
                        label = label->next->next->next->next->next;
                            
                            }
                    else {
                        printErrorMessage(14);
                        return NULL;
                    }
                }
                else {
                    Variable* newVariable = initVariable(label->vec->data, 4, VAR, 1);
                    addVariable(&variableList, newVariable);
                    while (label && label->type != DELIMITER) {
                        label = label->next;
                    }
                    if (label && label->type == DELIMITER && strcmp(label->vec->data, ";") != 0) {
                        label = label->next;
                    }
                }
            }
            else {
                printErrorMessage(13);
            }
        }
        (*token) = (*token)->next;
        return root;
    }
    else if (strcmp((*token)->vec->data, "char") == 0) {
        Token* label = (*token)->next;
        while (label && !(label->type == DELIMITER && strcmp(label->vec->data, ";") == 0)) {
            if (label && label->type == NAME && label->next && (label->next->type == DELIMITER)) {
                if (strcmp(label->next->vec->data, ",") == 0 || strcmp(label->next->vec->data, ";") == 0) {
                    Variable* newVariable = initVariable(label->vec->data, 1, VAR, 1);
                    addVariable(&variableList, newVariable);
                    if (label && label->next && strcmp(label->next->vec->data, ";") == 0) {
                        break;
                    }
                    label = label->next->next;
                    
                }
                //function
                else if (label->next->vec->data == "(") {
                    
                }
                
            }
            else if (label && label->type == NAME && label->next && (label->next->type == BIN_OPERATOR)) {
                if (strcmp(label->next->vec->data, "[") == 0) {
                    if (label->next->next && label->next->next->type == NUMBER
                        && label->next->next->next && label->next->next->next->type == DELIMITER
                        && strcmp(label->next->next->next->vec->data, "]") == 0
                        && label->next->next->next->next && label->next->next->next->next->type == DELIMITER
                        && (strcmp(label->next->next->next->next->vec->data, ",")
                            || strcmp(label->next->next->next->next->vec->data, ";"))) {
                        int counter = atoi(label->next->next->vec->data);
                        Variable* newVariable = initVariable(label->vec->data, 4, MAS, counter);
                        addVariable(&variableList, newVariable);
                        label = label->next->next->next->next->next;
                            
                            }
                    else {
                        printErrorMessage(14);
                        return NULL;
                    }
                }
                else {
                    Variable* newVariable = initVariable(label->vec->data, 1, VAR, 1);
                    addVariable(&variableList, newVariable);
                    while (label && label->type != DELIMITER) {
                        label = label->next;
                    }
                    if (label && label->type == DELIMITER && strcmp(label->vec->data, ";") != 0) {
                        label = label->next;
                    }
                }
            }
            else {
                printErrorMessage(13);
            }
        }
        (*token) = (*token)->next;
        return root;
    }
    else if (strcmp((*token)->vec->data, "if") == 0) {
        Node* newNode = createNode();
        newNode->parent = root;
        newNode->token = (*token);
        root->bottom = newNode;
        *token = (*token)->next;
        (*token)->vec->data[1] = ')';
        pushBackVector((*token)->vec, '\0');
        return newNode;
    }
    else if (strcmp((*token)->vec->data, "else") == 0) {
        Node* newNode = createNode();
        newNode->parent = root;
        newNode->token = (*token);
        root->bottom = newNode;
        *token = (*token)->next;
        (*token)->vec->data[1] = ')';
        pushBackVector((*token)->vec, '\0');
        return newNode;
    }
    else if (strcmp((*token)->vec->data, "while") == 0) {
        Node* newNode = createNode();
        newNode->parent = root;
        newNode->token = (*token);
        root->bottom = newNode;
        *token = (*token)->next;
        (*token)->vec->data[1] = ')';
        pushBackVector((*token)->vec, '\0');
        return newNode;
    }
    else if (strcmp((*token)->vec->data, "for") == 0) {
        Node* newNode = createNode();
        newNode->parent = root;
        newNode->token = (*token);
        root->bottom = newNode;
        *token = (*token)->next;
        (*token)->vec->data[1] = ')';
        pushBackVector((*token)->vec, '\0');
        return newNode;
    }
}


Node* addDelimetrToken(Node* root, Token** token) {
    if (strcmp((*token)->vec->data, ";") == 0) {
            (*token) = (*token)->next;
            while (root->parent != NULL) {
                root = root->parent;
            }
            if (root->prev) {
                root = root->prev;
            }
            Node* newNode = createNode();
            newNode->type = DATA_NODE;
            newNode->top = root;
            root->bottom = newNode;
            isLastOp = 1;
            return newNode;
        }
    else if (strcmp((*token)->vec->data, ",") == 0) {
            (*token) = (*token)->next;
            while (root->parent != NULL) {
                root = root->parent;
            }
            if (root->prev) {
                root = root->prev;
            }
            Node* newNode = createNode();
            newNode->type = DATA_NODE;
            newNode->top = root;
            root->bottom = newNode;
            return newNode;
        }
    else if (strcmp((*token)->vec->data, "(") == 0) {
            isLastOp = 1;
            
            Node* newNode = createNode();
            newNode->type = NULL_NODE;
            newNode->token = *token;
            (*token) = (*token)->next;

            if (root->type == DATA_NODE) {
                root->next = newNode;
                newNode->prev = root;
                return newNode;
            }

            newNode->parent = root;
            if (root->right == NULL) {
                root->right = newNode;
            }
            else {
                root->left = newNode;
            }
            return newNode;
        }
    else if (strcmp((*token)->vec->data, ")") == 0) {
            isLastOp = 0;
            (*token) = (*token)->next;
            while ( (root && (root->parent != NULL || root->prev != NULL || root->top != NULL) && !(root->token &&
                root->token->type == DELIMITER
                && ((strcmp(root->token->vec->data, "(") == 0) || (strcmp(root->token->vec->data, "()") == 0)))) ) {
                if (root->parent != NULL) {
                    root = root->parent;
                }
                else if (root->top != NULL) {
                    root = root->top;
                }
                else {
                    root = root->prev;
                }
            }
            return root;
        }
    else if (strcmp((*token)->vec->data, "]") == 0) {
            isLastOp = 0;
            (*token) = (*token)->next;
            while (root && root->parent != NULL && !(root->token->type == BIN_OPERATOR
                && strcmp(root->token->vec->data, "[") == 0)) {
                root = root->parent;
                }
            return root;
        }
    else if (strcmp((*token)->vec->data, "()") == 0) {
        Node* newNode = createNode();
        root->bottom = newNode;
        newNode->top = root;
        newNode->type = DATA_NODE;
        newNode->token = (*token);
        (*token) = (*token)->next;
        
        return newNode;
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
    root->type = DATA_NODE;
    if (root == NULL){
        deleteTokens(token);
        return NULL;
    }
    Node* node = root;

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

