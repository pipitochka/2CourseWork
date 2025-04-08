#include "../include/function.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

Function *initFunction(char *name, enum ReturnType returnType) {
    Function *function = (Function *) malloc(sizeof(Function));
    if (function == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    function->name = name;
    function->returnType = returnType;
    function->parameters = NULL;
    function->variables = NULL;
    function->numParameters = 0;
    function->numVariables = 0;
    function->currentOffset = 0;
    return function;
}

void deleteFunction(Function *function) {
    if (function != NULL) {
        free(function);
    }
}

void addParametrToFunction(Function *function, Variable* variable) {
    addVariable(&function->parameters, variable);
    function->numVariables++;
}

void addVariableToFunction(Function *function, Variable* variable) {
    addVariable(&function->variables, variable);
    function->numParameters++;
}

Variable* getVariableFromFunction(Function *function, char *name) {
    Variable* variable = findVariable(function->variables, name);
    if (variable != NULL) {
        return variable;
    }
    return findVariable(function->parameters, name);
}

void add(int* x, int y) {
    *x += y;
}
