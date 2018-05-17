#include "location.h"

/*
Add your implementation of the functions in "location.h" here.
*/

struct location* loc_create(int row, int col){

    if(row<0||col<0)    return NULL;

    struct location*  new = (struct location*)malloc(sizeof(struct location));
    new->row = row;
    new->col = col;
    //initialized but not started. any random value will do
    new->next_direction = 100;  

    return new;
}

void loc_start(struct location *loc){
    
    if(!loc)    return;
    loc->next_direction = RIGHT;
}

struct location* loc_neighbor(struct location *loc){

    if(!loc||loc->next_direction==100)  return NULL;
    //creates copy of object passed
    struct location*  copy = (struct location*)malloc(sizeof(struct location));
    copy->row = loc->row;
    copy->col = loc->col;
    copy->next_direction = loc->next_direction;
    //modify it so it matches next location in sequence
    switch(loc->next_direction){
        //make sure row and col dont go out of bounds? do we do it from another .c?
        case RIGHT:
            copy->col++;
            break;
        case DOWN:
            copy->row++;
            break;
        case LEFT:
            copy->col--;    
            break;
        case UP:
            copy->row--;
            break;
        default:
            //catches DONE and malfunctioning or uninitialized states. do nothing.
            break;
    }
    //advances iterator state of initial object, returns newly created location
    loc->next_direction++;  //enums hold number values beneath them.
    return copy;
}


bool loc_isdone(struct location loc){    
    
    return (loc.next_direction==DONE);
}

bool loc_isequal(struct location loc1, struct location loc2){
    
    return ((loc1.row==loc2.row)&&(loc1.col==loc2.col));
}

void loc_destroy(struct location *loc){
    
    if(!loc)    return;
    free(loc);
    loc = NULL;
}

void loc_print(struct location *loc){
    //function added for testing purposes by leba.
    if(!loc)    return;
    fprintf(stdout,"Fila: %d\tColumna: %d\tEstado: %d\n",loc->row,loc->col,loc->next_direction);
}
