#include "../include/codeGenerator.h"
#include <stdio.h>
#include <string.h>
#include "../../../Safe/Error/include/error.h"



int counter = 0;

extern VariableList* globalVariables;

extern Function* currentFunction;

extern FunctionList* currentFunctionList;

void startOfFile(FILE* file) {
    fprintf(file, ".data\n");


    VariableList* data = globalVariables;

    while (data != NULL) {
        if (data->variable->type == VAR) {
            fprintf(file, "%s: .word 0\n", data->variable->name);
        }
        data = data->next;
    }
    
    fprintf(file, ".text\n");
    fprintf(file, ".global main\n");
    fprintf(file, "\n");
}

void endOfFile(FILE* file) {
    fprintf(file, "\n");
    fprintf(file, "li a7, 10\n");
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
    } else if (strcmp(token->vec->data, "[") == 0) {
        return 35;
    } else {
        return -1; 
    }
}

void getToken(char* name, FILE* file, char* functionName, int down) {
    Function* function = findFunction(currentFunctionList, functionName);
    down *= 12;
    int top = 0;
    if (function) {
        top += function->numParameters + function->numVariables;
    }
    top *= 12;
    top += down;
    top += currentFunction->currentOffset;
    if (function != NULL) {
        Variable* q;
        q = findVariable(function->parameters, name);
        if (q != NULL) {
            int t = q->counter;
            t *= 12;
            top -= t;
            fprintf(file, "addi a4, sp, %d\n", top-4);
            fprintf(file, "lw a0, 0(a4)\n");
            fprintf(file, "mv a1, a4\n");
            fprintf(file, "lw a2, -8(a4)\n");
            return;
        }
        q = findVariable(function->variables, functionName);
        if (q != NULL) {
            int t = q->counter;
            t *= 12;
            t += function->numParameters * 12;
            top -= t;
            fprintf(file, "addi a4, sp, %d\n", top-4);
            fprintf(file, "lw a0, 0(a4)\n");
            fprintf(file, "addi a4, a4, -4\n");
            fprintf(file, "mv a1, a4\n");
            fprintf(file, "lw a2, -4(a4)\n");
            return;
        }
    }
    Variable* q = findVariable(globalVariables, name);
    if (q != NULL) {
        fprintf(file, "la a1, %s\n", q->name);
        fprintf(file, "lw a0, 0(a1)\n");
        fprintf(file, "li a2, %d\n", q->size);
    }
    
}

