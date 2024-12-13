#ifndef JERRY_H
#define JERRY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

// Planet
typedef struct Planet_t {
    char *name;
    double x;
    double y;
    double z;
} Planet;

// Origin
typedef struct Origin_t {
    Planet *planet;
    char *dimension;
} Origin;

// Physical Characteristics
typedef struct PhysicalCharacteristics_t {
    char *name;
    double value;
} PhysicalCharacteristics;

// Jerry
typedef struct JERRY_t {
    char *id;
    int happiness;
    Origin *origin;
    PhysicalCharacteristics *characteristics;    // not sure
    int characteristics_size;
} Jerry;

// Create functions
Status CreateJerry(Jerry **pp_jerry, char *id, int happiness, Planet *p_planet, char *dimension, int characteristics_size);
Status CreatePlanet(Planet **p_planet, char *name, double x, double y, double z);
Status CreatePhysicalCharacteristic(PhysicalCharacteristics **pp_characteristic, char *name, double value);
Status CreateOrigin(Origin **pp_origin, Planet *p_planet, char *dimension);

// Physical Characteristics functions
bool HasPhysicalCharacteristic(Jerry *p_jerry, char *name);
Status AddPhysicalCharacteristic(Jerry *p_jerry, char *name, double value);
Status RemovePhysicalCharacteristic(Jerry *p_jerry, char *name);

// Print functions
Status PrintJerry(Jerry *p_jerry);
Status PrintPlanet(Planet *planet);

// Destroy functions
Status DestroyJerry(Jerry *jerry);
Status DestroyPlanet(Planet *planet);
Status DestroyPhysicalCharacteristic(PhysicalCharacteristics *characteristic);
Status DestroyOrigin(Origin *origin);


#endif //JERRY_H
