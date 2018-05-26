//TESTING MAZE
#include "maze.h"
#include <stdio.h>

//Compile with gcc using: gcc -g testmaze.c maze.c location.c -o testmaze
int main(){

    //VARs
    struct location*    location_array;
    struct location     loc_start,loc_end,loc_test;
    struct maze*        test_maze;
    int number_loc = 5;
    
    //DEF 
    loc_start.row = 0;
    loc_start.col = 0;
    loc_start.next_direction = 100;
    
    loc_end.row = 6;
    loc_end.col = 6;
    loc_end.next_direction = 100;

    loc_test.row = 8;
    loc_test.col = -1;
    loc_test.next_direction = 22;

    location_array = (struct location*)malloc(sizeof(struct location)*number_loc);
    for(int i=0;i<number_loc;i++){
        struct location* new_loc_node = loc_create(i+1,i+1);
        location_array[i] = *new_loc_node;
        loc_destroy(new_loc_node);
        
        /*  SEG_FAULT on maze_destroy()
            location_array[i] = *loc_create(i+1,i+1);
        */
    }
    //TESTs
    test_maze = maze_create(location_array,number_loc,loc_start,loc_end);
    
        //GET_START, IS_END and IS_VALID
    printf("Start of the maze is...\t");
    struct location start = maze_get_start(*test_maze);
    loc_print(&start);
    printf("Is location 6,6 the end of this maze? %s\n"
            ,(maze_is_end(*test_maze,loc_end)) ? "true":"false");
    printf("Is location 0,0 the end of this maze? %s\n"
            ,(maze_is_end(*test_maze,loc_start)) ? "true":"false");

    loc_print(&loc_test);
    printf("Is this location of the maze? %s\n",
            (maze_is_valid(*test_maze,loc_test)) ? "true" : "false");

    //DESTROY
    maze_destroy(test_maze);

    return 0;
}
