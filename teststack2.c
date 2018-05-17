#include "stack.h"

int main(){

    struct locationstack *first = locationstack_create();


    locationstack_print(*first);
    locationstack_pop(first);
    locationstack_print(*first);
    printf("Is empty? %s\n",(locationstack_is_empty(*first)) ? "true":"false");
    
    locationstack_destroy(first);

    return 0;
}
