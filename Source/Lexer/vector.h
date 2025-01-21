#ifndef VECTOR_H
#define VECTOR_H

//description of vector
typedef struct Vec {
    char* data;
    int size;
    int capacity;
} Vector;

//allocate memory for vector
Vector* initVector();

//dealocate memory for vector
void freeVector(const Vector* vec);

//add element in the end of vector
void pushBackVector(Vector* vec, const char q);

#endif //VECTOR_H
