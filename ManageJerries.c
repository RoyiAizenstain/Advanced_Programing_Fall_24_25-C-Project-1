#include <stdio.h>
#include "Defs.h"
#include<string.h>

#include "Jerry.h"


int main(void) {
    Jerry *pJerry = (Jerry *) 0;
    Origin origin;
    Planet *pPlanet = (Planet *) 0;
    CreatePlanet(&pPlanet, "Earth", 1, 2, 3);
    Origin *pOrigin = (Origin *) 0;
    PhysicalCharacteristics *pCharacteristics = (PhysicalCharacteristics *) 0;
    PhysicalCharacteristics *pCharacteristics2 = (PhysicalCharacteristics *) 0;
    CreateJerry(&pJerry, "1", 50, pPlanet, "Dimension", 2);
    AddPhysicalCharacteristic(pJerry, "Height", 1.5);
    AddPhysicalCharacteristic(pJerry, "Width", 1.5);
    bool royi = HasPhysicalCharacteristic(pJerry, "Height");

    RemovePhysicalCharacteristic(pJerry, "Height");
    Status status = PrintJerry(pJerry);
    return 0;
}
