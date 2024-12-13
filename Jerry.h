#ifndef JERRY_H
#define JERRY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct Planet_t {
    char name[];
    int x;
    int y;
    int z;
} Planet;

typedef struct Origin_t {
    Planet *pplanet;          //pointer?
    char dimension[];
} Origin;

typedef struct PhysicalCharacteristics_t {
    char name[];
    double value;
} PhysicalCharacteristics;

typedef struct JERRY_t {
    char id[];
    int happiness;
    Origin origin;
    PhysicalCharacteristics *characteristics[];
    int characteristics_size;
} JERRY;

#endif //JERRY_H
