#include "../include/functionList.h"

#include <stdlib.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

//function to allocate memory for functionList
//if allocation can not be done return NULL and print a message
FunctionList* initFunctionList() {
    FunctionList* list = (FunctionList*)malloc(sizeof(FunctionList));
    if (list == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    return list;
}

//function to find function in functionList
//return NULL if function is not in List else return pointer on a function
//do it by recursion 
Function* findFunction(FunctionList* first, char* name) {
    if (first != NULL && name != NULL) {
        if (first->function != NULL && first->function->name != NULL && strcmp(first->function->name, name) == 0) {
            return first->function;
        }
        if (first->next != NULL && first->next->function != NULL) {
            return findFunction(first->next, name);
        }
        return NULL;
    }
    return NULL;
}

//function to deallocate memory for functionList
//recursively call deleteFunction for all elements of FunctionList
//deallocate memory for elements of FunctionList
void deleteFunctionList(FunctionList* first) {
    if (first != NULL) {
        if (first->function) {
            deleteFunction(first->function);
        }
        deleteFunctionList(first->next);
        free(first);
    }
}

//function to add function to functionList
//if functionList is NULL makes a functionList
//recursively find last elements of functionList
//add new element after it with pointer to the function inside
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