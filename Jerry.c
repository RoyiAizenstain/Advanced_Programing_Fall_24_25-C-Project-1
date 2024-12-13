#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include <stdio.h>

//typedef enum e_status { Success, Fail, FailRead, BadArg } Status;

// Create Jerry
Status CreateJerry(Jerry **pp_jerry, char *id, int happiness, Planet *p_planet, char *dimension,
                   int characteristics_size) {
    // Check if the arguments are valid
    if (id == NULL || characteristics_size <= 0 || happiness > 100 || happiness <
        0) {
        return BadArg;
    }
    // Allocate memory for the Jerry
    ALLOCATE(*pp_jerry, Jerry, 1);
    // Allocate memory for the id
    ALLOCATE((*pp_jerry)->id, char, strlen(id) + 1);
    strcpy((*pp_jerry)->id, id);
    (*pp_jerry)->happiness = happiness;
    Origin *p_origin;
    CreateOrigin(&p_origin, p_planet, dimension);
    (*pp_jerry)->origin = p_origin;
    // Allocate memory for the characteristics
    ALLOCATE((*pp_jerry)->characteristics, PhysicalCharacteristics, characteristics_size);
    (*pp_jerry)->characteristics_size = characteristics_size;

    return Success;
}

Status CreatePlanet(Planet **p_planet, char *name, int x, int y, int z) {
    // Check if the arguments are valid
    if (name == NULL || x < 0 || y < 0 || z < 0) {
        return BadArg;
    }
    // Allocate memory for the planet
    ALLOCATE(*p_planet, Planet, 1);
    // Allocate memory for the name
    ALLOCATE((*p_planet)->name, char, strlen(name) + 1);
    strcpy((*p_planet)->name, name);
    (*p_planet)->x = x;
    (*p_planet)->y = y;
    (*p_planet)->z = z;

    return Success;
}

Status CreatePhysicalCharacteristic(PhysicalCharacteristics **characteristic, char *name, double value) {
    // Check if the arguments are valid
    if (name == NULL || value < 0) {
        return BadArg;
    }
    // Allocate memory for the characteristic
    ALLOCATE(*characteristic, PhysicalCharacteristics, 1);
    // Allocate memory for the name
    ALLOCATE((*characteristic)->name, char, strlen(name) + 1);
    strcpy((*characteristic)->name, name);
    (*characteristic)->value = value;
    return Success;
}

Status CreateOrigin(Origin **origin, Planet *planet, char *dimension) {
    // Check if the arguments are valid
    if (planet == NULL || dimension == NULL) {
        return BadArg;
    }
    // Allocate memory for the origin
    ALLOCATE(*origin, Origin, 1);
    (*origin)->planet = planet;
    // Allocate memory for the dimension
    ALLOCATE((*origin)->dimension, char, strlen(dimension) + 1);
    strcpy((*origin)->dimension, dimension);
    return Success;
}

bool HasPhysicalCharacteristic(Jerry *p_jerry, char *name) {
    // Check if the arguments are valid
    if (p_jerry == NULL || name == NULL) {
        return False;
    }
    // Check if the Jerry has the characteristic
    for (int i = 0; i < p_jerry->characteristics_size; i++) {
        if (strcmp(p_jerry->characteristics[i].name, name) == 0) {
            return True;
        }
    }
    return False;
}

Status AddPhysicalCharacteristic(Jerry *p_jerry, char *name, double value) {
    // CREATE A NEW CHARACTERISTIC
    PhysicalCharacteristics *characteristic;
    CreatePhysicalCharacteristic(&characteristic, name, value);
    // Check if the arguments are valid
    if (p_jerry == NULL || characteristic == NULL) {
        return BadArg;
    }
    // Check if the Jerry already has the characteristic
    for (int i = 0; i < p_jerry->characteristics_size; i++) {
        if (p_jerry->characteristics[i].name == NULL) {
            p_jerry->characteristics[i] = *characteristic;
            return Success;
        }
    }
    // Reallocate memory for the characteristics
    REALLOCATE(p_jerry->characteristics, p_jerry->characteristics_size + 1);
    p_jerry->characteristics_size++;
    p_jerry->characteristics[p_jerry->characteristics_size - 1] = *characteristic;
    return Success;
}

Status RemovePhysicalCharacteristic(Jerry *p_jerry, char *name) {
    // Check if the arguments are valid
    if (p_jerry == NULL || name == NULL) {
        return BadArg;
    }
    // Check if the Jerry has the characteristic
    if (HasPhysicalCharacteristic(p_jerry, name) == False) {
        return Fail;
    }
    // Remove the characteristic
    PhysicalCharacteristics *temp;
    ALLOCATE(temp, PhysicalCharacteristics, p_jerry->characteristics_size - 1);
    int j = 0;
    // Copy the characteristics to the new array
    for (int i = 0; i < p_jerry->characteristics_size; i++) {
        if (strcmp(p_jerry->characteristics[i].name, name) != 0) {
            temp[j] = p_jerry->characteristics[i];
            j++;
        }
    }
    // Free the old array and update the Jerry
    free(p_jerry->characteristics);
    p_jerry->characteristics = temp;
    p_jerry->characteristics_size--;
    return Success;
}

//Planet to string format
static char* PlanetToString(Jerry *jerry) {

    char *result;
    char *PlantName = jerry->origin->planet->name;
    char PlantX = jerry->origin->planet->x+'0';
    char PlantY = jerry->origin->planet->y+'0';;
    char PlantZ = jerry->origin->planet->z+'0';
    sprintf(result, "%s", PlantName);
    fprintf(result, "%c", PlantX);
    return result;
}

Status PrintJerry(Jerry *jerry) {
    // Check if the arguments are valid
    if (jerry == NULL) {
        return BadArg;
    }
    // Print the Jerry
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d\n", jerry->happiness);
    printf("Origin : %s\n", jerry->origin->dimension);
    printf("Planet : %s (%d,%d,%d)\n", jerry->origin->planet->name,jerry->origin->planet->x,jerry->origin->planet->y,jerry->origin->planet->z);
    printf("Coordinates: (%d, %d, %d)\n", jerry->origin->planet->x, jerry->origin->planet->y, jerry->origin->planet->z);
    printf("Characteristics:\n");
    for (int i = 0; i < jerry->characteristics_size; i++) {
        printf("Name: %s, Value: %lf\n", jerry->characteristics[i].name, jerry->characteristics[i].value);
    }
    return Success;
}


