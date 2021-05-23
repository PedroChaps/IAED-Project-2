#ifndef IAEDPROJ2_HASH_H
#define IAEDPROJ2_HASH_H

#include "list.h"



typedef struct simple_node {
    Link ptr;
    struct simple_node *next;
} s_Node;

typedef struct simple_node* S_Link;



Link start_list();
S_Link NEW(Link node_ptr);
S_Link insertBegin(S_Link head, Link node_ptr);
S_Link insert_sorted_by_path(Link ptr, S_Link head);
void print_list_basic(S_Link head);
S_Link remove_elem(S_Link head, Link ptr_rm);

Link search_list_by_path(S_Link head, char *path);
Link search_list_by_value(S_Link head, char *value);


S_Link* create_path_table();
S_Link* create_value_table();

S_Link insert_path_table(Link node_ptr);
S_Link insert_value_table(Link node_ptr);

void remove_from_path_table(Link node_ptr);
void remove_from_value_table(Link node_ptr);

Link find_hash_node_by_path(char *path);
Link find_hash_node_by_value(char *value);

Link insert_tables(Link node);
void free_hash_tables();

void free_list(S_Link head);
#define HASH_SIZE 32479





#endif
