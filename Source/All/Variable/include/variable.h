#ifndef VARIABLE_H
#define VARIABLE_H

enum Type{VAR, MAS};

typedef struct Variable {
    char* name;
    int size;
    enum Type type;
    int nums;
    int counter;
    int isRef;
} Variable;

Variable* initVariable(char* name, int size, enum Type type, int nums, int isRef);

void deleteVariable(Variable* first);

#endif //VARIABLE_H
