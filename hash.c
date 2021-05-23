#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition of the two Hash Tables: Path Table and Value table. */
static S_Link *Path_Table;
static S_Link *Value_Table;


/* ----------------------------- Simple List -------------------------------- */



/* Create a new simple Node, given a Node */
S_Link NEW(Link node_ptr){
    S_Link x;

    x = (S_Link) malloc(sizeof(s_Node));
    check_OOM(x);

    x->ptr = node_ptr;
    x->next = NULL;

    return x;
}

/* Insert a node pointer on the beginning of a list */
S_Link insertBegin(S_Link head, Link node_ptr){
    S_Link x;

    /* Creates the node and updates next */
    x = NEW(node_ptr);
    x->next = head;

    return x;
}



/* Extracts the last path name of a complete path
 * Eg: from "/a/b/c" returns "c".
 * Used on the next functions. */
char *get_last_path(char *complete_path){

    char *ptr;
    char *aux;

    ptr = complete_path;

    for(aux = ptr; (*aux) != '\0'; aux++){
        if ((*aux) == '/'){
            ptr = aux;
        }
    }
    return ptr+1;
}

/* Inserts a Node on a simple List alphabetically by Path */
S_Link insert_sorted_by_path(Link ptr, S_Link head){

    S_Link aux;
    S_Link new;

    new = (S_Link) malloc(sizeof(s_Node));
    check_OOM(new);

    new->ptr = ptr;
    new->next = NULL;

    /* Verifies if list is empty */
    if (head == NULL){
        head = new;
        return head;
    }
    /*Verifies first element. The function get_last_path is used in other
     * to only compare the last sub-path (since the initial sub-paths are equal
     * for every element). */
    else if (strcmp(get_last_path(ptr->path_name),
                    get_last_path(head->ptr->path_name)) < 0){
        new->next = head;
        head = new;
        return head;
    }
    /*else finds the first value in which the last sub-path of path_name is
     * alphabetically lower */
    for (aux = head;
         aux->next != NULL && strcmp(get_last_path(ptr->path_name),
                                     get_last_path(aux->next->ptr->path_name)) > 0;
         aux = aux->next);

    new->next = aux->next;
    aux->next = new;

    return head;
}



/* Prints the last sub-path of the paths stored on the node pointers of each
 * element of the list */
void print_list_basic(S_Link head){

    /* Verifies if head is NULL */
    if (head == NULL){
        return;
    }
    /*prints the list's last sub-path */
    for(; head != NULL; head = head->next){
        printf("%s\n", get_last_path(head->ptr->path_name));
    }
}

/* Remove a simple Node from a simple List that has a specified Node */
S_Link remove_elem(S_Link head, Link ptr_rm) {
    S_Link t, prev;
    /* Searches for the Node */
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (t->ptr == ptr_rm) {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;

            free(t);
            break;
        }
    }
    return head;
}

/* Searches a simple List for a node that has the specified path */
Link search_list_by_path(S_Link head, char *path){

    S_Link t;
    /* Searches for the path */
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->path_name, path) == 0)
            return t->ptr;
    return NULL;

}

/* Searches a simple List for the oldest Node that has the specified value */
Link search_list_by_value(S_Link head, char *value){
    Link ptr = NULL;
    S_Link t;
    int oldest;
    /* Two cycles. The purpose of first one is to find the first node that
     * has the same goal value, in order to give oldest a value. */
    for(t = head; t != NULL; t = t->next) {
        if (strcmp(t->ptr->value, value) == 0) {
            ptr = t->ptr;
            oldest = t->ptr->id;
            break;
        }
    }
    /* Now, the cycle continues but verifies first if the id is less than
     * the oldest (means the node is older) and only then compares the
     * string (More efficient). */
    for(; t != NULL; t = t->next) {
        if (t->ptr->id < oldest && strcmp(t->ptr->value, value) == 0){
            ptr = t->ptr;
            oldest = t->ptr->id;
        }
    }
    return ptr;

}


/* Frees a Simple List */
void free_list(S_Link head){

    S_Link ptr;

    if (head == NULL){
        return;
    }
    /* Auxiliary pointer that points to next*/
    ptr = head->next;

    /* Frees head and cycles through every next, freeing the simple Nodes */
    free(head);
    while(ptr != NULL){
        head = ptr;
        ptr = ptr->next;
        free(head);
    }
}



/* ---------------------------- Hash Tables --------------------------------- */

/* Functions the create both tables. */

S_Link* create_path_table(){


    /*Alloc a pointer which points to HASH_SIZE pointers */
    Path_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);
    check_OOM(Path_Table);

    /* Sets the hash table entries to only have pointers pointing to NULL */
    memset(Path_Table, 0, sizeof(S_Link) * HASH_SIZE);

    return Path_Table;
}

