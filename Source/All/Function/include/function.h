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
} Function;

Function *initFunction(char *name, enum ReturnType returnType);

void deleteFunction(Function *function);

void addParametrToFunction(Function *function, Variable* variable);
void addVariableToFunction(Function *function, Variable* variable);

#endif //FUNCTION_H
