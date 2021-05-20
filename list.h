
#ifndef IAEDPROJ2_LIST_H
#define IAEDPROJ2_LIST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* A node is made up of 4 components:
 *      The path's name;
 *      It's value;
 *      A pointer to the next node below (next deepness);
 *      A pointer to the next node on it's right.
*/



struct node {
    char *path_name;
    char *value;
    struct node *next_down;
    struct node *next_right;
    int id;
} Node;

typedef struct node* Link;



struct simple_node {
    Link ptr;
    struct simple_node *next;
} s_Node;

typedef struct simple_node* S_Link;

Link create_list();

char *get_last_path(char *complete_path);

Link list_insert_right_end(Link head, Link x);
void print_list(Link head);
void verify_memory(void *ptr);
Link new_node(char *path, char *val, Link parent);
Link search_list_by_path(S_Link head, char *path);
Link search_list_by_value(S_Link head, char *value);
Link remove_node_right(Link head, Link node_rm);
Link free_node(Link node);





#endif
