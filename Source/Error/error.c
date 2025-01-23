#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

char* errors[] = {
    "error: unterminated string\n",
};


void printErrorMessage(const int errorCode) {
    if (errors[errorCode] == NULL) {
        exit(-1);
    }
    else {
        printf("%s\n", errors[errorCode]);
    }
}

