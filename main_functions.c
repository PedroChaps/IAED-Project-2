#include "main_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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



/* Quits the program, deleting all the allocated memory:
 *  Deletes everything below the Hierarchy List (root);
 *  Frees the Hierarchy List name and Node;
 *  Frees both hash tables;
 *  Quits the program. */
void quit(Link Hierarchy_list){
    delete("/");

    free(Hierarchy_list->path_name);
    free(Hierarchy_list);

    free_hash_tables();

    exit(EXIT_SUCCESS);
}


/* Prototype of the function create_paths_to_path.
 * Creates all the sub-paths leading to the path.
 * If the input is "/a/b/c", creates the sub-paths "/a" and "/a/b", if not
 * created before.
 * Used on the next function. */
void create_paths_to_path(char *path);

/* Sets a value to a specified path */
void set(char *path, char *val){

    Link ptr;
    /* Verifies if path is NULL */
    if (strcmp("", path) == 0 || path == NULL){
        return;
    }

    /*Verifies if the path has already been created by finding the corresponding
     * node on the Path Table.
     * Pointer can either have an address which points to the Node: In this case
     * alters the value; Or can can be NULL, which means it hasn't been created:
     * creates all the sub-paths that lead to path */
    ptr = find_hash_node_by_path(path);

    if (ptr != NULL){
        /* If pointer already had a value, removes old entry from the value hash
         * table and frees the value */
        if (ptr->value != NULL) {
            remove_from_value_table(ptr);
            free(ptr->value);
        }


        /* If the value from the input is NULL, also sets the value to NULL */
        if (strcmp("", val) == 0 || val == NULL){
            ptr->value = NULL;
            return;
        }
        else {
            /* Allocates memory to the value and copies the value from the
             * input */
            ptr->value = (char *) malloc(sizeof(char) * (strlen(val) + 1));
            check_OOM(ptr->value);
            strcpy(ptr->value, val);

            /* Updates pointer value on hash table */
            insert_value_table(ptr);
            return;
        }
    }


    /*Otherwise, all the paths leading to path that are not created must be
     * created first.
     * Eg. If the objective is to "set /a/b/c/d hi" but / and /a are the only
     * paths that exist, "/a/b", "/a/b/c" and "/a/b/c/d" must be created first,
     * without any value associated, and only then the value is associated to
     * /a/b/c/d */

    /* Creates all the missing paths */
    create_paths_to_path(path);

    /* calls set again to set the value to the path that is now created */
    set(path, val);

}



/* Prints all the paths and it's values */
void print(Link head){
    /* Recursive function. Stop case is when head is NULL. */
    if (head == NULL){
        return;
    }
    /* Only prints if head has a value */
    if (head->value != NULL){
        printf("%s %s\n", head->path_name, head->value);
    }

    /* The order of printing is down (deepness comes first) and then right
     * (since the insertion order is preserved when going right). */
    print(head->next_down);
    print(head->next_right);
}



/* Finds what value a specified path has */
void find(char *path){

    Link ptr;

    /* finds the path on the hash table.
     * if the path is not found, a NULL pointer is returned.
     * if the path is found but it has no value, it's value is NULL. */

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

    Link ptr;
    Link aux;
    S_Link temp_lst;

    ptr = find_hash_node_by_path(path);
    temp_lst = NULL;

    /* path is the parent. The objective is to list all children ordered
     * alphabetically.
     * A parallel simple List is created, that stores sorted pointers to the
     * corresponding nodes.
     * Then, prints the list.*/

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
     * will be compared and inserted sorted on a new auxiliary simple List */
    for (aux = ptr->next_down; aux != NULL; aux=aux->next_right){
        temp_lst = insert_sorted_by_path(aux, temp_lst);
    }
    /* Prints the list */
    print_list_basic(temp_lst);
    /* Frees the list */
    free_list(temp_lst);

}



/* Searches for the oldest path that has a certain value */
void search(char *value){

    Link ptr;

    /* Searches the Value Table for the node that has value as value */
    ptr = find_hash_node_by_value(value);

    /* if pointer is NULL, it means no path was found */
    if (ptr == NULL){
        printf(ERROR1);
        return;
    }
    /* prints the path name */
    printf("%s\n", ptr->path_name);

}



/* Prototype of find_parent_path, which finds the Node that is parent of a
 * specified Node.
 * If Node's path is "/a/b/c", returns the Node which path is "/a/b" */
Link find_parent_path(Link node);

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

    /* Finds the node associated with path and it's parent (in order to update
     * node's previous node's next). */
    node = find_hash_node_by_path(path);

    if (node == NULL){
        printf("%s", ERROR1);
        return;
    }
    /* Finds the parent */
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

    }

    /* if the path to be deleted is Root, just has to free every node to the
     * right and down of the first child and the child */
    else {
        node->next_down = free_node_down_right(node->next_down);
    }
}



/* -------------------------- AUX Functions ----------------------------------*/


/* Creates all the missing paths that lead to a path */
void create_paths_to_path(char *full_path){
    /* State variable that indicates if an already existing path is found */
    int state = NOT_FOUND;
    /* Counts number of '/' */
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

    /* The cycle ended when an already created directory was found (on last case,
     * "/"). Now, all the missing directories must be created.
     * To do that, replenishes all the '\0' to '/', creating every path on each
     * step, until the number of '/' inserted is equal to the number of
     * '\0' switched (when cont is 0). */
    ptr = full_path;
    while (cont != 0){
        /*Finds the pointer to the full path, which is guaranteed to exist */
        aux = find_hash_node_by_path(full_path);
        /* Reverts '\0' and discounts 1 on count */
        for(; *ptr != '\0'; ptr++);
        *ptr = '/'; cont--;
        /* Creates the new path, without value (NULL) */
        new = new_node(full_path, NULL, aux);
        insert_tables(new);
    }
}



/* Given a path, finds it's parent path.
 * If the path is /a/b/c, it's parent path is /a/b;
 * If the path /a/b/c and /a/b/d exist, /a/b/d's parent path is still /a/b;
 * uses an auxiliary pointer to find the last '/' and switch it to
 * '\0' temporarily. */
Link find_parent_path(Link node){

    unsigned int size;
    char *ptr;
    Link aux;

    if (node == NULL){
        return NULL;
    }

    size = strlen(node->path_name);
    /* Pointer that points to the last character */
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
        /* makes aux point to the parent */
        aux = find_hash_node_by_path(node->path_name);
        /* revert the string */
        *ptr = '/';
    }
    /* Returns the parent node */
    return aux;

}




