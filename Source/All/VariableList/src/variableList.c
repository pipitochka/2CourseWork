#include "../include/variableList.h"

#include <stdlib.h>
#include <string.h>

VariableList* initVariableList() {
    VariableList* variableList = (VariableList*)malloc(sizeof(VariableList));
    return variableList;
}


Variable* findVariable(VariableList* first, char* name) {
    if (first != NULL) {
        if (first->variable != NULL && first->variable->name != NULL) {
            if (strcmp(first->variable->name, name) == 0) {
                return first->variable;
            }
        }
        else {
            return findVariable(first->next, name);
        }
    }
    return NULL;
}

void deleteVariableList(VariableList* first) {
    if (first != NULL) {
        deleteVariableList(first->next);
        if (first->variable != NULL) {
            deleteVariable(first->variable);
        }
        free(first);
    }
}

void addVariable(VariableList** first, Variable* variable) {
    if (*first == NULL) {
        (*first) = initVariableList();
        (*first)->variable = variable;
        return;
    }
    VariableList* current = *first;
    while (current->next != NULL) {
        current = current->next;
    }
    VariableList* newVariableList = initVariableList();
    newVariableList->variable = variable;
    newVariableList->counter = current->counter + 1;
    current->next = newVariableList;
}

