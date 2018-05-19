#include "maze.h"

/*
Add your implementation of the functions in "maze.h" here.
*/

struct maze* maze_create(struct location *init_valid_locations,
                        int valid_location_count,
                        struct location init_location_start,
                        struct location init_location_end)
{

    if(!init_valid_locations||valid_location_count<1)  return NULL;

    //ALLOC
    struct maze* new_maze = (struct maze*)malloc(sizeof(struct maze));

    new_maze->valid_locations       = init_valid_locations;
    new_maze->valid_location_count  = valid_location_count;
    new_maze->location_start        = init_location_start;
    new_maze->location_end          = init_location_end;

    return new_maze;
}

void maze_destroy(struct maze *maze){
    
    if(!maze||!maze->valid_locations||maze->valid_location_count<1)   return;  //eval left to right, shouldnt be a problem.

    free(maze->valid_locations);
    maze->valid_locations = NULL;
    free(maze);
    maze = NULL;

    //free locations and afterwards the maze itself
    /*  SEF_FAULT. How can we follow maze.h instructions of destroying 
        every location on the maze on this function then?

        for(int i=0;i<(maze->valid_location_count);i++){
            loc_destroy((maze->valid_locations)+i);
        }
    */

    return;
}

struct location maze_get_start(struct maze maze){
    
    return maze.location_start;
}

bool maze_is_valid(struct maze maze, struct location loc){

    if(!maze.valid_locations||maze.valid_location_count<1)  return false;

    for(int i=0;i<(maze.valid_location_count);i++){
        if(loc_isequal((maze.valid_locations[i]),loc))   return true;
    }

    return false;
}

bool maze_is_end(struct maze maze, struct location loc){
    
    return loc_isequal(maze.location_end,loc);
}
