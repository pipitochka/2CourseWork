#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vector.h"

#include "../../../Safe/Error/include/error.h"

//allocate memory for vector
//return point to allocated vector or null if allocation cannot be competed
//makes fields size = 0(used memory) and capacity = 1(allocated memory)
//allocate memory for massive
Vector* initVector() {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    vec->size = 0;
    vec->capacity = 1;
    vec->data = malloc(vec->capacity * sizeof(char));
    if (vec->data == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    return vec;
}

//deallocate memory for vector
void freeVector(Vector* vec) {
    if (vec != NULL) {
        free(vec->data);  
        free(vec);        
    }
}

//add element in the end of vector
//if size > capacity reallocate memory and makes buffer bigger two times 
void pushBackVector(Vector* vec, const char q) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        char * new;
        if ((new = malloc(vec->capacity * sizeof(char))) == NULL) {
            printErrorMessage(5);
            return;
        }
        memcpy(new, vec->data, vec->size * sizeof(char));
        free(vec->data);
        vec->data = new;
        vec->data[vec->size] = q;
        vec->size++;
    }
    else {
        vec->data[vec->size] = q;
        vec->size++;
    }
}


