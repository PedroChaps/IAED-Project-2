//
// Created by pedro on 18/05/2021.
//

#ifndef IAEDPROJ2_SIMPLE_LIST_H
#define IAEDPROJ2_SIMPLE_LIST_H

#include "list.h"

/* Simple node used on the hash table.
 * Stores a pointer to a complex node (of the main structure).
 */

struct simple_node {
    Link ptr;
    struct simple_node *next;
} s_Node;

typedef struct simple_node* S_Link;

S_Link NEW(Link node_ptr);
S_Link insertBegin(S_Link head, Link node_ptr);
Link search_list_by_path(S_Link head, char *path);

#endif //IAEDPROJ2_SIMPLE_LIST_H
