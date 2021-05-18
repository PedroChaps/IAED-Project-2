#include "main_functions.h"


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
void list(char *path, S_Link *Table, int M, S_Link sorted_lst){
    /* Var path is the parent. The objective is to list all children ordered
     * alphabetically.
     * A parallel simple list is created, that stores sorted pointers to the
     * corresponding nodes. Then, prints the list.*/

    /* static variable which counts the number of elements inserted on the
     * sorted list. In order to mitigate efficiency problems. */
    static int cont = 0;
    int i;
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

    /*Skips the first elements which are already in the sorted list */
    for (aux = ptr->next_down, i = 0; i != cont; aux=aux->next_right);
    for (; aux != NULL; aux=aux->next_right){
        sorted_lst = insert_sorted(aux, sorted_lst);
        cont++;
    }

    print_list_basic(sorted_lst);

}






/* -------------------------- AUX Functions ----------------------------------*/

