#include "stack.h"

int main(){


    struct location* init_loc = loc_create(0,0);
    struct locationstack *first = locationstack_create(*init_loc);
    loc_destroy(init_loc);


    locationstack_print(*first);
    locationstack_pop(first);
    locationstack_print(*first);
    printf("Is empty? %s\n",(locationstack_is_empty(*first)) ? "true":"false");
    
    locationstack_destroy(first);

    return 0;
}
