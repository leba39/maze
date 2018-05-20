#include "stack.h"

/*
Add your implementation of the functions in "stack.h" here.
*/

//LOCATION STACK

struct locationstack* locationstack_create(struct location init_loc){
    
    struct locationstacknode* init_node  = locationstacknode_create(init_loc,NULL);
    struct locationstack* init_stack     = (struct locationstack*)malloc(sizeof(struct locationstack));
    init_stack->top = init_node;
    
    return init_stack;
}

void locationstack_push(struct locationstack *stack, struct location loc){

    assert(stack);
    
    struct locationstacknode* new_node  = locationstacknode_create(loc,stack->top);
    stack->top = new_node;

    return;
}

void locationstack_pop(struct locationstack *stack){

    assert(stack);
    
    //save new top, pop old one and set new top on stack.
    struct locationstacknode* new_top = stack->top->next;
    locationstacknode_destroy(stack->top);
    stack->top = new_top;

    return;
}

const struct location locationstack_get_top(struct locationstack stack){

    if(stack.top)  return stack.top->loc;
}

bool locationstack_is_empty(struct locationstack stack){

    return (stack.top==NULL);
}

bool locationstack_is_on(struct locationstack stack, struct location loc){

    if(!stack.top)  return false;   //assert?

    struct locationstacknode* node_nav = stack.top;
    do{
        if(loc_isequal(loc,node_nav->loc))   return true;
        node_nav = node_nav->next;
    }while(node_nav);
    
    return false; 
}

void locationstack_print(struct locationstack stack){
    //print bottom to top
    if(!stack.top)  return;

    int depth = 0;
    struct locationstacknode* node_nav = stack.top;
    //find depth
    do{
        depth++;
        node_nav = node_nav->next;
    }while(node_nav);
    //print
    for(;depth>0;depth--){
        node_nav = stack.top;
        for(int i=depth-1;i>0;i--){
            node_nav = node_nav->next;
        }        
        fprintf(stdout,"Stack element no. %d:\t",depth);
        loc_print(&(node_nav->loc));
    }

    return;
}

void locationstack_destroy(struct locationstack *stack){
    
    if(locationstack_is_empty(*stack)){
        free(stack);
        stack = NULL;
    }

    return;
}


//LOCATION STACK NODE

struct locationstacknode* locationstacknode_create(const struct location loc, struct locationstacknode *next){
    
    struct locationstacknode* new  = (struct locationstacknode*)malloc(sizeof(struct locationstacknode));
    new->loc    = loc;
    new->next   = next; //puedo hacer un locationstacknode_set_next
    return new;
}

void locationstacknode_destroy(struct locationstacknode *node){

    if(!node)   return; //assert?
   
    node->next = NULL; 
    loc_destroy(&node->loc); 
        //free(node); 
        //careful, this is not neccessary and will cause segfault
        //by double-freeing.
    node = NULL;
    return;
}

const struct location locationstacknode_get_location(struct locationstacknode node){
    return node.loc;
}

struct locationstacknode* locationstacknode_get_next(struct locationstacknode node){
    return node.next;
}

void locationstacknode_set_next(struct locationstacknode *node, struct locationstacknode *delta_next){
    
    if(!node||!delta_next)  return; //assert? delta_next could be NULL in some cases??
    node->next = delta_next;
    return;
}
