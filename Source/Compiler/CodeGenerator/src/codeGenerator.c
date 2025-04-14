#include "../include/codeGenerator.h"
#include <stdio.h>
#include <string.h>
#include "../../../Safe/Error/include/error.h"

//global variable to calculate .loop number
int counter = 0;

//flag of entry point of programm
int isMainExist = 0;

//list of global variables
extern VariableList* globalVariables;

//pointer to current function
extern Function* currentFunction;

//list of all functions
extern FunctionList* currentFunctionList;

//function to prepare file, make sections before .data
void startOfFile(FILE* file) {
    if (file == NULL) {
        return;
    }
    fprintf(file, ".data\n");
    
    VariableList* data = globalVariables;

    //writing global variables
    while (data != NULL) {
        if (data->variable->type == VAR) {
            fprintf(file, "%s: .word 0\n", data->variable->name);
        }
        data = data->next;
    }

    //start section .data
    fprintf(file, ".text\n");
    fprintf(file, ".global main\n");
    fprintf(file, "\n");
}

//finish file
void endOfFile(FILE* file) {
    if (file == NULL) {
        return;
    }
    fprintf(file, "\n");
    //call finish programm
    fprintf(file, "li a7, 10\n");
    fprintf(file, "ecall\n");
}

//function to compare string with mathematical sign
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

//function to get variable in function
//in offset calculation remember that first - parameters, after - variables
//load value of founded variable in a0 a1 a2 - value, address, size
void getToken(char* name, FILE* file, int down) {
    if (file == NULL || name == NULL) {
        return;
    }
    Function* function = currentFunction;
    if (function == NULL) {
        return;
    }
    down *= 12;
    int top = 0;
    //calculate global offset
    if (function) {
        top += function->numParameters + function->numVariables;
    }
    top *= 4;
    top += down;
    top += currentFunction->currentOffset;
    if (function != NULL) {
        Variable* q;

        //try to find variable in parameters
        q = findVariable(function->parameters, name);
        if (q != NULL) {

            //calculate offset
            int t = q->counter;
            t *= 4;
            top -= t;

            //loading variable in registrs
            fprintf(file, "addi a4, sp, %d\n", top + 4);
            fprintf(file, "mv a1, a4\n");
            fprintf(file, "lw a1, 0(a1)\n");
            fprintf(file, "lw a0, 0(a1)\n");
            fprintf(file, "lw a2, -4(a4)\n");
            return;
        }
        
        //try to find variable in variables
        q = findVariable(function->variables, name);
        if (q != NULL) {

            //calculate offset
            int t = q->counter;
            t *= 4;
            //skip parameters stack memory
            t += function->numParameters * 4;
            top -= t;

            //loading variable in registrs
            fprintf(file, "addi a4, sp, %d\n", top + 4);
            fprintf(file, "mv a1, a4\n");
            fprintf(file, "lw a1, 0(a1)\n");
            fprintf(file, "lw a0, 0(a1)\n");
            fprintf(file, "lw a2, -4(a4)\n");
            return;
        }
    }

    //trying to find variable in global variables
    Variable* q = findVariable(globalVariables, name);

    //loading variable in registrs
    if (q != NULL) {
        fprintf(file, "la a1, %s\n", q->name);
        fprintf(file, "lw a0, 0(a1)\n");
        fprintf(file, "li a2, %d\n", q->size);
        return;
    }

    //variable was not founded so print error
    printErrorMessage(17);
}

//function to prepare stack for function call after all parametres were loaded 
//recursively add all variables of function on the stack
//parameters was taken from AST
void printLocalVariables(FILE* file, Function* function) {
    VariableList* variables = function->variables;
    int counter = 0;
    while (variables != NULL) {
        //calculate current offset and move stack pointer
        //(variables->counter - counter) - size of current variable
        fprintf(file, "addi sp, sp, %d\n", -1 * (variables->counter - counter) * 4);
        counter = variables->counter;
        //loading variable on a stack
        fprintf(file, "addi a4, sp, 4\n");
        fprintf(file, "addi a5, sp, 8\n");
        fprintf(file, "sw a5, 0(a4)\n");
        if (variables->variable->type == MAS) {
            fprintf(file, "addi a6, sp, 12\n");
            fprintf(file, "sw a6, 4(a4)\n");
        }
        fprintf(file, "li a5, %d\n", variables->variable->size);
        fprintf(file, "sw a5, -4(a4)\n");
        variables = variables->next;
    }
}

