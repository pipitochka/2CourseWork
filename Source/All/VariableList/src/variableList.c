#include "../include/variableList.h"

#include <stdlib.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

VariableList* initVariableList() {
    VariableList* variableList = (VariableList*)malloc(sizeof(VariableList));
    if (variableList == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    return variableList;
}


Variable* findVariable(VariableList* first, char* name) {
    if (first != NULL) {
        if (first->variable != NULL && first->variable->name != NULL) {
            if (strcmp(first->variable->name, name) == 0) {
                return first->variable;
            }
        }
        return findVariable(first->next, name);
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

int addVariable(VariableList** first, Variable* variable) {
    if (*first == NULL) {
        (*first) = initVariableList();
        (*first)->variable = variable;
        if (variable->type == VAR) {
            (*first)->counter = 3;
            return 3;
        }
        if (variable->type == MAS) {
            (*first)->counter = variable->nums + 2;
            return variable->nums + 2;
        }
    }
    VariableList* current = *first;
    while (current->next != NULL) {
        current = current->next;
    }
    VariableList* newVariableList = initVariableList();
    newVariableList->variable = variable;
    current->next = newVariableList;
    if (variable->type == VAR) {
        newVariableList->counter = current->counter + 3;
        return current->counter + 3;
    }
    if (variable->type == MAS) {
        newVariableList->counter = current->counter + variable->nums + 2;
        return current->counter + variable->nums + 2;
    }
    
}


