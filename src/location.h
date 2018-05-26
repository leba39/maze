#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
This file represents the "location" struct.

It also provides several functions which you can use to operate on and
interact with location structs.  If we were programming in OOP in C++
or Java, these would be member functions, but since we are in C they
simply take a pointer to a location struct.

You have access to a function which iterates over the neighbors of a
location.  Two locations are neighbors if and only if their rows are
the same and columns differ by one, or if their columns are the same
and their rows differ by one.  Here's how you can print out all the
neighbors of a location called loc:

loc_start(loc);
while(!loc_isdone(loc))
{
    struct location *neighbor = loc_neighbor(loc);
    loc_print(neighbor);
}

What do these functions do?  loc_start initializes the iteration
capability of a location.  Calling loc_neighbor() on a location that
has not been initialized should fail.  loc_neighbor does three things:
creates a copy of the object passed, modifies it so that it matches the
next location in sequence, advances the iterator state of the initial
object, and finally returns the newly created location.  loc_isdone()
will tell you whether all neighbors of a location have been iterated
over.

The order of neighbor iteration is very important!  You should first
visit the neighbor to the right, then down, then left, then up.  Thus,
loc_neighbor() should never return the same location that was passed
to it (a location is never a neighbor to itself).

A location object keeps track of what iteration it is on with the states
RIGHT, DOWN, LEFT, UP, DONE, which are defined as an enum.

Two locations are equal if and only if their row and column values are
equal regardless of their iteration states.  Thus, you must use
the dedicated function loc_isequal() to compare two locations instead
if directly comparing the structs.  The iteration state of a location
should not be printed in loc_print(), and when a location is read in
from a file, only row and column data is affected.

Construction should initialize data members to reasonable values.
When you are finished with a location object you must call
loc_destroy() on it to deallocate memory.  The values of data members
should not affect the behavior of this function.
*/

struct location
{
    int row, col;
    unsigned int next_direction;
};

enum { RIGHT, DOWN, LEFT, UP, DONE };
struct location* loc_create(int row, int col);
void loc_start(struct location *loc);
struct location* loc_neighbor(struct location *loc);
bool loc_isdone(struct location loc);
bool loc_isequal(struct location loc1, struct location loc2);
void loc_destroy(struct location *loc);
void loc_print(struct location *loc);

#endif
