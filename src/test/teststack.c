//TESTING STACKS

#include "stack.h"

//compile with gcc using: gcc -g teststack.c stack.c location.c -o test

int main(){

    //VARs
    struct location *init_loc,*loc_one_zero,*loc_one_one,*loc_one_two,*loc_two_two;
    struct locationstack* my_first_stack;

    //DEF    

    init_loc     = loc_create(0,0);
    loc_one_zero = loc_create(1,0);
    loc_one_one  = loc_create(1,1);
    loc_one_two  = loc_create(1,2);
    loc_two_two  = loc_create(2,2);

    my_first_stack = locationstack_create(*init_loc);

    //TESTs 

    //PUSH
    locationstack_push(my_first_stack,*loc_one_zero);
    locationstack_push(my_first_stack,*loc_one_one);
    locationstack_push(my_first_stack,*loc_one_two);
    locationstack_push(my_first_stack,*loc_two_two);
    /*  THIS WOULD CREATE A DANGLING POINTER. 
        THE INABILITY TO FREE IT AFTERWARDS MAKES VALGRIND CRY.
        ALTHOUGH IT STILL WORKS OK.

        locationstack_push(my_first_stack, *loc_create(3,3));
    */
    
    //getting rid of created locations.
    loc_destroy(loc_one_zero);
    loc_destroy(loc_one_one);
    loc_destroy(loc_one_two);
    loc_destroy(loc_two_two);
    loc_destroy(init_loc);

    //GET_TOP AND PRINTS
    struct location new_top = locationstack_get_top(*my_first_stack);
    fprintf(stdout,"Top of the stack is ...");
    loc_print(&new_top);

    fprintf(stdout,"Whole stack now looks like this: \n");
    locationstack_print(*my_first_stack);

    //IS_ON
    struct location *loc_three_three = loc_create(3,3);
    fprintf(stdout,"Is there a location three_three on the stack? %s\n"
    ,(locationstack_is_on(*my_first_stack,*loc_three_three)) ? "true" : "false");
    loc_destroy(loc_three_three);
    
    //POP
    locationstack_pop(my_first_stack);
    locationstack_pop(my_first_stack);
    locationstack_pop(my_first_stack);
    locationstack_pop(my_first_stack);

    fprintf(stdout,"Is the stack empty and ready to destroy? %s\n"
            ,(locationstack_is_empty(*my_first_stack)) ? "true" : "false");
    locationstack_destroy(my_first_stack);  //doesnt do anything bc its not empty
    locationstack_print(*my_first_stack);    //only initial loc 0,0 remaining
    locationstack_pop(my_first_stack);
    //another locationstack_pop() would cause the assert() to abort the program

    //DESTROY + ISEMPTY
    fprintf(stdout,"Is the stack empty and ready to destroy? %s\n"
            ,(locationstack_is_empty(*my_first_stack)) ? "true" : "false");

    locationstack_destroy(my_first_stack);  //would only destroy if its already empty.

    return 0;
}
