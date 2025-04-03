#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/error.h"

char* errors[] = {
    "error: unterminated string\n", //0
    "error: unterminated character\n",
    "Error in symbol %c\n",
    "Invalid operator\n",
    "Invalid character\n",
    "Assert fault\n", //5
    "File not found\n" //6
    "Allocation memory for Node error\n" //7
    "Null node error\n" //8
    "Error threre is left list\n" //9
    "Error threre is left list\n" //10
    "Error no left operator for assignments\n" //11
    "Error no file to write\n" //12
    "Invalid syntax\n" //13
    "Two binary OP\n" //14
    "Invalid AST\n" //15
    "Error in if-else construction\n" //16
    "Error in if-else construction\n" //17
};


void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

