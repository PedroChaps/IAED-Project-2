//
// Created by pedro on 17/05/2021.
//

#ifndef IAEDPROJ2_HASH_H
#define IAEDPROJ2_HASH_H


#define HASH_SIZE 7919

#include "list.h"



S_Link* create_hash_table();
void insert_hash_table(Link node_ptr, S_Link *Table, int M);
Link find_hash_value(char* path, S_Link *Table, int M);
void remove_from_hash_table(Link node_ptr, S_Link *Table, int M);








#endif //IAEDPROJ2_HASH_H
