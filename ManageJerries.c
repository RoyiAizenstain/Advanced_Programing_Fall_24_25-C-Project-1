#include <stdio.h>
#include "Defs.h"
#include<string.h>
#include "Jerry.h"
#include <ctype.h>

/*
int main(void) {
    Jerry *pJerry = (Jerry *) 0;
    Origin origin;
    Planet *pPlanet = (Planet *) 0;
    CreatePlanet(&pPlanet, "Earth", 123.10,8392.00,99.20);
    Origin *pOrigin = (Origin *) 0;

    CreateJerry(&pJerry, "23dF21", 50, pPlanet, "C-137", 2);
    AddPhysicalCharacteristic(pJerry, "Height", 166.20);
    AddPhysicalCharacteristic(pJerry, "LimbsNumber", 4.00);
    //AddPhysicalCharacteristic(pJerry, "Weight", 80.00);
    bool royi = HasPhysicalCharacteristic(pJerry, "Height");

    Status status = PrintJerry(pJerry);

    RemovePhysicalCharacteristic(pJerry, "Height");
    //AddPhysicalCharacteristic(pJerry, "Height", 1.5);
    status = PrintJerry(pJerry);

    DestroyJerry(pJerry);
    DestroyPlanet(pPlanet);
    return 0;
}
*/
//Read planet line
static Status ReadPlanetLine(char *line, Planet **pp_planet) {
    if (line == NULL || pp_planet == NULL) {
        return FailRead;
    }
    char name[300];
    strcpy(name, line);
    double x, y, z;
    //read each value from line separated by comma
    char *token = strtok(name, ",");
    x = atof(strtok(NULL, ","));
    y = atof(strtok(NULL, ","));
    z = atof(strtok(NULL, ","));
    //create planet
    CreatePlanet(pp_planet, name, x, y, z);
    return Success;
}

//find planet in planets
static Planet *findPlanet(char *name, Planet **planets, int size) {
    if (name == NULL || *planets == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        if (strcmp(planets[i]->name, name) == 0) {
            return planets[i];
        }
    }
    return NULL;
}

