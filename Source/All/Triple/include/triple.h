#ifndef TRIPLE_H
#define TRIPLE_H

enum Type{VAR, MAS};

typedef struct Triple {
    char* name;
    int size;
    struct Triple* next;
    enum Type type;
    int nums;
} Triple;

Triple* initTriple(char* name, int size, enum Type type, int nums);

Triple* findTriple(Triple* first, char* name);

void deleteTriple(Triple* first);

void addTriple(Triple** first, char* name, int size, enum Type type, int nums);

#endif //TRIPLE_H