S_Link* create_value_table(){

    /*Alloc a pointer which points to HASH_SIZE pointers */
    Value_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);
    check_OOM(Value_Table);

    /* Sets the hash table entries to only have pointers pointing to NULL */
    memset(Value_Table, 0, sizeof(S_Link) * HASH_SIZE);

    return Value_Table;
}




/* Hashes a string. Returns the index where it should be saved on the Hash
 * Tables */
int hash(char *v, int M){
    int h, a = 31415, b = 27183;
    if(v == NULL)
        return 0;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
        h = (a * h + *v) % M;
    }
    return h;
}


/* Finds the Node associated to a path in the Path Table */
Link find_hash_node_by_path(char *path){

    int i;
    Link ptr;
    /* Hashes the path to find the index where it belongs */
    i = hash(path, HASH_SIZE);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted path is associated to */
    ptr = search_list_by_path(Path_Table[i], path);
    /* If ptr is NULL, it means there is no Node with the associated Path */
    return ptr;
}

/* Finds the oldest Node associated to a value in the Value Table */
Link find_hash_node_by_value(char *value){

    int i;
    Link ptr;
    /* Hashes the value to find the index where it belongs */
    i = hash(value, HASH_SIZE);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted value is associated to */
    ptr = search_list_by_value(Value_Table[i], value);
    /* If ptr is NULL, it means there is no Node with the associated Value */
    return ptr;
}




/* Insert a Node pointer in the Path Table. */
void insert_path_table(Link node_ptr){

    int i;
    /* Hashes the node's path_name */
    i = hash(node_ptr->path_name, HASH_SIZE);

    /* Inserts the node pointer on the beginning of the list on the table index */
    Path_Table[i] = insertBegin(Path_Table[i], node_ptr);

}

/* Insert a Node pointer in the Value Table. */
void insert_value_table(Link node_ptr){

    int i;
    /* It's possible for a value to not be defined.
     * Verifies first if it exists */
    if (node_ptr->value == NULL)
        return;

    /* Hashes the node's value */
    i = hash(node_ptr->value, HASH_SIZE);

    /* Inserts the node pointer on the beginning of the list on the table index */
    Value_Table[i] = insertBegin(Value_Table[i], node_ptr);

}



/* Remove a Node pointer in the Hash Table. */
void remove_from_path_table(Link node_ptr){

    int i;

    i = hash(node_ptr->path_name, HASH_SIZE);
    Path_Table[i] = remove_elem(Path_Table[i], node_ptr);
}


/* Remove a Node pointer in the Value Table. */
void remove_from_value_table(Link node_ptr){
    int i;
    /* It's possible for a value to not be defined.
     * Verifies first if it exists */
    if (node_ptr->value == NULL) {
        return;
    }
    i = hash(node_ptr->value, HASH_SIZE);
    Value_Table[i] = remove_elem(Value_Table[i], node_ptr);
}



/* Insert a node in both tables */
void insert_tables(Link node){
    insert_path_table(node);
    insert_value_table(node);
}



/* Frees every entry of the Hash Tables and the Hash Tables */
void free_hash_tables(){
    int i;
    /* Cycles through every entry, freeing the lists on the entries that are
     * not NULL */
    for(i = 0; i < HASH_SIZE; i++){

        if (Path_Table[i] != NULL){
            free_list(Path_Table[i]);
            Path_Table[i] = NULL;
        }

        if (Value_Table[i] != NULL){
            free_list(Value_Table[i]);
            Value_Table[i] = NULL;
        }
    }
    /* Frees the tables */
    free(Path_Table);
    free(Value_Table);
}



/* Frees node, its brothers and every node below it.
 * Defined here because, before fred, the Node entry is also removed from the
 * Hash Tables. */
Link free_node_down_right(Link node){

    if (node == NULL)
        return NULL;
    /* Calls the function recursively to the children and brothers of a node */
    if (node->next_down != NULL)
        node->next_down = free_node_down_right(node->next_down);

    if (node->next_right != NULL)
        node->next_right = free_node_down_right(node->next_right);

    /* Removes the node from the tables and frees everything associated with
     * it */
    remove_from_path_table(node);
    remove_from_value_table(node);
    node = free_node(node);

    return node;

}


/* Starts the hierarchy list.
 * First creates both tables and creates the hierarchy list, inserting it on
 * the tables afterwards. */
Link start_list(){

    Link Hierarchy_lst;

    create_path_table();
    create_value_table();

    Hierarchy_lst = create_list();
    insert_tables(Hierarchy_lst);

    return Hierarchy_lst;
}

