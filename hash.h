#ifndef IAEDPROJ2_HASH_H
#define IAEDPROJ2_HASH_H

#include "list.h"


/* A simple Node is a simpler list which is used on the externally chained Hash
 * Tables defined afterwards. The simple Node is made up of 2 components:
 *      A pointer to a Node;
 *      A pointer to the next simple Node;
*/
typedef struct simple_node {
    Link ptr;
    struct simple_node *next;
} s_Node;

typedef struct simple_node* S_Link;


/* Functions that operate simple Lists / simple Nodes */

S_Link NEW(Link node_ptr);

S_Link insertBegin(S_Link head, Link node_ptr);
S_Link insert_sorted_by_path(Link ptr, S_Link head);

Link search_list_by_path(S_Link head, char *path);
Link search_list_by_value(S_Link head, char *value);

S_Link remove_elem(S_Link head, Link ptr_rm);

void print_list_basic(S_Link head);

/* -------------------------------------------------------------------------- */

/* Functions that operate the Hash Tables.
 * 2 Hash Tables are defined: One that stores pointers to Nodes by the Path
 * Name, from now on called Path Table, and one that stores pointers to Nodes by
 * their value, from now on called Value Table. */

/* They share a common Hash Table Size (the largest 4 Byte prime number): */
#define HASH_SIZE 32479

/* Functions that create and operate Hash Tables */
S_Link* create_path_table();
S_Link* create_value_table();

void insert_path_table(Link node_ptr);
void insert_value_table(Link node_ptr);

void remove_from_path_table(Link node_ptr);
void remove_from_value_table(Link node_ptr);

Link find_hash_node_by_path(char *path);
Link find_hash_node_by_value(char *value);

void insert_tables(Link node);
void free_hash_tables();

void free_list(S_Link head);
Link free_node_down_right(Link node);

/* Function to start the Hierarchy list */
Link start_list();

#endif
