#include "../include/function.h"
#include "../../../Safe/Error/include/error.h"
#include <stdlib.h>

// allocate memory for function
// if allocation can not be done return NULL and print a message
// makes all fields 0 or NULL
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

// deallocate memory for function
void deleteFunction(Function *function) {
    if (function != NULL) {
        free(function);
    }
}

// deallocate memory for function
void addParametrToFunction(Function *function, Variable* variable) {
    function->numParameters = addVariable(&function->parameters, variable);
    variable->counter = function->numParameters;
}

//function to add Variable to parameters (VariableList)
//increase variable counter to easily takes offset on a stack
void addVariableToFunction(Function *function, Variable* variable) {
    function->numVariables = addVariable(&function->variables, variable);
    variable->counter = function->numVariables;
}

//function to add Variable to variables (VariableList)
//increase variable counter to easily takes offset on a stack
Variable* getVariableFromFunction(Function *function, char *name) {
    Variable* variable = findVariable(function->variables, name);
    if (variable != NULL) {
        return variable;
    }
    return findVariable(function->parameters, name);
}
