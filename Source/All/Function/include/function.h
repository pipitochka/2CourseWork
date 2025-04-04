#ifndef FUNCTION_H
#define FUNCTION_H

#include "../../VariableList//include/variableList.h"

enum ReturnType {RETURN_INT, RETURN_CHAR, RETURN_VOID};

typedef struct Function {
    char *name;
    enum ReturnType returnType;
} Function;

#endif //FUNCTION_H
