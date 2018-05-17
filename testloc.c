//TESTING LOCATIONS
#include "location.h"

//compile with gcc using:   gcc -g testloc.c location.c -o test

int main(){

    struct location* initial_location = NULL;

    initial_location = loc_create(2,2);
    loc_start(initial_location);

    while(!loc_isdone(*initial_location)){
        struct location* neighbor = loc_neighbor(initial_location);
        loc_print(neighbor);
        loc_destroy(neighbor);
    }
    loc_destroy(initial_location);
    return 0;
}
