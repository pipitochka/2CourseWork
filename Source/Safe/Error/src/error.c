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
    "Error threre is left list" //9
};


void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