void generate(Node* node, FILE* file) {
    if (node != NULL) {
        if (node->function != NULL) {
            fprintf(file, "%s:\n", node->function->name);
            fprintf(file, "addi sp, sp, -4\n");
            fprintf(file, "sw ra, 0(sp)\n");
            currentFunction = node->function;
            node->function->currentOffset = 4;
            node = node->bottom;
            generate(node->next, file);
            fprintf(file, "lw ra, 0(sp)\n");
            fprintf(file, "addi sp, sp, 4\n");
            fprintf(file, "ret\n");
            fprintf(file, "## end function %s\n", node->top->function->name);
            node = node->bottom;
        }
        if (node->type == FUNCTION_CALL) {
            Node* q = node->next;
            int counter = 0;
            while (q && q->token) {
                getToken(q->token->vec->data, file, node->token->vec->data, counter);
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a0, 0(sp)\n");
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a1, 0(sp)\n");
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a2, 0(sp)\n");
                q = q->bottom;
                counter++;
            }
            Function * function = findFunction(currentFunctionList, node->token->vec->data);
            fprintf(file, "call %s\n", node->token->vec->data);
            fprintf(file, "addi sp, sp, %d\n", (function->numParameters + function->numVariables) * 12);
            node = node->bottom;
        }
        if (!(node->next &&
            (node->next->token->type == NUMBER
                || node->next->token->type == STRING
                || node->next->token->type == NAME
                || (node->next->token->type == BIN_OPERATOR && strcmp(node->next->token->vec->data, "[") == 0)))) {
            generate(node->next, file);
        }
        if (node->token && (node->token->type == BIN_OPERATOR || node->token->type == UNAR_OPERATOR)) {
            fprintf(file, "# start OP\n");
            generate(node->right, file);
            if (node->right) {
                node->right->generated = 1;
                if (currentFunction != NULL) {
                    currentFunction->currentOffset += 12;
                }
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a0, 0(sp)\n");
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a1, 0(sp)\n");
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw a2, 0(sp)\n");
                fprintf(file, "\n");
            }
            generate(node->left, file);
            if (node->left) {
                node->left->generated = 1;
            }
            if (node->right) {
                if (currentFunction != NULL) {
                    currentFunction->currentOffset -= 12;
                }
                fprintf(file, "lw a5, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "lw a4, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "lw a3, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "\n");
            }
            switch (getValue(node->token)) {
                case 1: {
                    fprintf(file, "add a0, a0, a3\n");
                    break;
                }
                case 2: {
                    fprintf(file, "sub a0, a0, a3\n");
                    break;
                }
                case 3: {
                    fprintf(file, "mul a0, a0, a3\n");
                    break;
                }
                case 4: {
                    fprintf(file, "div a0, a0, a3\n");
                    break;
                }
                case 5: {
                    fprintf(file, "rem a0, a0, a3\n");
                    break;
                }
                case 6: {
                    fprintf(file, "add a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 7: {
                    fprintf(file, "div a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 8: {
                    fprintf(file, "mul a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 9: {
                    fprintf(file, "div a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 10: {
                    fprintf(file, "rem a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 11: {
                    fprintf(file, "sw a3, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 12: {
                    fprintf(file, "beq a0, x0, loop%d\n", counter);
                    fprintf(file, "beq a3, x0, loop%d\n", counter);
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
                    fprintf(file, "bne a3, x0, loop%d\n", counter+1);
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
                        fprintf(file, "beq a3, x0, loop%d\n", counter);
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
                    fprintf(file, "beq a0, a3, loop%d\n", counter);
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
                    fprintf(file, "beq a0, a3, loop%d\n", counter);
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
                    fprintf(file, "bge a1, a3, loop%d\n", counter);
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
                    fprintf(file, "bge a0, a3, loop%d\n", counter);
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
                    fprintf(file, "blt a0, a3, loop%d\n", counter);
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
                    fprintf(file, "bgt a0, a3, loop%d\n", counter);
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
                        fprintf(file, "addi a3, a3, 1\n");
                        fprintf(file, "sw a3, 0(a4) \n");
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
                        fprintf(file, "addi a3, a3, -1\n");
                        fprintf(file, "sw a3, 0(a4)\n");
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
                    fprintf(file, "sll a0, a0, a3\n");
                    break; 
                }
                case 24: {
                    fprintf(file, "srl a0, a0, a3\n");
                    break; 
                }
                case 25: {
                    fprintf(file, "and a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 26: {
                    fprintf(file, "or a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    fprintf(file, "\n");
                    break;
                }
                case 28: {
                    if (node->right) {
                        fprintf(file, "xori a0, a3, -1\n");
                    }
                    else {
                        fprintf(file, "xori a0, a0, -1\n");
                    }
                    break;
                }
                case 29: {
                    fprintf(file, "xor a0, a0, a3\n");
                    break;
                }
                case 30: {
                    fprintf(file, "xor a0, a0, a3\n");
                    fprintf(file, "sw a0, 0(a1)\n");
                    break;
                }
                case 31: {
                    fprintf(file, "and a0, a0, a3\n");
                    break;
                }
                case 32: {
                    fprintf(file, "or a0, a0, a3\n");
                    break;
                }
                case 33: {
                    if (node->right) {
                        fprintf(file, "mv a1, a3\n");
                        fprintf(file, "lw a0, 0(a1)\n");
                        fprintf(file, "mv a2, a5\n");
                    }
                    else {
                        fprintf(file, "mv a1, a0\n");
                        fprintf(file, "lw a0, 0(a1)\n");
                    }
                }
                case 34: {
                    if (node->right) {
                        fprintf(file, "mv a0, a4\n");
                    }
                    else {
                        fprintf(file, "mv a0, a1\n");
                    }
                    break;
                }
                case 35: {
                    fprintf(file, "mul a6, a2, a3\n");
                    fprintf(file, "add a1, a1, a6\n");
                    fprintf(file, "lw a0, 0(a1)\n");
                    break;
                }
            }
            fprintf(file, "# end OP\n");

        }
        else if (node->left == NULL && node->right == NULL && node->token && node->token->type == NAME
            && node->generated == 0) {
            getToken(node->token->vec->data, file, currentFunction->name, 0);
        }
        else if (node->left == NULL && node->right == NULL && node->token && node->token->type == NUMBER
            && node->generated == 0) {
            fprintf(file, "li a0, %s\n", node->token->vec->data);
            fprintf(file, "li a1, 0\n");
            fprintf(file, "li a2, 0\n");
            }
        else if (node->token && node->token->type == DELIMITER && strcmp(node->token->vec->data, "(") == 0) {
            if (node->right) {
                generate(node->right, file);
            }
        }
        else if (node->token && node->token->type == DELIMITER && strcmp(node->token->vec->data, "[") == 0) {
            if (node->right) {
                generate(node->right, file);
            }
        }
        else if (node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "if") == 0) {
            if (node->bottom || node->bottom->token && node->bottom->token->type == DELIMITER
                && strcmp(node->bottom->token->vec->data, "()") == 0) {
                node = node->bottom;
                generate(node->next, file);
                int t = counter;
                counter += 2;
                fprintf(file, "beq a0, x0, .loop%d\n", t);

                node = node->bottom;
                if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                    generate(node->next, file);
                }
                else {
                    printErrorMessage(16);
                    return;
                }
                
                fprintf(file, "j .loop%d\n", t+1);

                fprintf(file, ".loop%d\n", t);
                node = node->bottom;
                if (node && node->bottom && node->bottom->token
                    && node->bottom->token->type == KWORD && strcmp(node->bottom->token->vec->data, "else") == 0) {
                    node = node->bottom;
                    node = node->bottom;
                    if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                        generate(node->next, file);
                    }
                    else {
                        printErrorMessage(15);
                        return;
                    }
                }
                
                

                fprintf(file, ".loop%d\n", t + 1);
            }
            else {
                printErrorMessage(15);
                return;
            }
        }
        else if (node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "while") == 0) {
            int t = counter;
            counter += 2;
            fprintf(file, ".loop%d\n", t);

            if (node->bottom || node->bottom->token && node->bottom->token->type == DELIMITER
                && strcmp(node->bottom->token->vec->data, "()") == 0) {
                node = node->bottom;
                generate(node->next, file);
            }
            else {
                printErrorMessage(16);
                return;
            }
            fprintf(file, "beq a0, x0, .loop%d\n", t + 1);

            node = node->bottom;
            if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                generate(node->next, file);
            }
            else {
                printErrorMessage(16);
                return;
            }
            
            fprintf(file, "j .loop%d\n", t);
            fprintf(file, ".loop%d\n", t+1);

            
        }
        else if (node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "for") == 0) {
            int t = counter;
            counter += 2;
            if (node && node->bottom && node->bottom->bottom && node->bottom->bottom->bottom) {
                node = node->bottom;

                generate(node->next, file);
                fprintf(file, ".loop%d\n", t);
                node = node->bottom;
                
                generate(node->next, file);

                fprintf(file, "beq a0, x0, .loop%d\n", t + 1);
                node = node->bottom;
                generate(node->bottom->next, file);
                generate(node->next, file);
                node = node->bottom;
                
                fprintf(file, "j .loop%d\n", t);
                fprintf(file, ".loop%d\n", t+1);
            }
            else {
                printErrorMessage(17);
            }
        }
        
        generate(node->bottom, file);
    }
}


void generateCode(Node* code, char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printErrorMessage(12);
        return;
    }
    fprintf(file, "## Generated by codeGenerator\n");
    startOfFile(file);
    generate(code, file);
    endOfFile(file);
}
