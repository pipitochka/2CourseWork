#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vector.h"

//allocate memory for vector
Vector* initVector() {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        printf("Error in allocation memory for Vector\n");
        return NULL;
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


