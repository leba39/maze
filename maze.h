#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdbool.h>
#include "location.h"   //already has stdlib

/*
This file represents the "maze" struct.

A maze object consists of a starting location, an ending location, and a list
of valid locations.  It does not contain any functions which might help you
solve the maze.

The list of valid locations should be stored as an array, and its length
kept in the variable valid_location_count.

The function maze_destroy() should free any memory being used by invoking
location_destroy() on each valid location in the list.

maze_get_start() can be used to retrieve the starting location for the maze.

maze_is_end() can be used to check if a given location matches the end
location for the maze.

maze_is_valid() tells you if a given location exists in the list of valid
locations.

location_start and location_end are the starting and ending locations of
the maze, respectively.
*/

struct maze
{
    struct location *valid_locations;
    int valid_location_count;
    struct location location_start, location_end;
};

struct maze* maze_create(struct location *init_valid_locations,
                        int valid_location_count,
                        struct location init_location_start,
                        struct location init_location_end);
void maze_destroy(struct maze *maze);
struct location maze_get_start(struct maze maze);
bool maze_is_valid(struct maze maze, struct location loc);
bool maze_is_end(struct maze maze, struct location loc);

#endif
