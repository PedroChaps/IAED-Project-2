#include "hash.h"


S_Link* create_hash_table(){
    /*Alloc a pointer which points to HASH_SIZE pointers */
    S_Link* Table;
    Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);

    int i;
    /*Resets the hash table entries to only have pointers pointing to NULL */
    for(i = 0; i < HASH_SIZE; i++){
        Table[i] = NULL;
    }
    return Table;
}

/* Hashes a string. Returns the index where it should be saved */
int hash(char *v, int M){
    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
        h = (a * h + *v) % M;
    }
    return h;
}
/* Insert a node pointer in the hash table. */
void insert_hash_table(Link node_ptr, S_Link *Table, int M){
    /* Hashes the node's path_name */
    int i = hash(node_ptr->path_name, M);
    /* Inserts the node pointer on the beginning of the right index */
    Table[i] = insertBegin(Table[i], node_ptr);

}

/* Find a value associated to a node pointer in the hash table */
Link find_hash_value(char* path, S_Link *Table, int M){
    /* Hashes the path to find the index where it belongs */
    int i = hash(path, M);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted path is associated to */
    Link ptr = search_list_by_path(Table[i], path);

    return ptr;
}