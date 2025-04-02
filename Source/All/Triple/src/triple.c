#include "../include/triple.h"

#include <stdlib.h>
#include <string.h>

Triple* initTriple(char* name, int size, enum Type type, int nums) {
    Triple* triple = (Triple*)malloc(sizeof(Triple));
    triple->next = NULL;
    triple->name = name;
    triple->size = size;
    triple->type = type;
    triple->nums = nums;
    return triple;
}

Triple* findTriple(Triple* first, char* name) {
    if (first != NULL) {
        if (strcmp(first->name, name) == 0) {
            return first;
        }
        else {
            return findTriple(first->next, name);
        }
    }
    else {
        return NULL;
    }
}

void deleteTriple(Triple* first) {
    if (first != NULL) {
        deleteTriple(first->next);
    }
    free(first);
}

void addTriple(Triple** first, char* name, int size, enum Type type, int nums) {
    if (*first == NULL) {
        *first = initTriple(name, size, type, nums);
        return;
    }
    Triple* current = *first;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = initTriple(name, size, type, nums);
}

