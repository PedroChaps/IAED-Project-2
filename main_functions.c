#include "main_functions.h"


void create_paths_to_path(char *path, char *val, S_Link *Table, int M);

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



/* Sets a value to a specified path */
void set(char *path, char *val, S_Link *Table, int M){


    /*Verifies first if the path exists */
    /*If it does, it's easy. Only alters the value */
    Link ptr = find_hash_value(path, Table, M);

    if (ptr != NULL){
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
        for(; *ptr != '/'; ptr--);
        /* ptr now points to '/'. Changes it to '\0' and increments counter */
        *ptr = '\0'; cont++;
        /* Checks if the reduced path exists. If not, the cycle continues */
        aux = find_hash_value(full_path, Table, M);
        if (aux != NULL){
            state = FOUND;
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