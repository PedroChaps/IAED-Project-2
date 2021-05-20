#include "main_functions.h"


void create_paths_to_path(char *path, char *val, S_Link *Table, int M);
Link find_parent_path(Link node, S_Link *Table, int M);
void free_node_down_right(Link node, S_Link *Table, int M);
void delete_all( S_Link *Table, int M);

/* Prints all the commands available */
void help(){
    printf("%s: %s\n", COMMAND1, COMMAND1_I);
    printf("%s: %s\n", COMMAND2, COMMAND2_I);
    printf("%s: %s\n", COMMAND3, COMMAND3_I);
    printf("%s: %s\n", COMMAND4, COMMAND4_I);
    printf("%s: %s\n", COMMAND5, COMMAND5_I);
    printf("%s: %s\n", COMMAND6, COMMAND6_I);
    printf("%s: %s\n", COMMAND7, COMMAND7_I);
    printf("%s: %s\n", COMMAND8, COMMAND8_I);

}

void quit(S_Link *Table, int M){
    delete_all(Table, M);
    exit(EXIT_SUCCESS);
}


/* Sets a value to a specified path */
void set(char *path, char *val, S_Link *Table, int M){


    /*Verifies first if the path exists */
    /*If it does, it's easy. Only alters the value */
    Link ptr = find_hash_value(path, Table, M);

    if (ptr != NULL){
        /* Initializes value */
        ptr->value = (char *) malloc(sizeof(char) * strlen(val));
        verify_memory(ptr->value);
        strcpy(ptr->value, val);
        return;
    }

    /*Otherwise, all the paths leading to path that are not created must be
     * created first.
     * Eg. If the objective is to "set /a/b/c/d hi" but / and /a are the only
     * paths that exist, /a/b, /a/b/c and /a/b/c/d must be created first,
     * without any value associated, and only then the value is associated to
     * /a/b/c/d */

    /* Creates all the missing paths */
    create_paths_to_path(path, val, Table, M);

    /* sets the value to the path that is now created */
    set(path, val, Table, M);

}


/* Prints all the paths and it's values */
void print_all_hierarchy(Link head){

    if (head == NULL){
        return;
    }
    /*WIP test with other downs and rights (currently I cant set new values besides
     * forcing a new_node). */


    if (head->value != NULL){
        printf("%s %s\n", head->path_name, head->value);
    }
    /* The order of printing is down (deepness comes first) and then right
     * (since the insertion order is preserved when going right). */
    print_all_hierarchy(head->next_down);
    print_all_hierarchy(head->next_right);
    /* Only prints if the path has a value */
}

/* Prints all the paths and it's values */
void WIP_print_all_hierarchy_including_no_values(Link head){

    if (head == NULL){
        return;
    }
    /*WIP test with other downs and rights (currently I cant set new values besides
     * forcing a new_node). */


    if (head->value != NULL){
        printf("%s %s\n", head->path_name, head->value);
    }

    else{
        printf("%s ~NULL~\n", head->path_name);
    }
    /* The order of printing is down (deepness comes first) and then right
     * (since the insertion order is preserved when going right). */
    WIP_print_all_hierarchy_including_no_values(head->next_down);
    WIP_print_all_hierarchy_including_no_values(head->next_right);
    /* Only prints if the path has a value */
}

/* Finds what value a specified path has */
void find(char *path, S_Link *Table, int M){

    /* finds the path on the hash table.
     * if the path is not found, a NULL pointer is returned.
     * if the path is found but it has no value, it's value is NULL */

    Link ptr = find_hash_value(path, Table, M);

    if (ptr == NULL){
        printf(ERROR1);
        return;
    }

    else if (ptr->value == NULL){
        printf(ERROR2);
        return;
    }

    else{
        printf("%s\n", ptr->value);
        return;
    }
}



/* Lists all the next paths (children) of path */
void list(char *path, S_Link *Table, int M){
    /* Var path is the parent. The objective is to list all children ordered
     * alphabetically.
     * A parallel simple list is created, that stores sorted pointers to the
     * corresponding nodes. Then, prints the list.*/

    Link aux;
    /* Verifies first if the path exists and if it has at least one child.  */
    Link ptr = find_hash_value(path, Table, M);
    if (ptr == NULL){
        printf(ERROR1);
    }
    else if (ptr->next_down == NULL){
        return;
    }
    /* Since the path exists and has at least one child, all of it's children
     * will be compared and inserted sorted on a new auxiliary simple list */

    S_Link temp_lst = NULL;

    for (aux = ptr->next_down; aux != NULL; aux=aux->next_right){
        temp_lst = insert_sorted(aux, temp_lst);
    }

    print_list_basic(temp_lst);

}

