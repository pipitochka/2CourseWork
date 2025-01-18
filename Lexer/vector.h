#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <stdio.h>


//description of vector
typedef struct Vec {
    char* data;
    int size;
    int capacity;
} Vector;

//allocate memory for vector
Vector* initVector() {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        printf("Error in allocation memory for Vector\n");
        exit(-1);
    }
    vec->size = 0;
    vec->capacity = 1;
    vec->data = malloc(vec->capacity * sizeof(char));
    if (vec->data == NULL) {
        printf("Error in allocation memory for elements of Vector\n");
        exit(-1);
    }
    return vec;
}

//dealocate memory for vector
void freeVector(const Vector* vec) {
    free(vec->data);
}

//add element in the end of vector
void pushBackVector(Vector* vec, const char q) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        char * new;
        if ((new = malloc(vec->capacity * sizeof(char))) == NULL) {
            printf("Error in allocation memory for elements of Vector\n");
            exit(-1);
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


#endif //VECTOR_H
