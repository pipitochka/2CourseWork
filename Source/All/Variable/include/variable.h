#ifndef VARIABLE_H
#define VARIABLE_H

//types of variable
enum Type{VAR, MAS};

typedef struct Variable {
    char* name;
    int size;
    enum Type type;
    int nums;
    int counter;
    int isRef;
} Variable;

//function to allocate memory for variable
Variable* initVariable(char* name, int size, enum Type type, int nums, int isRef);

//function to deallocate memory for variable
//don't deallocate memory for name
void deleteVariable(Variable* first);

#endif //VARIABLE_H
