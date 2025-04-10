#ifndef VARIABLELIST_H
#define VARIABLELIST_H
#include "../../Variable/include/variable.h"

typedef struct VariableList {
    Variable* variable;
    struct VariableList* next;
    int counter;
} VariableList;

VariableList* initVariableList();

Variable* findVariable(VariableList* first, char* name);

void deleteVariableList(VariableList* first);

int addVariable(VariableList** first, Variable* variable);

#endif //VARIABLELIST_H