/* Deletes a path and all of it's sequential right and down nodes */
void delete(char *path, S_Link *Table, int M){

    /* if path has no arguments, deletes Root */
    if (strcmp("\0", path) == 0){
        delete("/", Table, M);
        return;
    }

    /*Finds the node associated with path and it's parent (in order to update
     * node's previous node's next). */
    Link node = find_hash_value(path, Table, M);
    if (node == NULL){
        printf("%s", ERROR1);
        return;
    }
    Link aux = find_parent_path(node, Table, M);


    /* Finds the node on the parent->next_down and removes it from the list.
     * If it's root, it's not necessary because everything will be removed on
     * the next function. */
    if (strcmp("/", path) != 0) {
        aux->next_down = remove_node_right(aux->next_down, node);

    /* Frees the node and all of his children and grandchildren and removes them
     * from the hash table.
     * First unlinks with his brothers */
    node->next_right = NULL;
    free_node_down_right(node, Table, M);
    node = NULL;
    }
    /* if the path to be deleted is root, just has to free every node to the
     * right and down of the first child */
    else{
        free_node_down_right(node->next_down, Table, M);
        /* Sets the freed node to NULL to have control */
        node->next_down = NULL;
    }
}

/* Deletes all the paths */
void delete_all( S_Link *Table, int M){
    delete("/", Table, M);
}




/* -------------------------- AUX Functions ----------------------------------*/



/* Extracts the last path name of a complete path
 * Eg: from "/a/b/c" returns "c" */
char *get_last_path(char *complete_path){

    char *ptr = complete_path;
    char *aux;

    for(aux = ptr; (*aux) != '\0'; aux++){
        if ((*aux) == '/'){
            ptr = aux;
        }
    }
    return ptr+1;
}

/* Creates all the missing paths that lead to a path */
void create_paths_to_path(char *full_path, char *val, S_Link *Table, int M){
    int state = NOT_FOUND;
    int cont = 0;
    unsigned long int size;
    Link aux, aux2;

    size = strlen(full_path);
    /* Pointer that points to the last character of full_path */
    char *ptr = &full_path[size-1];
    /* Changes all the '/' to '\0', tracking how many were changed, until an existing
     * path is found.
     * Eg. /a/b/c/d/e -> /a/b/c/d\0e -> /a/b/c\0d\0e -> ... */

    /* Stops when an existing directory is found OR the ptr matches full_path,
     * a.k.a. ptr reached root and didn't find any previously created directory*/
    while(state == NOT_FOUND && ptr != full_path){
        /* Finds the last '/' and changes it to '\0' */
        for(; ptr != full_path && *ptr != '/'; ptr--);
        /* ptr now points to '/'. Changes it to '\0' and increments counter */
        if (ptr != full_path) {
            *ptr = '\0';
            cont++;
            /* Checks if the reduced path exists. If not, the cycle continues */
            aux = find_hash_value(full_path, Table, M);
            if (aux != NULL) {
                state = FOUND;
            }
        }
    }


    /* Verifies, if the stop case was '/', if the first element after root
     * is already created. If not, creates it. */
    if (ptr == full_path){
        aux = find_hash_value(full_path, Table, M);
        if (aux == NULL){
            aux2 = find_hash_value("/", Table, M);
            new_node(full_path, NULL, aux2, Table);
        }
    }

    /* The cycle ends when an already created directory is found (on last case,
     * "/"). Now, all the missing directories must be created.
     * To do that, replenishes all the '\0' to '/', creating every path on each
     * step, until the number of '/' inserted is equal to the number of
     * '\0' switched. */
    ptr = full_path;
    while (cont != 0){
        /*Finds the pointer to the full path, which is guaranteed to exist */
        aux = find_hash_value(full_path, Table, M);
        /* Reverts '\0' and discounts 1 on count */
        for(; *ptr != '\0'; ptr++);
        *ptr = '/'; cont--;
        /* Creates the new path, without value */
        new_node(full_path, NULL, aux, Table);
    }
}

/* Given a path, finds the previous path.
 * If path /a/b/c exists, it's previous path is /a/b;
 * If path /a/b/c and /a/b/d exist, /a/b/d's previous path is /a/b/c;
 * */
Link find_parent_path(Link node, S_Link *Table, int M){
    /* use an auxiliary pointer to find the last '/' and switch it to
     * '\0' temporarily. */

    unsigned long long int size = strlen(node->path_name);
    char *ptr = &node->path_name[size-1];
    Link aux;

    /* Finds the last '/' and changes it to '\0' */
    for(; ptr != node->path_name && *ptr != '/' ; ptr--);

    /*if it stopped on root, the parent is root. Doesn't changes it to '\0' */
    if (ptr == node->path_name){
        aux = find_hash_value("/", Table, M);
    }
    else{
        /* ptr now points to '/'. Changes it to '\0 */
        *ptr = '\0';
        /* aux points to the parent */
        aux = find_hash_value(node->path_name, Table, M);
        /* revert the string */
        *ptr = '/';
    }

    return aux;

}

/* Frees node, its brothers and every node below it */
void free_node_down_right(Link node, S_Link *Table, int M){

    if (node == NULL)
        return;

    if (node->next_down != NULL)
        free_node_down_right(node->next_down, Table, M);

    if (node->next_right != NULL)
        free_node_down_right(node->next_right, Table, M);

    if (strcmp("/", node->path_name) != 0) {
        remove_from_hash_table(node, Table, M);
        node = free_node(node);
    }

}


