#include "../include/codeGenerator.h"
#include <stdio.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

int counter = 0;

void startOfFile(FILE* file) {
    fprintf(file, ".data\n");

    FILE* fileVariable = fopen("variable.txt", "r");
    if (fileVariable != NULL) {

        char buffer[64];
        
        size_t bytesRead;
        while (fgets(buffer, sizeof(buffer), fileVariable) != NULL) {
            fprintf(file, "%s", buffer);
        }
    }

    
    fprintf(file, ".text\n");
    fprintf(file, ".global _start\n");
    fprintf(file, "\n");
}

void endOfFile(FILE* file) {
    fprintf(file, "\n");
    fprintf(file, "li a0, 10\n");
    fprintf(file, "ecall\n");
}

int getValue(Token* token) {
    if (strcmp(token->vec->data, "+") == 0) {
        return 1;
    } else if (strcmp(token->vec->data, "-") == 0) {
        return 2;
    } else if (strcmp(token->vec->data, "*") == 0 && token->type == BIN_OPERATOR) {
        return 3;
    } else if (strcmp(token->vec->data, "/") == 0) {
        return 4;
    } else if (strcmp(token->vec->data, "%") == 0) {
        return 5;
    } else if (strcmp(token->vec->data, "+=") == 0) {
        return 6;
    } else if (strcmp(token->vec->data, "-=") == 0) {
        return 7;
    } else if (strcmp(token->vec->data, "*=") == 0) {
        return 8;
    } else if (strcmp(token->vec->data, "/=") == 0) {
        return 9;
    } else if (strcmp(token->vec->data, "%=") == 0) {
        return 10;
    } else if (strcmp(token->vec->data, "=") == 0) {
        return 11;
    } else if (strcmp(token->vec->data, "&&") == 0) {
        return 12;
    } else if (strcmp(token->vec->data, "||") == 0) {
        return 13;
    } else if (strcmp(token->vec->data, "!") == 0) {
        return 14;
    } else if (strcmp(token->vec->data, "==") == 0) {
        return 15;
    } else if (strcmp(token->vec->data, "!=") == 0) {
        return 16;
    } else if (strcmp(token->vec->data, "<=") == 0) {
        return 17;
    } else if (strcmp(token->vec->data, ">=") == 0) {
        return 18;
    } else if (strcmp(token->vec->data, "<") == 0) {
        return 19;
    } else if (strcmp(token->vec->data, ">") == 0) {
        return 20;
    } else if (strcmp(token->vec->data, "++") == 0) {
        return 21;
    } else if (strcmp(token->vec->data, "--") == 0) {
        return 22;
    } else if (strcmp(token->vec->data, "<<") == 0) {
        return 23;
    } else if (strcmp(token->vec->data, ">>") == 0) {
        return 24;
    } else if (strcmp(token->vec->data, "&=") == 0) {
        return 25;
    } else if (strcmp(token->vec->data, "|=") == 0) {
        return 26;
    } else if (strcmp(token->vec->data, "~") == 0) {
        return 28;
    } else if (strcmp(token->vec->data, "^") == 0) {
        return 29;
    } else if (strcmp(token->vec->data, "^=") == 0) {
        return 30;
    } else if (strcmp(token->vec->data, "&") == 0 && token->type == BIN_OPERATOR) {
        return 31;
    } else if (strcmp(token->vec->data, "|") == 0) {
        return 32;
    } else if (strcmp(token->vec->data, "*") == 0 && token->type == UNAR_OPERATOR) {
        return 33;
    } else if (strcmp(token->vec->data, "&") == 0 && token->type == UNAR_OPERATOR) {
        return 34;
    } else {
        return -1; 
    }
}

