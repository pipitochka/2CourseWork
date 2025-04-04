#include "../include/variable.h"

#include <stdlib.h>
#include <string.h>

Variable* initVariable(char* name, int size, enum Type type, int nums) {
    Variable* triple = (Variable*)malloc(sizeof(Variable));
    triple->name = name;
    triple->size = size;
    triple->type = type;
    triple->nums = nums;
    return triple;
}

void deleteVariable(Variable* first) {
    free(first);
}
