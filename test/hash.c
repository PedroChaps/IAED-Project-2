#include "hash.h"


static S_Link *Path_Table;
static S_Link *Value_Table;



S_Link* create_path_table(){


    /*Alloc a pointer which points to HASH_SIZE pointers */
    Path_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);

    int i;
    /*Resets the hash table entries to only have pointers pointing to NULL */
    for(i = 0; i < HASH_SIZE; i++){
        Path_Table[i] = NULL;
    }
    return Path_Table;
}

S_Link* create_value_table(){


    /*Alloc a pointer which points to HASH_SIZE pointers */
    Value_Table = (S_Link *) malloc(sizeof(S_Link) * HASH_SIZE);

    int i;
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
    int i = hash(path, HASH_SIZE);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted path is associated to */
    Link ptr = search_list_by_path(Path_Table[i], path);

    return ptr;
}

/* Find a value associated to a node pointer in the hash table */
Link find_hash_node_by_value(char *value){
    /* Hashes the path to find the index where it belongs */
    int i = hash(value, HASH_SIZE);

    /* Searches on the table's corresponding index for the node pointer that
     * the wanted value is associated to */
    Link ptr = search_list_by_value(Value_Table[i], value);

    return ptr;
}


/* Insert a node pointer in the hash table, by path. */
void insert_path_table(Link node_ptr){
    /* Hashes the node's path_name */
    int i = hash(node_ptr->path_name, HASH_SIZE);
    /* Inserts the node pointer on the beginning of the right index */
    Path_Table[i] = insertBegin(Path_Table[i], node_ptr);

}

/* Insert a node pointer in the hash table, by value. */
void insert_value_table(Link node_ptr){
    /* Hashes the node's path_name */
    int i = hash(node_ptr->value, HASH_SIZE);
    /* Inserts the node pointer on the beginning of the right index */
    Value_Table[i] = insertBegin(Value_Table[i], node_ptr);

}


/* Remove a node pointer in the hash table, by path. */
void remove_from_path_table(Link node_ptr){

    int i = hash(node_ptr->path_name, HASH_SIZE);
    Path_Table[i] = remove_elem(Path_Table[i], node_ptr);
}

/* Remove a node pointer in the hash table, by value. */
void remove_from_value_table(Link node_ptr){

    int i = hash(node_ptr->value, HASH_SIZE);
    Value_Table[i] = remove_elem(Value_Table[i], node_ptr);
}

/* --------------------- Simple List -------------------------- */

/* This type of list is only used on Hash. It's meant to be a simpler list,
 * which only has a pointer to the next node and a pointer to a Complex list
 * pointer. */
S_Link create_simple_list(){

    S_Link head = (S_Link) malloc(sizeof(s_Node));
    verify_memory(head);

    head->next = NULL;
    head->ptr = NULL;

    return head;
}

S_Link insert_sorted_by_path(Link ptr, S_Link head){

    S_Link aux;
    S_Link new = (S_Link) malloc(sizeof(s_Node));
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


S_Link NEW(Link node_ptr)
{
    S_Link x = (S_Link) malloc(sizeof(s_Node));
    x->ptr = node_ptr;
    x->next = NULL;

    return x;
}

/* Insert a node pointer on the beginning of a list */
S_Link insertBegin(S_Link head, Link node_ptr)
{

    S_Link x = NEW(node_ptr);
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