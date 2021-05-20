#ifndef IAEDPROJ2_HASH_H
#define IAEDPROJ2_HASH_H




#include "list.h"




S_Link create_simple_list();
S_Link NEW(Link node_ptr);
S_Link insertBegin(S_Link head, Link node_ptr);
S_Link insert_sorted_by_path(Link ptr, S_Link head);
void print_list_basic(S_Link head);
S_Link remove_elem(S_Link head, Link ptr_rm);




S_Link* create_path_table();
S_Link* create_value_table();

void insert_path_table(Link node_ptr);
void insert_value_table(Link node_ptr);

void remove_from_path_table(Link node_ptr);
void remove_from_value_table(Link node_ptr);

Link find_hash_node_by_path(char *path);
Link find_hash_node_by_value(char *value);

#define HASH_SIZE 7919





#endif
