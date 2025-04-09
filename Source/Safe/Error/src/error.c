#include "../include/error.h"

#include <stdlib.h>
#include <stdio.h>

const char* errors[] = {
    "error: unterminated string\n",  // 0
    "error: unterminated character\n",  // 1
    "error: invalid symbol %c\n",  // 2
    "error: invalid operator\n",  // 3
    "error: file not found\n",  // 4
    "Allocation memory error\n",  // 5
    "error: variable exists\n",  // 6
    "error: function exists\n",  // 7
    "error: invalid amount of scopes", // 8
    "error: invalid binary operation", // 9
    "error: invalid unary operation", // 10
    "error: invalid count of params of function", // 11
    "error: invalid AST", // 12
    "error: invalid function call", // 13
    "error: unterminated ( in function call", // 14
    "error: invalid syntax in operation kword, no ( after", // 15
    "error: not enough {", // 16
    "error: using unexpected variable", // 17
    "error: no function main" // 18
};



void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

