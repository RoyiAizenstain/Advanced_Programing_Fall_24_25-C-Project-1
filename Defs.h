#ifndef DEFS_H
#define DEFS_H
#include <stdlib.h>
#include <stdio.h>

// Boolean type
typedef enum e_bool { False, True } bool;

// Status of the function
typedef enum e_status { Success, Fail, FailRead, BadArg } Status;

// Allocate memory for a variable of type
#define ALLOCATE(var, type, size) \
    if ((var = (type*)malloc(sizeof(type)*size)) == NULL) { \
        fprintf(stderr, "Memory allocation failed\n"); \
        return Fail; \
   }

// Reallocate memory for a variable of type
#define REALLOCATE(var, size)\
    void* ptr_new; \
    if ((ptr_new = realloc(var, sizeof(typeof(*var))*size)) == NULL) { \
        return Fail; \
   } var = ptr_new;\
   ptr_new = NULL;

// to int
#define TO_INT (*(int*)var)

#endif //DEFS_H
