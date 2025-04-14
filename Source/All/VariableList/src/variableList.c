#include "../include/variableList.h"

#include <stdlib.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

//function to allocate memory for variableList
//if alloctaion can not be done return NULL
VariableList* initVariableList() {
    VariableList* variableList = (VariableList*)malloc(sizeof(VariableList));
    if (variableList == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    return variableList;
}

//function to find variable in variableList by name
//return point to founded variable or NULL if there is no variable inside variableList
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

//function to deallocate memory for variableList
//recursively deallocate memory for all objects
//also deallocate memory for variable
void deleteVariableList(VariableList* first) {
    if (first != NULL) {
        deleteVariableList(first->next);
        if (first->variable != NULL) {
            deleteVariable(first->variable);
        }
        free(first);
    }
}

//function to add variable into variableList
//also recalculate offset of stack and return it
//offset depend on type of variable and size of massive if it is a pointer
int addVariable(VariableList** first, Variable* variable) {
    if (*first == NULL) {
        (*first) = initVariableList();
        (*first)->variable = variable;
        if (variable->type == VAR) {
            (*first)->counter = 3;
            return 3;
        }
        if (variable->type == MAS) {
            (*first)->counter = variable->nums + 3;
            return variable->nums + 3;
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
        newVariableList->counter = current->counter + variable->nums + 3;
        return current->counter + variable->nums + 3;
    }
    
}


