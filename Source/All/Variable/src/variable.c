#include "../include/variable.h"

#include <stdlib.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

//function to allocate memory for variable
//makes others field 0 or NULL
//if allocation can not be done return NULL
//return point to new Variable
Variable* initVariable(char* name, int size, enum Type type, int nums, int isRef) {
    Variable* triple = (Variable*)malloc(sizeof(Variable));
    if (triple == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    triple->name = name;
    triple->size = size;
    triple->type = type;
    triple->nums = nums;
    triple->counter = 0;
    triple->isRef = isRef;
    return triple;
}

//function to deallocate memory for variable
//don't deallocate memory for name
void deleteVariable(Variable* first) {
    free(first);
}
