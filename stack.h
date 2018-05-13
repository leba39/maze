#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdbool.h>
#include "location.h"

//predeclaration
struct locationstacknode;

/*
This file represents two data structures:  a "locationstack" and "locationstacknode".

The struct(s) in question implements a simple stack of location objects. There
is no templating functionality; only location objects are allowed.  It can
grow and shrink dynamically as necessary.

The functions stack_push(), stack_pop(), and stack_get_top() provide
standard stack functionality.  **NOTE** that in the event of an unsatisfied
precondition when calling these functions, the program should crash using
assert() from <assert.h>!!  stack_is_empty() checks if the stack is empty,
and stack_is_on() tells you if the given location is on the stack.

The stack should be implemented with a linked list, however the head of
the list should represent the top of the stack (i.e., the side you insert
and remove from).  However, stack_print() should print the stack from
bottom to top.  This will require a tricky solution, think carefully.
*/

struct locationstack 
{
    struct locationstacknode *top;
};

void locationstack_push(struct locationstack *stack, struct location loc);
void locationstack_pop(struct locationstack *stack);
const struct location locationstack_get_top(struct locationstack stack);
bool locationstack_is_empty(struct locationstack stack);
bool locationstack_is_on(struct locationstack stack, struct location loc);
void locationstack_print(struct locationstack stack);
void locationstack_destroy(struct locationstack *stack);

/*
This struct represents a single node on a locationstack.  The next pointer
points to the node below it on the stack (or NULL, if the node is on the
bottom of the stack).

You must use locationstacknode_create() and locationstacknode_destroy()
to create and destroy instances of the struct, including in implementations
of locationstack-related functions.

Getter/setter functions are self-explanatory.
*/

struct locationstacknode
{
    struct location loc;
    struct locationstacknode *next;
};

struct locationstacknode* locationstacknode_create(const struct location loc, struct locationstacknode *next);
void locationstacknode_destroy(struct locationstacknode *node);
const struct location locationstacknode_get_location(struct locationstacknode node);
struct locationstacknode* locationstacknode_get_next(struct locationstacknode node) ;
void locationstacknode_set_next(struct locationstacknode *node, struct locationstacknode *delta_next);

#endif
