//
// Created by pedro on 17/05/2021.
//

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
} Node;

typedef struct node* Link;



struct simple_node {
    Link ptr;
    struct simple_node *next;
} s_Node;

typedef struct simple_node* S_Link;



Link create_list();
Link list_insert_right_end(Link head, Link x);
void print_list(Link head);
void verify_memory(void *ptr);
Link new_node(char *path, char *val, Link parent, S_Link* table);
Link search_list_by_path(S_Link head, char *path);


S_Link create_simple_list();
S_Link NEW(Link node_ptr);
S_Link insertBegin(S_Link head, Link node_ptr);
S_Link insert_sorted(Link ptr, S_Link head);
void print_list_basic(S_Link head);



#include "hash.h"


#endif //IAEDPROJ2_LIST_H
