#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long int nodes_number;

/* Verifies if the program is OOM (out of memory).
 * This function is only called when memory is allocated, in order to
 * verify if the pointer returned by Malloc is NULL.
 * Calls exit() in order to free memory and quit the program. */
void check_OOM(void *ptr){
    if (ptr == NULL){

        printf("No memory\n");
        exit(EXIT_SUCCESS);
    }
}


/*Function to create a new node.
  When a new node is created, their elements are also created and
  it is inserted on the end of the parent's children list, so it stays sorted
  by insertion;
*/
Link new_node(char *path, char *val, Link parent){

    Link x = (Link) malloc(sizeof(Node));
    check_OOM(x);

    /* Fills x's information */

    /* Path */
    x->path_name = (char *) malloc(sizeof(char) * (strlen(path) + 1));
    check_OOM(x->path_name);

    strcpy(x->path_name, path);


    /* Value */
    /* A node can be created without value (for instance, when the command
     * set is called.
     * So, verifies if the val argument is NULL and if it isn't, allocates
     * memory and copies the value. */
    if (val != NULL) {
        x->value = (char *) malloc(sizeof(char) * (strlen(val) + 1));
        check_OOM(x->value);

        strcpy(x->value, val);
    }
    else {
        x->value = NULL;
    }
    /* Next pointers */
    x->next_down = (x -> next_right = NULL);

    /* Id */
    x->id = ++nodes_number;

    /* Inserts x on the rightest end of the parent's children */
    parent->next_down = list_insert_right_end(parent->next_down, x);

    return x;
}


/* Frees everything associated with a node and the node.
 * Sets everything to null in order to have control. */
Link free_node(Link node){

    if (node == NULL)
        return NULL;

    if(node->path_name != NULL) {
        free(node->path_name);
        node->path_name = NULL;
    }

    if(node->value != NULL) {
        free(node->value);
        node->value = NULL;
    }

    free(node);
    node = NULL;

    return node;
}



/* Function to create the head of the Hierarchy list */
Link create_list(){


    Link head;
    head = (Link) malloc(sizeof(Node));
    check_OOM(head);

    /* Attributes 0 to the global variable */
    nodes_number = 0;

    /* Saves the starting information */
    head->path_name = (char *) malloc(sizeof("/"));
    check_OOM(head->path_name);

    strcpy(head->path_name, "/");

    head->value = NULL;

    head->next_right = (head->next_down = NULL);

    head->id = ++nodes_number;

    return head;
}


/* Insert a node on the right of the rightest node */
Link list_insert_right_end(Link head, Link x){

    Link aux;
    /* If the down element of parent is NULL it means it has no children so x
    * becomes the new child */
    if(head == NULL){
        head = x;
        return head;
    }
    /* Else, head remains unaltered. Finds and updates the rightest node. */
    for(aux = head; aux->next_right != NULL; aux = aux->next_right);
    aux->next_right = x;
    return head;
}


/* Finds and removes a node by traveling the list to the right. The node is not
 * fred on purpose (It is fred afterwards on the main function) */
Link remove_node_right(Link head, Link node_rm){
    Link t, prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next_right) {
        if(t == node_rm) {
            if(t == head)
                head = t->next_right;
            else
                prev->next_right = t->next_right;
            break;
        }
    }
    return head;
}




