#include "../include/functionList.h"

#include <stdlib.h>
#include <string.h>

FunctionList* initFunctionList() {
    FunctionList* list = (FunctionList*)malloc(sizeof(FunctionList));

    return list;
}

Function* findFunction(FunctionList* first, char* name) {
    if (first != NULL) {
        if (first->function && first->function->name && strcmp(first->function->name, name) == 0) {
            return first->function;
        }
        else {
            return findFunction(first->next, name);
        }
    }
    return NULL;
}

void deleteFunctionList(FunctionList* first) {
    if (first != NULL) {
        if (first->function) {
            deleteFunction(first->function);
        }
        deleteFunctionList(first->next);
        free(first);
    }
    
}

void addFunction(FunctionList** first, Function* function) {
    if (*first == NULL) {
        *first = initFunctionList();
        (*first)->function = function;
        return;
    }
    FunctionList* current = *first;
    while (current->next != NULL) {
        current = current->next;
    }
    FunctionList* newFunctionList = initFunctionList();
    current->next = newFunctionList;
    newFunctionList->function = function;
}