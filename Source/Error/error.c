#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

char* errors[] = {
    "error: unterminated string\n", //0
    "error: unterminated character\n",
    "Error in symbol %c\n",
    "Invalid operator\n",
    "Invalid character\n",
    "Assert fault\n", //5
    "File not found\n" //6
};


void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