//find jerry in jerries
static Jerry *findJerry(char *id, Jerry **jerries, int size) {
    if (id == NULL || *jerries == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {;
        if (strcmp(jerries[i]->id, id) == 0) {
            return jerries[i];
        }

    }
    return NULL;
}

//Read jerry line
static Status ReadJerry(char *line, Jerry **pp_jerry, Planet **pp_planet, int numberOfPlanets) {
    if (line == NULL || pp_jerry == NULL || pp_planet == NULL) {
        return FailRead;
    }
    char id[300];
    strcpy(id, line);
    //read each value separated by comma
    char *token = strtok(id, ",");
    char *dimension = strtok(NULL, ",");
    char *planetName = strtok(NULL, ",");
    int happiness = atoi(strtok(NULL, ","));
    //find planet
    Planet *planet = findPlanet(planetName, pp_planet, numberOfPlanets);
    //create jerry
    CreateJerry(pp_jerry, id, happiness, planet, dimension, 0);
    return Success;
}

//Read physical characteristics line
static Status ReadPhysicalCharacteristicsLine(char *line, Jerry *p_jerry) {
    if (line == NULL || p_jerry == NULL) {
        return FailRead;
    }
    char temp[300];
    strcpy(temp, line);

    //read each value separated by comma
    char *name = strstr(temp, "\t");
    //skip white spaces
    while (isspace(*name))
        ++name;
    //read each value separated by :
    strtok(temp, ":");
    char *value = strtok(NULL, ":");
    //skip white spaces
    strtok(value, "\r\n");
    //add physical characteristic
    AddPhysicalCharacteristic(p_jerry, name, atof(value));
    return Success;
}

//print manu
static void PrintManu() {
    char choice[300];
    printf("AW JEEZ RICK, what do you want to do now ? \n");
    printf("1 : Print all Jerries \n");
    printf("2 : Print all Planets \n");
    printf("3 : Add physical characteristic to Jerry \n");
    printf("4 : Remove physical characteristic from Jerry \n");
    printf("5 : Print Jerries by a planet \n");
    printf("6 : Print Jerries by a physical characteristic \n");
    printf("7 : Go home \n");
}

static bool ValidInput(char *input) {
    if (strcmp(input, "1") == 0 || strcmp(input, "2") == 0 || strcmp(input, "3") == 0 || strcmp(input, "4") == 0 ||
        strcmp(input, "5") == 0 || strcmp(input, "6") == 0 || strcmp(input, "7") == 0) {
        return True;
    }
    return False;
}

//print all jerries
static void PrintAllJerries(Jerry **jerries, int size) {
    //loop through all jerries
    for (int i = 0; i < size; i++) {
        PrintJerry(jerries[i]);
    }
}

//print all planets
static PrintAllPlanets(Planet **planets, int size) {
    //loop through all planets
    for (int i = 0; i < size; i++) {
        PrintPlanet(planets[i]);
    }
}

//check if jerry has physical characteristic
void to_upper(char * temp) {
    //loop through all characters
    for (int i = 0; temp[i] != '\0'; i++) {
        //if character is lower case
        if (temp[i] >= 'a' && temp[i] <= 'z') {
            temp[i] = temp[i] - 32;
        }
    }
}

static AddPCToJerrr(Jerry **jerries, int size) {
    char id[300];
    //get jerry id
    printf("What is your Jerry's ID ? \n");
    scanf("%s", id);
    //find jerry
    Jerry *jerry = findJerry(id, jerries, size);
    //if jerry not found
    if (jerry == NULL) {
        printf("OH NO! I CAN'T FIND HIM RICK ! \n");
    } else {
        //get physical characteristic name
        printf("What physical characteristic can you add to Jerry - %s ? \n", jerry->id);
        char name[300];
        scanf("%s", name);
        //if physical characteristic already exists
        if (HasPhysicalCharacteristic(jerry, name)) {
            to_upper(name);
            printf("RICK I ALREADY KNOW HIS %s! \n", name);
        }else{
            //add physical characteristic
            printf("What is the value of %s ? \n", name);
            double value;
            scanf("%lf", &value);
            AddPhysicalCharacteristic(jerry, name, value);
        }

    }
}

static RemovePCToJerrr(Jerry **jerries, int size) {
    char id[300];
    //get jerry id
    printf("What is your Jerry's ID ? \n");
    scanf("%s", id);
    //find jerry
    Jerry *jerry = findJerry(id, jerries, size);
    //if jerry not found
    if (jerry == NULL) {
        printf("OH NO! I CAN'T FIND HIM RICK ! \n");
    } else {
        //get physical characteristic name
        printf("What physical characteristic do you want to remove from Jerry - %s ? \n", jerry->id);
        char name[300];
        scanf("%s", name);
        //if physical characteristic already exists
        if (!HasPhysicalCharacteristic(jerry, name)) {
            to_upper(name);
            printf("RICK I DON'T KNOW HIS %s ! \n", name);
        }else{
            //add physical characteristic
            RemovePhysicalCharacteristic(jerry, name);
            PrintJerry(jerry);
        }

    }
}

int main(int argc, char *argv[]) {
    int NumberOfPlanets = atoi(argv[1]);
    int NumberOfJerries = atoi(argv[2]);

    Planet *planets[NumberOfPlanets];
    Jerry *jerries[NumberOfJerries];


    FILE *file = fopen(argv[3], "r");
    char chunk[300];
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(chunk, sizeof(chunk), file)) {
            // Print each line to the standard output.
            if (strcmp("Planets\n", chunk) == 0) {
                for (int i = 0; i < NumberOfPlanets; i++) {
                    fgets(chunk, sizeof(chunk), file);
                    ReadPlanetLine(chunk, &planets[i]);
                }
            }
            fgets(chunk, sizeof(chunk), file);
            if (strcmp("Jerries\n", chunk) == 0) {
                fgets(chunk, sizeof(chunk), file);
                for (int i = 0; i < NumberOfJerries; i++) {
                    ReadJerry(chunk, &jerries[i], planets, NumberOfPlanets);
                    Jerry *p_lastjerry = jerries[i];
                    fgets(chunk, sizeof(chunk), file);
                    while (chunk[0] == '\t') {
                        ReadPhysicalCharacteristicsLine(chunk, p_lastjerry);
                        if (fgets(chunk, sizeof(chunk), file) == NULL) {
                            break;
                        }
                    }
                }
            }
        }

        // Close the file stream once all lines have been
        // read.
        fclose(file);
    } else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
    }

    char id[300];
    while (True) {
        PrintManu();
        char choice[300];
        scanf("%s", choice);
        if (ValidInput(choice)) {
            int todo = atoi(choice);
            switch (todo) {
                case 1:
                    PrintAllJerries(jerries, NumberOfJerries);
                    break;
                case 2:
                    PrintAllPlanets(planets, NumberOfPlanets);
                    break;
                case 3:
                    AddPCToJerrr(jerries, NumberOfJerries);
                    break;
                case 4:
                    RemovePCToJerrr(jerries, NumberOfJerries);
                    break;
            }
        } else {
            printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");
        }
    }

    // Destroy all the planets
    for (int i = 0; i < NumberOfJerries; i++) {
        DestroyJerry(jerries[i]);
    }
    //Destroy all Jerries
    for (int i = 0; i < NumberOfPlanets; i++) {
        DestroyPlanet(planets[i]);
    }

    return 0;
}
