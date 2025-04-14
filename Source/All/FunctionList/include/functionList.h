#ifndef FUNCTIONLIST_H
#define FUNCTIONLIST_H

#include "../../Function/include/function.h"

typedef struct FunctionList {
    Function* function;
    struct FunctionList* next;
} FunctionList;

//function to allocate memory for functionList
FunctionList* initFunctionList();

//function to find function in functionList
Function* findFunction(FunctionList* first, char* name);

//function to deallocate memory for functionList
void deleteFunctionList(FunctionList* first);

//function to add function to functionList
void addFunction(FunctionList** first, Function* function);

#endif //FUNCTIONLIST_H
