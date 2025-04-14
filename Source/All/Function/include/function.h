#ifndef FUNCTION_H
#define FUNCTION_H

#include "../../VariableList//include/variableList.h"

enum ReturnType {RETURN_INT, RETURN_CHAR, RETURN_VOID};

typedef struct Function {
    char *name;
    enum ReturnType returnType;
    VariableList *parameters;
    VariableList *variables;
    int numParameters;
    int numVariables;
    int currentOffset;
} Function;

//function to allocate memory for function
//others filed will be 0 or NULL except name and ReturnType
Function *initFunction(char *name, enum ReturnType returnType);

//function to deallocate memory for function
//don't deallocate memory for function name and Variables name
void deleteFunction(Function *function);

//function to add Variable to parameters (VariableList)
void addParametrToFunction(Function *function, Variable* variable);

//function to add Variable to variables (VariableList)
void addVariableToFunction(Function *function, Variable* variable);

#endif //FUNCTION_H
