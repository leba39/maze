/*
The maze solver implementation goes in this file.

However, there is a special rule:  you are not allowed to directly access
or modify any of the elements of any struct you create.  In other words,
the following code is against the rules:

struct location *x = create_location(5, 5);
x.row = 6;

Your algorithm must make use only of the functions you have written in
your *.c files.
*/

/*
    MAZE SOLVING PROGRAM. MAIN.
*/

#include "maze.h"
#include "stack.h"
#include "location.h"   //shouldn't be neccessary

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

FILE* open_file(char* filename);
int read_file(FILE* fp, struct location** loc_arr,struct location* loc_start, struct location* loc_end);

int main(int argc, char* argv[]){

    //VARs
    FILE* input_file = NULL;
    char* input_filename;
    bool tried      = false;
    bool end        = false;
    int maze_no_locs;
    struct location* maze_locs;
    struct location maze_start, maze_end, loc_top, loc_next;
    struct maze* maze;    
    struct locationstack* loc_stack;

    //Open file
    do{
        if(argc<2||tried){
            fprintf(stdout,"Enter name of input file:\t");
            fscanf(stdin,"%s",input_filename);
        }else{
             tried =  true;
             input_filename = argv[1];
        }
        input_file = open_file(input_filename);
    }while(!input_file);
    
    //Read file, verify format
    if((maze_no_locs = read_file(input_file,&maze_locs,&maze_start,&maze_end))<0){
        fclose(input_file);
        fprintf(stderr,"Error reading input file. Error code:\t%d\n",maze_no_locs);
        return -1;
    }

    //MAZE SOLVING:

    maze        = maze_create(maze_locs,maze_no_locs,maze_start,maze_end);
    loc_stack   = locationstack_create(maze_get_start(*maze));    
    loc_top     = locationstack_get_top(*loc_stack);           // == maze_start

    while(!locationstack_is_empty(*loc_stack)){
        /*  Priorities: 
         *  Check all neighbors, if it isnt on the stack, go there.
         *  If the location is done and no new valid position is available for pushing it into the stack then pop current top (backtrace). 
         *  If we found the end of maze break and print stack. If the maze has no exit, all locs become DONE and stack become EMPTY.
         *  Print result.
         *  (Save current node.loc.next_dir state with a pop and push) -> could be fixed with stack.h returning location*
         */

        locationstack_pop(loc_stack);

        loc_start(&loc_top);        
        while(!loc_isdone(loc_top)){
            
            struct location* loc_nav = loc_neighbor(&loc_top);
            if(maze_is_valid(*maze,*loc_nav)&&!locationstack_is_on(*loc_stack,*loc_nav)){
                loc_next  = *loc_nav;
                loc_destroy(loc_nav);
                break;    
                
            }        
            loc_destroy(loc_nav);   
        }
        
        if(!loc_isdone(loc_top)){
            locationstack_push(loc_stack,loc_top);
            locationstack_push(loc_stack,loc_next);        
        }

        //debug
        //locationstack_print(*loc_stack);

        loc_top = locationstack_get_top(*loc_stack);
        if(maze_is_end(*maze,loc_top)){
            end = true;
            break;
        }
    }

    if(end){
        fprintf(stdout,"Exit found! Maze completed!\n");
        locationstack_print(*loc_stack);
    }else{
        fprintf(stdout,"This maze has no possible exit!\n");
    }

    //DESTROY
    locationstack_destroy(loc_stack);
    maze_destroy(maze);
    
    return 0;
}

FILE* open_file(char* filename){

    FILE* fp;
    if(!filename)   return NULL;

    fp = fopen(filename,"r");
    if(!fp){
        fprintf(stderr,"Error, couldnt open file. Error num:\t%d\n",errno);
        perror("Description:\t");
    }

    return fp;    
}

int read_file(FILE* fp, struct location** loc_arr,struct location* loc_start, struct location* loc_end){

    if(!fp) return -1;  //no file opened
    puts("File opened! READING...");

    //VARs
    int n_locs, verification;
    char newline;

    //READ
    verification = fscanf(fp,"%d",&n_locs);
    if(verification!=1||n_locs<2)   return -2; //wrong scan or number of valid locations

    *loc_arr = (struct location*)malloc(sizeof(struct location)*n_locs);
    for(int i=0;i<n_locs;i++){
        
        int row,col;
        verification = fscanf(fp,"%d %d",&row,&col);
        if(verification!=2||row<0||col<0)   return -3;   //wrong scan or invalid location
        struct location* new_valid_loc  = loc_create(row,col);
        (*loc_arr)[i]                   = *new_valid_loc;
        loc_destroy(new_valid_loc);
    }

    while(true){
        newline = fgetc(fp);
        if(newline == '\n') break;
    }

    for(int i=0;i<2;i++){   //start and end locations
        int row,col;
        verification = fscanf(fp,"%d %d",&row,&col);
        if(verification!=2||row<0||col<0)   return -3;   //wrong scan or invalid location
        struct location* start_end_loc  = loc_create(row,col);
        if(i==0){
            *loc_start = *start_end_loc;
        }else{
            *loc_end   = *start_end_loc;
        }
        loc_destroy(start_end_loc);
    }

    //VERIFY AND CLOSE
    verification = fscanf(fp,"%d",&verification);
    if((verification == EOF)&&(feof(fp))){
        fclose(fp);
        return n_locs; //GOOD EXIT!
    }else{
        return -4;  //input format incorrect
    }
}
