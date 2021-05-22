#include "main_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_paths_to_path(char *path);
Link find_parent_path(Link node);
void free_node_down_right(Link node);


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

void quit(Link Hierarchy_list){
    delete("/");
    free(Hierarchy_list->path_name);
    free(Hierarchy_list);
    free_hash_tables();
    exit(EXIT_SUCCESS);
}


/* Sets a value to a specified path */
void set(char *path, char *val){


    /*Verifies first if the path exists */
    /*If it does, only alters it's value */
    Link ptr;

    if (strcmp("", path) == 0 || path == NULL){
        return;
    }

    ptr = find_hash_node_by_path(path);

    if (ptr != NULL){
        /* Removes old entry from the value hash table, verifying first if
         * it exists */
        if (ptr->value != NULL)
            remove_from_value_table(ptr);

        /* Frees previous value and initializes a new value */
        free(ptr->value);
        ptr->value = (char *) malloc(sizeof(char) * strlen(val));
        check_OOM(ptr->value);

        strcpy(ptr->value, val);

        /* Updates pointer value on hash table */
        insert_value_table(ptr);
        return;
    }

    /*Otherwise, all the paths leading to path that are not created must be
     * created first.
     * Eg. If the objective is to "set /a/b/c/d hi" but / and /a are the only
     * paths that exist, /a/b, /a/b/c and /a/b/c/d must be created first,
     * without any value associated, and only then the value is associated to
     * /a/b/c/d */

    /* Creates all the missing paths */
    create_paths_to_path(path);

    /* calls set again to set the value to the path that is now created */
    set(path, val);

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
void find(char *path){

    /* finds the path on the hash table.
     * if the path is not found, a NULL pointer is returned.
     * if the path is found but it has no value, it's value is NULL */

    Link ptr;
    ptr = find_hash_node_by_path(path);

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
void list(char *path){
    /* Var path is the parent. The objective is to list all children ordered
     * alphabetically.
     * A parallel simple list is created, that stores sorted pointers to the
     * corresponding nodes. Then, prints the list.*/
    Link ptr;
    Link aux;
    S_Link temp_lst;

    ptr = find_hash_node_by_path(path);
    temp_lst = NULL;

    /* If path has no string, list was called without arguments, so lists root */
    if (strcmp("", path) == 0 || path == NULL) {
        list("/");
        return;
    }

    /* Verifies first if the path exists OR if it has at least one child. */

    if (ptr == NULL){
        printf(ERROR1);
        return;
    }
    else if (ptr->next_down == NULL){
        return;
    }

    /* Since the path exists and has at least one child, all of it's children
     * will be compared and inserted sorted on a new auxiliary simple list */
    for (aux = ptr->next_down; aux != NULL; aux=aux->next_right){
        temp_lst = insert_sorted_by_path(aux, temp_lst);
    }

    print_list_basic(temp_lst);

}


/* Searches for the oldest path that has a certain value */
void search(char *value){

    Link ptr;

    ptr = find_hash_node_by_value(value);

    /* if pointer is NULL, it means no path was found */
    if (ptr == NULL){
        printf(ERROR1);
        return;
    }
    /* prints the path name */
    printf("%s\n", ptr->path_name);

}



/* Deletes a path and all of it's sequential right and down nodes */
void delete(char *path){

    Link node;
    Link parent;

    /* if path is empty, it means a general delete, deletes
     * everything below Root */
    if (strcmp("\0", path) == 0 || path == NULL){
        delete("/");
        return;
    }

    /*Finds the node associated with path and it's parent (in order to update
     * node's previous node's next). */
    node = find_hash_node_by_path(path);

    if (node == NULL){
        printf("%s", ERROR1);
        return;
    }

    parent = find_parent_path(node);
    if (parent == NULL || parent->next_down == NULL){
        return;
    }

    /* If not root, finds the node on the parent->next_down and removes it from
     * the list */
    if (strcmp("/", path) != 0) {

        parent->next_down = remove_node_right(parent->next_down, node);

        /* Frees the node and all of his children and grandchildren.
         * First unlinks with his brothers */
        node->next_right = NULL;
        free_node_down_right(node);

        /* Sets the freed node to NULL to have control */
        node = NULL;
    }

    /* if the path to be deleted is Root, just has to free every node to the
     * right and down of the first child */
    else {
        free_node_down_right(node->next_down);
        /* Sets the freed node to NULL to have control */
        node->next_down = NULL;
    }
}



/* -------------------------- AUX Functions ----------------------------------*/

/*     size = 7             /a\0b\0ca        */

/* Creates all the missing paths that lead to a path */
void create_paths_to_path(char *full_path){
    int state = NOT_FOUND;
    unsigned int cont = 0;
    unsigned int size;
    Link aux, aux2, new;
    char *ptr;

    size = strlen(full_path);

    /* Pointer that points to the last character of full_path */
    ptr = &full_path[size-1];

    /* Changes all the '/' to '\0', tracking how many were changed, until an
     * existing path is found.
     * Eg. /a/b/c/d/e -> /a/b/c/d\0e -> /a/b/c\0d\0e -> ... */

    /* Stops when an existing directory is found OR the ptr matches full_path
     * (that means ptr reached root and didn't find any previously
     * created directory) */
    while(state == NOT_FOUND && ptr != full_path){
        /* Finds the last '/' and changes it to '\0' */
        for(; ptr != full_path && *ptr != '/'; ptr--);
        /* ptr now points to '/'. Changes it to '\0' and increments counter */
        if (ptr != full_path) {
            *ptr = '\0';
            cont++;
            /* Checks if the reduced path exists. If not, the cycle continues */
            aux = find_hash_node_by_path(full_path);
            if (aux != NULL) {
                state = FOUND;
            }
        }
    }


    /* If the stop case was '/', verifies if the first element after root
     * is already created. If not, creates it. */
    if (ptr == full_path){
        aux = find_hash_node_by_path(full_path);
        if (aux == NULL){
            /* If the first path possible doesn't exist then creates it
             * with the parent being Root */
            aux2 = find_hash_node_by_path("/");
            new = new_node(full_path, NULL, aux2);
            insert_tables(new);
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
        aux = find_hash_node_by_path(full_path);
        /* Reverts '\0' and discounts 1 on count */
        for(; *ptr != '\0'; ptr++);
        *ptr = '/'; cont--;
        /* Creates the new path, without value */
        new = new_node(full_path, NULL, aux);
        insert_tables(new);
    }
}

/* Given a path, finds it's parent path.
 * If path /a/b/c exists, it's parent path is /a/b;
 * If path /a/b/c and /a/b/d exist, /a/b/d's parent path is still /a/b;
 * */
Link find_parent_path(Link node){
    /* use an auxiliary pointer to find the last '/' and switch it to
     * '\0' temporarily. */

    unsigned int size;
    char *ptr;
    Link aux;

    if (node == NULL){
        return NULL;
    }

    size = strlen(node->path_name);
    ptr = &node->path_name[size-1];

    /* Finds the last '/' and changes it to '\0' */
    for(; ptr != node->path_name && *ptr != '/' ; ptr--);

    /*if it stopped on root, the parent is root. Doesn't changes it to '\0' */
    if (ptr == node->path_name){
        aux = find_hash_node_by_path("/");
    }
    else{
        /* ptr now points to '/'. Changes it to '\0' */
        *ptr = '\0';
        /* aux points to the parent */
        aux = find_hash_node_by_path(node->path_name);
        /* revert the string */
        *ptr = '/';
    }

    return aux;

}

/* Frees node, its brothers and every node below it */
void free_node_down_right(Link node){

    if (node == NULL)
        return;

    if (node->next_down != NULL)
        free_node_down_right(node->next_down);

    if (node->next_right != NULL)
        free_node_down_right(node->next_right);

    if (strcmp("/", node->path_name) != 0) {
        remove_from_path_table(node);
        remove_from_value_table(node);
        free_node(node);
    }
}


