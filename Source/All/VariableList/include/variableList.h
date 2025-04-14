#ifndef VARIABLELIST_H
#define VARIABLELIST_H
#include "../../Variable/include/variable.h"

typedef struct VariableList {
    Variable* variable;
    struct VariableList* next;
    int counter;
} VariableList;

//function to allocate memory for variableList
VariableList* initVariableList();

//function to find variable in variableList
Variable* findVariable(VariableList* first, char* name);

//function to deallocate memory for variableList
void deleteVariableList(VariableList* first);

//function to add variable into variableList
int addVariable(VariableList** first, Variable* variable);

#endif //VARIABLELIST_H
