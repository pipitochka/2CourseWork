#include "../include/error.h"

#include <stdlib.h>
#include <stdio.h>

const char* errors[] = {
    "error: unterminated string\n",  // 0
    "error: unterminated character\n",  // 1
    "Error in symbol %c\n",  // 2
    "Invalid operator\n",  // 3
    "Invalid character\n",  // 4
    "Assert fault\n",  // 5
    "File not found\n",  // 6
    "Allocation memory for Node error\n",  // 7
    "Null node error\n",  // 8
    "Error there is left list\n",  // 9
    "Error there is left list (alternative message)\n",  // 10
    "Error no left operator for assignments\n",  // 11
    "Error no file to write\n",  // 12
    "Invalid syntax\n",  // 13
    "Two binary OP\n",  // 14
    "Invalid AST\n",  // 15
    "Error in if-else construction\n",  // 16
    "Error in if-else construction (alternative)\n",  // 17
    "Variable exists\n",  // 18
    "int* int[50]\n",  // 19
    "Invalid amount of scopes" // 20
};



void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