void generate(Node* node, FILE* file) {
    if (node != NULL) {
        generate(node->next, file);
        if (node->token && (node->token->type == BIN_OPERATOR || node->token->type == UNAR_OPERATOR)) {
            fprintf(file, "# start OP\n");
            generate(node->right, file);
            if (node->right) {
                node->right->generated = 1;
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a0, 0(sp)\n");
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a1, 0(sp)\n");
                fprintf(file, "\n");
            }
            generate(node->left, file);
            if (node->left) {
                node->left->generated = 1;
            }
            if (node->right) {
                fprintf(file, "lw a3, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "lw a2, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "\n");
            }
            switch (getValue(node->token)) {
                case 1: {
                    fprintf(file, "add a0, a0, a2\n");
                    break;
                }
                case 2: {
                    fprintf(file, "sub a0, a0, a2\n");
                    break;
                }
                case 3: {
                    fprintf(file, "mul a0, a0, a2\n");
                    break;
                }
                case 4: {
                    fprintf(file, "div a0, a0, a2\n");
                    break;
                }
                case 5: {
                    fprintf(file, "rem a0, a0, a2\n");
                    break;
                }
                case 6: {
                    fprintf(file, "add a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 7: {
                    fprintf(file, "div a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 8: {
                    fprintf(file, "mul a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 9: {
                    fprintf(file, "div a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 10: {
                    fprintf(file, "rem a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 11: {
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 12: {
                    fprintf(file, "beq a0, x0, loop%d\n", counter);
                    fprintf(file, "beq a2, x0, loop%d\n", counter);
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
                    fprintf(file, "bne a2, x0, loop%d\n", counter+1);
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
                case 14: {
                    if (node->right) {
                        fprintf(file, "beq a2, x0, loop%d\n", counter);
                    } else if (node->left) {
                        fprintf(file, "beq a1, x0, loop%d\n", counter);
                    } else {
                        printErrorMessage(15);
                    }
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 15: {
                    fprintf(file, "beq a0, a2, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 16: {
                    fprintf(file, "beq a0, a2, loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 17: {
                    fprintf(file, "bge a1, a2, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 18: {
                    fprintf(file, "bge a0, a2, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 19: {
                    fprintf(file, "blt a0, a2, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 20: {
                    fprintf(file, "bgt a0, a2, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, ".loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, ".loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 21: {
                    if (node->right && node->right->token) {
                        fprintf(file, "addi a2, a2, 1\n");
                        fprintf(file, "sw a2, 0(a3) \n");
                    }
                    else if (node->left && node->left->token) {
                        fprintf(file, "addi a0, a0, 1\n");
                        fprintf(file, "sw a0, 0(a2)\n");
                    }
                    else {
                        printErrorMessage(11);
                    }
                    break; 
                }
                case 22: {
                    if (node->right && node->right->token) {
                        fprintf(file, "addi a2, a2, -1\n");
                        fprintf(file, "sw a2, 0(a3)\n");
                    }
                    else if (node->left && node->left->token) {
                        fprintf(file, "addi a0, a0, -1\n");
                        fprintf(file, "sw a0, 0(a1)\n");
                    }
                    else {
                        printErrorMessage(11);
                    }
                    break; 
                }
                case 23: {
                    fprintf(file, "sll a0, a0, a2\n");
                    break; 
                }
                case 24: {
                    fprintf(file, "srl a0, a0, a2\n");
                    break; 
                }
                case 25: {
                    fprintf(file, "and a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 26: {
                    fprintf(file, "or a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 28: {
                    if (node->right) {
                        fprintf(file, "xori a0, a2, -1\n");
                    }
                    else {
                        fprintf(file, "xori a0, a0, -1\n");
                    }
                    break;
                }
                case 29: {
                    fprintf(file, "xor a0, a0, a2\n");
                    break;
                }
                case 30: {
                    fprintf(file, "xor a0, a0, a2\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    break;
                }
                case 31: {
                    fprintf(file, "and a0, a0, a2\n");
                    break;
                }
                case 32: {
                    fprintf(file, "or a0, a0, a2\n");
                    break;
                }
                case 33: {
                    if (node->right) {
                        fprintf(file, "mv a1, a2\n");
                        fprintf(file, "lw a0, 0(a1)\n");
                    }
                    else {
                        fprintf(file, "mv a1, a0\n");
                        fprintf(file, "lw a0, 0(a1)\n");
                    }
                }
                case 34: {
                    if (node->right) {
                        fprintf(file, "mv a0, a3\n");
                    }
                    else {
                        fprintf(file, "mv a0, a1\n");
                    }
                    break;
                }
            }
            fprintf(file, "# end OP\n");

        }
        else if (node->left == NULL && node->right == NULL && node->token && node->token->type == NAME
            && node->generated == 0) {
            fprintf(file, "la a1, %s\n", node->token->vec->data);
            fprintf(file, "lw a0, 0(a1)\n");
        }
        else if (node->left == NULL && node->right == NULL && node->token && node->token->type == NUMBER
            && node->generated == 0) {
            fprintf(file, "li a0, %s\n", node->token->vec->data);
            fprintf(file, "li a1, 0\n");
            }
        else if (node->token && node->token->type == DELIMITER && strcmp(node->token->vec->data, "(") == 0) {
            if (node->right) {
                generate(node->right, file);
            }
        }
        //generate(node->right, file);
        generate(node->bottom, file);
    }
}

void generateCode(Node* code, char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printErrorMessage(12);
        return;
    }
    fprintf(file, "// Generated by codeGenerator\n");
    startOfFile(file);
    generate(code, file);
    endOfFile(file);
}
