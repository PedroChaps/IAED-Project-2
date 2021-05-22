#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static S_Link *Path_Table;
static S_Link *Value_Table;
void free_list(S_Link head);

Link start_list(){
    Link Hierarchy_lst;
    /* creates both tables */
    create_path_table();
    create_value_table();

    Hierarchy_lst = create_list();
    insert_tables(Hierarchy_lst);

    return Hierarchy_lst;
}


S_Link* create_path_table(){
    int i;

    /*Alloc a pointer which points to HASH_SIZE pointers */
    Path_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);
    check_OOM(Path_Table);

    /*Resets the hash table entries to only have pointers pointing to NULL */
    for(i = 0; i < HASH_SIZE; i++){
        Path_Table[i] = NULL;
    }
    return Path_Table;
}

S_Link* create_value_table(){

    int i;

    /*Alloc a pointer which points to HASH_SIZE pointers */
    Value_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);
    check_OOM(Value_Table);

    /*Resets the hash table entries to only have pointers pointing to NULL */
    for(i = 0; i < HASH_SIZE; i++){
        Value_Table[i] = NULL;
    }
    return Value_Table;
}

/* Hashes a string. Returns the index where it should be saved */
int hash(char *v, int M){
    int h, a = 31415, b = 27183;
    if(v == NULL)
        return 0;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
        h = (a * h + *v) % M;
    }
    return h;
}


/* Find a path associated to a node pointer in the hash table */
Link find_hash_node_by_path(char *path){
    /* Hashes the path to find the index where it belongs */
    int i;
    Link ptr;
    i = hash(path, HASH_SIZE);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted path is associated to */
    ptr = search_list_by_path(Path_Table[i], path);

    return ptr;
}

/* Find a value associated to a node pointer in the hash table */
Link find_hash_node_by_value(char *value){
    /* Hashes the path to find the index where it belongs */
    int i;
    Link ptr;

    i = hash(value, HASH_SIZE);
    /* Searches on the table's corresponding index for the node pointer that
     * the wanted value is associated to */
    ptr = search_list_by_value(Value_Table[i], value);

    return ptr;
}


/* Insert a node pointer in the hash table, by path. */
void insert_path_table(Link node_ptr){
    /* Hashes the node's path_name */
    int i;

    i = hash(node_ptr->path_name, HASH_SIZE);
    /* Inserts the node pointer on the beginning of the right index */
    Path_Table[i] = insertBegin(Path_Table[i], node_ptr);

}

/* Insert a node pointer in the hash table, by value. */
void insert_value_table(Link node_ptr){

    int i;
    /* It's possible for a value to not be defined.
     * Verifies first if it exists */
    if (node_ptr->value == NULL)
        return;
    /* Hashes the node's value */
    i = hash(node_ptr->value, HASH_SIZE);
    /* Inserts the node pointer on the beginning of the right index */
    Value_Table[i] = insertBegin(Value_Table[i], node_ptr);

}


/* Remove a node pointer in the hash table, by path. */
void remove_from_path_table(Link node_ptr){

    int i;

    i = hash(node_ptr->path_name, HASH_SIZE);
    Path_Table[i] = remove_elem(Path_Table[i], node_ptr);
}

/* Remove a node pointer from the value table. */
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
void free_hash_tables(){
    int i;

    for(i = 0; i < HASH_SIZE; i++){

        if (Path_Table[i] != NULL){
            free_list(Path_Table[i]);
        }

        if (Value_Table[i] != NULL){
            free_list(Value_Table[i]);
        }
    }
    free(Path_Table);
    free(Value_Table);
}

void insert_tables(Link node){
    insert_path_table(node);
    insert_value_table(node);
}

/* --------------------- Simple List -------------------------- */



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
        /*Verifies first element */
    else if (strcmp(get_last_path(ptr->path_name), get_last_path(head->ptr->path_name)) < 0){
        new->next = head;
        head = new;
        return head;
    }
    /*finds the first value in which path_name is lower */
    for (aux = head;
         aux->next != NULL && strcmp(get_last_path(ptr->path_name), get_last_path(aux->next->ptr->path_name)) > 0;
         aux = aux->next);

    new->next = aux->next;
    aux->next = new;

    return head;
}


S_Link NEW(Link node_ptr){
    S_Link x;

    x = (S_Link) malloc(sizeof(s_Node));
    check_OOM(x);

    x->ptr = node_ptr;
    x->next = NULL;

    return x;
}

/* Insert a node pointer on the beginning of a list */
S_Link insertBegin(S_Link head, Link node_ptr)
{

    S_Link x;

    x = NEW(node_ptr);
    x->next = head;
    return x;
}

/* Searches a list for a specified path.
 * Returns the node pointer that points to the path.
 * If it doesn't exist, returns NULL. */
/*
Link search_list_by_path(S_Link head, char *path){

    S_Link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->path_name, path) == 0)
            return t->ptr;
    return NULL;

}
*/
/* Only prints the paths stored on the node pointers of each element of the
 * list */
void print_list_basic(S_Link head){
    /* Verifies if head is NULL */
    if (head == NULL){
        return;
    }
    /*prints the list */
    for(; head != NULL; head = head->next){
        printf("%s\n", get_last_path(head->ptr->path_name));
    }

}

S_Link remove_elem(S_Link head, Link ptr_rm) {
    S_Link t, prev;

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

/* Searches a simple list for a node that has the specified path */
Link search_list_by_path(S_Link head, char *path){

    S_Link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->path_name, path) == 0)
            return t->ptr;
    return NULL;

}

/* Searches a simple list for the oldest node that has the specified value */
Link search_list_by_value(S_Link head, char *value){
    Link ptr = NULL;
    S_Link t;
    int min;

    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->value, value) == 0) {
            /* if first value */
            if (ptr == NULL){
                ptr = t->ptr;
                min = t->ptr->id;
            }
            /* if not the first value (path has been attributed already) */
            else if (t->ptr->id < min) {
                /* If the id is less than min, a candidate is found.
                 * min is updated to the new minimum.*/
                ptr = t->ptr;
                min = t->ptr->id;
            }
        }
    return ptr;

}


/* Extracts the last path name of a complete path
 * Eg: from "/a/b/c" returns "c" */
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

void free_list(S_Link head){

    S_Link ptr;

    if (head == NULL){
        return;
    }

    ptr = head->next;

    /* Frees head*/
    free(head);
    while(ptr != NULL){
        head = ptr;
        ptr = ptr->next;
        free(head);
    }

}