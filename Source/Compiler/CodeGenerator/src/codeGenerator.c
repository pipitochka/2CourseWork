#include "../include/codeGenerator.h"
#include <stdio.h>
#include <string.h>

int counter = 0;

int getValue(Vector* vec) {
    if (strcmp(vec->data, "+") == 0) {
        return 1;
    } else if (strcmp(vec->data, "-") == 0) {
        return 2;
    } else if (strcmp(vec->data, "*") == 0) {
        return 3;
    } else if (strcmp(vec->data, "/") == 0) {
        return 4;
    } else if (strcmp(vec->data, "%") == 0) {
        return 5;
    } else if (strcmp(vec->data, "+=") == 0) {
        return 6;
    } else if (strcmp(vec->data, "-=") == 0) {
        return 7;
    } else if (strcmp(vec->data, "*=") == 0) {
        return 8;
    } else if (strcmp(vec->data, "/=") == 0) {
        return 9;
    } else if (strcmp(vec->data, "%=") == 0) {
        return 10;
    } else if (strcmp(vec->data, "=") == 0) {
        return 11;
    } else if (strcmp(vec->data, "&&") == 0) {
        return 12;
    } else if (strcmp(vec->data, "||") == 0) {
        return 13;
    } else if (strcmp(vec->data, "!") == 0) {
        return 14;
    } else if (strcmp(vec->data, "==") == 0) {
        return 15;
    } else if (strcmp(vec->data, "!=") == 0) {
        return 16;
    } else if (strcmp(vec->data, "<=") == 0) {
        return 17;
    } else if (strcmp(vec->data, ">=") == 0) {
        return 18;
    } else if (strcmp(vec->data, "<") == 0) {
        return 19;
    } else if (strcmp(vec->data, ">") == 0) {
        return 20;
    } else if (strcmp(vec->data, "++") == 0) {
        return 21;
    } else if (strcmp(vec->data, "++") == 0) {
        return 22;
    } else if (strcmp(vec->data, "<<") == 0) {
        return 23;
    } else if (strcmp(vec->data, ">>") == 0) {
        return 24;
    } else if (strcmp(vec->data, "&=") == 0) {
        return 25;
    } else if (strcmp(vec->data, "|=") == 0) {
        return 26;
    } else if (strcmp(vec->data, "!=") == 0) {
        return 27;
    } else if (strcmp(vec->data, "~") == 0) {
        return 28;
    } else if (strcmp(vec->data, "^") == 0) {
        return 29;
    } else if (strcmp(vec->data, "^=") == 0) {
        return 30; 
    } else {
        return -1; 
    }
}


void generate(Node* node, FILE* file) {
    if (node != NULL) {
        generate(node->next, file);
        if (node->left && node->right) {
            generate(node->right, file);
            node->right->generated = 1;
            fprintf(file, "addi sp, sp, -4\n");
            fprintf(file, "sw a0, 0(sp)\n");
            fprintf(file, "\n");
            generate(node->left, file);
            node->left->generated = 1;
            fprintf(file, "lw a1, 0(sp)\n");
            fprintf(file, "addi sp, sp, 4\n");
            fprintf(file, "\n");
            switch (getValue(node->token->vec)) {
                case 1: {
                    fprintf(file, "add a0, a1, a0\n");
                    break;
                }
                case 2: {
                    fprintf(file, "div a0, a1, a0\n");
                    break;
                }
                case 3: {
                    fprintf(file, "mul a0, a1, a0\n");
                    break;
                }
                case 4: {
                    fprintf(file, "div a0, a1, a0\n");
                    break;
                }
                case 5: {
                    fprintf(file, "rem a0, a1, a0\n");
                    break;
                }
                case 6: {
                    fprintf(file, "add a0, a0, a1\n");
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 7: {
                    fprintf(file, "div a0, a0, a1\n");
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 8: {
                    fprintf(file, "mul a0, a0, a1\n");
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 9: {
                    fprintf(file, "div a0, a0, a1\n");
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 10: {
                    fprintf(file, "rem a0, a0, a1\n");
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 11: {
                    fprintf(file, "la a1, %s\n", node->left->token->vec->data);
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 12: {
                    fprintf(file, "beq a0, x0, loop%d\n", counter);
                    fprintf(file, "beq a1, x0, loop%d\n", counter);
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+2);
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+2);
                    fprintf(file, "\n");
                    counter += 3;
                    break;
                }
                case 13: {
                    fprintf(file, "beq a0, x0, loop%d\n", counter);
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "bne a1, x0, loop%d\n", counter+1);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+2);
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+2);
                    fprintf(file, "\n");
                    counter += 3;

                    break;
                }
            }
        }
        if (node->left == NULL && node->right == NULL && node->token && node->token->type == NAME && node->generated == 0) {
            fprintf(file, "la a0, %s\n", node->token->vec->data);
            fprintf(file, "lw a0, 0(a0)\n");
        }
        //generate(node->right, file);
        generate(node->bottom, file);
    }
}

void generateCode(Node* code, char* fileName) {
    FILE* file = fopen(fileName, "w");
    fprintf(file, "// Generated by codeGenerator\n");
    
    generate(code, file);
}
