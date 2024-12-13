#include <stdio.h>
#include "Defs.h"
#include<string.h>


int main(void) {
    int *royi;
    ALLOCATE(royi, int, 5);
    printf("%d\n", sizeof(royi));

    REALLOCATE(royi, 1);
    char str[] = "geeksforgeeks is the best";
    //converting the given string into uppercase.
    return 0;
}
