#include <stdio.h>
#include "Defs.h"
#include<string.h>

#include "Jerry.h"


int main(void) {
    Jerry *pJerry = (Jerry *) 0;
    Origin origin;
    Planet *pPlanet = (Planet *) 0;
    CreatePlanet(&pPlanet, "Earth", 123.10,8392.00,99.20);
    Origin *pOrigin = (Origin *) 0;
    PhysicalCharacteristics *pCharacteristics = (PhysicalCharacteristics *) 0;
    PhysicalCharacteristics *pCharacteristics2 = (PhysicalCharacteristics *) 0;
    CreateJerry(&pJerry, "23dF21", 50, pPlanet, "C-137", 2);
    AddPhysicalCharacteristic(pJerry, "Height", 166.20);
    AddPhysicalCharacteristic(pJerry, "LimbsNumber", 4.00);
    //AddPhysicalCharacteristic(pJerry, "Weight", 80.00);
    bool royi = HasPhysicalCharacteristic(pJerry, "Height");

    Status status = PrintJerry(pJerry);
    //RemovePhysicalCharacteristic(pJerry, "Height");
    //AddPhysicalCharacteristic(pJerry, "Height", 1.5);

    DestroyJerry(pJerry);
    return 0;
}
