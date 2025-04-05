#ifndef FUNCTIONLIST_H
#define FUNCTIONLIST_H

#include "../../Function/include/function.h"

typedef struct FunctionList {
    Function* function;
    struct FunctionList* next;
} FunctionList;

FunctionList* initFunctionList();

Function* findFunction(FunctionList* first, char* name);

void deleteFunctionList(FunctionList* first);

void addFunction(FunctionList** first, Function* function);

#endif //FUNCTIONLIST_H