//general function to analyse AST and generate code
//recursively analyse all node of AST
void generate(Node* node, FILE* file) {
    if (node == NULL || file == NULL) {
        return;
    }
    if (node != NULL) {
        //if founded function declaration
        if (node && node->function != NULL) {
            fprintf(file, "%s:\n", node->function->name);
            currentFunction = node->function;

            //case main function
            //difference - no other function call main so we need to prepare stack and push variables independently
            if (strcmp(node->function->name, "main") == 0) {
                isMainExist = 1;
                
                //allocation parametrs on stack
                printLocalVariables(file, node->function);

                //generate body of funtion
                node = node->bottom;
                generate(node->next, file);

                //stack clearing and print signal for debug
                fprintf(file, "addi sp, sp, %d\n", (currentFunction->numVariables) * 4);
                fprintf(file, "## end function %s\n", node->top->function->name);
                
                //go to next Node
                node = node->bottom;
            }
            //case not main function
            else {
                //save the return address to the stack because in recursion it will be overwritten 
                fprintf(file, "addi sp, sp, -4\n");
                fprintf(file, "sw ra, 0(sp)\n");

                //change current offset
                node->function->currentOffset = 4;

                //generate body of function
                node = node->bottom;
                generate(node->next, file);

                //restoring the return address and go out from a function
                fprintf(file, "lw ra, 0(sp)\n");
                fprintf(file, "addi sp, sp, 4\n");
                fprintf(file, "ret\n");
                fprintf(file, "## end function %s\n", node->top->function->name);

                //go to the next node
                node = node->bottom;
            }
        }
        
        //if founded function call 
        if (node && node->type == FUNCTION_CALL) {
            //preparing a stack
            //load all parameters to call a gunction
            Node* q = node->next;

            //counter to calculate offset as we change sp during loading wariables
            int counter = 0;
            while (q && q->token) {

                //loading variable by value
                if (q->token->type == NAME) {
                    //get value in a0, a1, a2 
                    getToken(q->token->vec->data, file, counter);
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a0, 0(sp)\n");

                    //change the address of a local variable
                    fprintf(file, "mv a1, sp\n");
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a1, 0(sp)\n");
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a2, 0(sp)\n");

                    //go to the next variable and increase a counter
                    q = q->bottom;
                    counter++;
                }
                
                //loading number
                else if (q->token->type == NUMBER) {
                    //loading number by it value
                    fprintf(file, "li a0, %s\n", q->token->vec->data);
                    fprintf(file, "li a1, 0\n");
                    fprintf(file, "li a2, 4\n");

                    //change the address of a local variable
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a0, 0(sp)\n");
                    fprintf(file, "mv a1, sp\n");
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a1, 0(sp)\n");
                    fprintf(file, "addi sp, sp, -4\n");
                    fprintf(file, "sw a2, 0(sp)\n");

                    //go to the next variable and increase a counter
                    q = q->bottom;
                    counter++;
                }

                //loading variable by it adress 
                else if (q->token->type == BIN_OPERATOR || q->token->type == UNAR_OPERATOR) {
                    if (strcmp(q->token->vec->data, "&") == 0 && q->next && q->next->token->type == NAME) {
                        //get a variable in a0 a1 a2
                        getToken(q->next->token->vec->data, file, counter);
                        fprintf(file, "addi sp, sp, -4\n");
                        fprintf(file, "mv a0, a1\n");
                        fprintf(file, "sw a0, 0(sp)\n");
                        fprintf(file, "mv a1, sp\n");
                        fprintf(file, "addi sp, sp, -4\n");
                        fprintf(file, "sw a1, 0(sp)\n");
                        fprintf(file, "addi sp, sp, -4\n");
                        fprintf(file, "sw a2, 0(sp)\n");

                        //go to the next variable and increase a counter
                        q = q->bottom;
                        counter++;
                    }
                    //error situation, trash if funtion call
                    else {
                        printErrorMessage(20);
                        return;
                    }
                }
                else {
                    break;
                }
            }
            //find function which we will call
            Function * function = findFunction(currentFunctionList, node->token->vec->data);

            //move stack pointer for function variables 
            printLocalVariables(file, function);

            //call function
            fprintf(file, "call %s\n", node->token->vec->data);

            //return stack to previous after function call
            fprintf(file, "addi sp, sp, %d\n", (function->numParameters + function->numVariables) * 4);

            //go to next
            node = node->bottom;
        }
        
        //analyse a tree
        if (node && !(node->next &&
            (node->next->token->type == NUMBER
                || node->next->token->type == STRING
                || node->next->token->type == NAME
                || (node->next->token->type == BIN_OPERATOR && strcmp(node->next->token->vec->data, "[") == 0)))) {
            generate(node->next, file);
        }
        
        //analyse a tree
        if (node && node->next && node->next->token->type == NAME && node->next->bottom && node->next->bottom->type == FUNCTION_CALL) {
            generate(node->next->bottom, file);
        }

        //analyse an operator Node
        if (node && node->token && (node->token->type == BIN_OPERATOR || node->token->type == UNAR_OPERATOR)) {
            fprintf(file, "# start OP\n");

            //calculate right son
            generate(node->right, file);
            //save the right son on a stack
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

            //calculate left son
            generate(node->left, file);
            if (node->left) {
                node->left->generated = 1;
            }

            //take a right son from a stack
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

            //switch by operator value
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
                    fprintf(file, "sub a0, a0, a3\n");
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
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+2);
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+2);
                    fprintf(file, "\n");
                    counter += 3;
                    break;
                }
                case 13: {
                    fprintf(file, "beq a0, x0, loop%d\n", counter);
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "bne a3, x0, loop%d\n", counter+1);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+2);
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+2);
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
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 15: {
                    fprintf(file, "beq a0, a3, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 16: {
                    fprintf(file, "beq a0, a3, loop%d\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 17: {
                    fprintf(file, "bge a1, a3, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 18: {
                    fprintf(file, "bge a0, a3, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 19: {
                    fprintf(file, "blt a0, a3, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
                    fprintf(file, "\n");
                    
                    counter += 2;
                    
                    break; 
                }
                case 20: {
                    fprintf(file, "bgt a0, a3, loop%d\n", counter);
                    fprintf(file, "li a0 0\n");
                    fprintf(file, "j loop%d\n", counter+1);
                    fprintf(file, "\n");
                    
                    fprintf(file, "loop%d:\n", counter);
                    fprintf(file, "li a0 1\n");
                    fprintf(file, "\n");

                    fprintf(file, "loop%d:\n", counter+1);
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
                    fprintf(file, "add a1, a0, a6\n");
                    fprintf(file, "lw a0, 0(a1)\n");
                    break;
                }
            }
            fprintf(file, "# end OP\n");
        }

        //analyse situation with name Node 
        else if (node && node->left == NULL && node->right == NULL && node->token && node->token->type == NAME
            && node->generated == 0) {
            //check if it is not function 
            if (findFunction(currentFunctionList,node->token->vec->data) == NULL) {
                //get variable in a0 a1 a2
                getToken(node->token->vec->data, file, 0);
            }
            else {
                //if it is function call it
                generate(node->bottom, file);
            }
        }

        //analyse situation with number Node 
        else if (node && node->left == NULL && node->right == NULL && node->token && node->token->type == NUMBER
            && node->generated == 0) {
            //load it value in a0, a1, a2
            fprintf(file, "li a0, %s\n", node->token->vec->data);
            fprintf(file, "li a1, 0\n");
            fprintf(file, "li a2, 0\n");
            }

        //analyse open scope Node
        else if (node && node->token && node->token->type == DELIMITER && strcmp(node->token->vec->data, "(") == 0) {

            //calculate value in scope
            if (node->right) {
                generate(node->right, file);
            }
        }

        //analyse open massive scope Node
        else if (node && node->token && node->token->type == DELIMITER && strcmp(node->token->vec->data, "[") == 0) {

            //calculate value in scope
            if (node->right) {
                generate(node->right, file);
            }
        }

        //analyse if Node
        else if (node && node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "if") == 0) {
            if (node->bottom || node->bottom->token && node->bottom->token->type == DELIMITER
                && strcmp(node->bottom->token->vec->data, "()") == 0) {
                node = node->bottom;

                //checking the condition 
                generate(node->next, file);
                int t = counter;
                counter += 2;

                //loop for true 
                fprintf(file, "beq a0, x0, loop%d\n", t);

                //generate body of true
                node = node->bottom;
                if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                    generate(node->next, file);
                }
                else {
                    //for some mistakes in AST
                    printErrorMessage(16);
                    return;
                }
                
                fprintf(file, "j loop%d\n", t+1);

                //loop for false
                fprintf(file, "loop%d:\n", t);
                node = node->bottom;

                //checking of else block
                if (node && node->bottom && node->bottom->token
                    && node->bottom->token->type == KWORD && strcmp(node->bottom->token->vec->data, "else") == 0) {
                    node = node->bottom;
                    node = node->bottom;

                    //generate code of else block
                    if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                        generate(node->next, file);
                    }
                    else {
                        //for some mistakes in AST
                        printErrorMessage(15);
                        return;
                    }
                }
                fprintf(file, "loop%d:\n", t + 1);
            }
            else {
                //for mistakes in AST
                printErrorMessage(15);
                return;
            }
        }

        //analyse while Node
        else if (node && node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "while") == 0) {
            int t = counter;
            counter += 2;
            fprintf(file, "loop%d:\n", t);

            //generate block of condition
            if (node->bottom || node->bottom->token && node->bottom->token->type == DELIMITER
                && strcmp(node->bottom->token->vec->data, "()") == 0) {
                node = node->bottom;
                generate(node->next, file);
            }
            else {
                printErrorMessage(16);
                return;
            }

            //check condition
            fprintf(file, "beq a0, x0, loop%d\n", t + 1);

            //block of statement
            node = node->bottom;
            if (node && node->next && node->next->token && node->next->token->type == SCOPE_OPEN) {
                generate(node->next, file);
            }
            else {
                printErrorMessage(16);
                return;
            }

            //jump to check
            fprintf(file, "j loop%d\n", t);

            //jump to final part
            fprintf(file, "loop%d:\n", t+1);
        }

        //analyse for Node
        else if (node && node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "for") == 0) {
            int t = counter;
            counter += 2;
            if (node && node->bottom && node->bottom->bottom && node->bottom->bottom->bottom) {
                node = node->bottom;

                //generate preparation for for block
                generate(node->next, file);
                fprintf(file, "loop%d:\n", t);
                node = node->bottom;

                //generate check block
                generate(node->next, file);
                fprintf(file, "beq a0, x0, loop%d\n", t + 1);

                //generate statement block and update block
                node = node->bottom;
                generate(node->bottom->next, file);
                generate(node->next, file);
                node = node->bottom;
                
                fprintf(file, "j loop%d\n", t);
                fprintf(file, "loop%d:\n", t+1);
            }
            else {
                //for error in AST
                printErrorMessage(17);
            }
        }

        //analyse return Node
        else if (node && node->token && node->token->type == KWORD && strcmp(node->token->vec->data, "return") == 0) {
            //move to a0, a1, a2 statement
            generate(node->bottom, file);
            fprintf(file, "lw ra, 0(sp)\n");
            fprintf(file, "addi sp, sp, 4\n");
            fprintf(file, "ret\n");
            node = node->bottom->bottom;
        }

        if (node) {
            generate(node->bottom, file);
        }
    }
}


//main function to generate code from AST
//open file and make preparations 
void generateCode(Node* code, char* fileName) {
    //opening file
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printErrorMessage(4);
        return;
    }
    fprintf(file, "## Generated by codeGenerator\n");
    
    //preparations
    startOfFile(file);

    //analyse AST and write in the file
    generate(code, file);
    if (isMainExist == 0) {
        printErrorMessage(18);
    }

    //final steps
    endOfFile(file);
    fclose(file);

    //deallocation memory
    deleteFunctionList(currentFunctionList);
    deleteVariableList(globalVariables);
    currentFunctionList = NULL;
    globalVariables = NULL;
}
