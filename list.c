#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A static variable that counts the number of nodes created */
static long int nodes_number;

/* Verifies if the program is OOM (out of memory).
 * This function is only called when memory is allocated, in order to
 * verify if the pointer returned by Malloc is NULL.*/


void check_OOM(void *ptr){
    if (ptr == NULL){

        printf("No memory\n");
        exit(EXIT_SUCCESS);
    }
}


/* When a new node is created:
 *      their elements are filled;
 *      it is inserted on the end of the list, so it stays sorted by insertion;
 *      it is inserted on the hash_table.
 */
Link new_node(char *path, char *val, Link parent){

    Link x = (Link) malloc(sizeof(Node));
    check_OOM(x);
    /* Fills x's information */
    x->path_name = (char *) malloc(sizeof(char) * (strlen(path) + 1));
    if (x->path_name == OUT_OF_MEMORY)
        return OUT_OF_MEMORY;

    strcpy(x->path_name, path);

    if (val != NULL) {
        x->value = (char *) malloc(sizeof(char) * (strlen(val) + 1));
        if (x->value == OUT_OF_MEMORY)
            return OUT_OF_MEMORY;
        strcpy(x->value, val);
    }
    else {
        x->value = NULL;
    }

    x->next_down = (x -> next_right = NULL);

    x->id = ++nodes_number;

    /* Inserts x on the rightest end of the parent's children */
    parent->next_down = list_insert_right_end(parent->next_down, x);

    /* Inserts x on the hash tables */
    return x;
}

Link create_list(){


    Link head;
    head = (Link) malloc(sizeof(Node));
    /*Memory doesn't need to be checked because this is one of the first
     * functions to be called */
    if (head == OUT_OF_MEMORY)
        return OUT_OF_MEMORY;


    nodes_number = 0;
    /* Saves the starting information */
    head->path_name = (char *) malloc(sizeof("/"));
    if (head->path_name == OUT_OF_MEMORY)
        return OUT_OF_MEMORY;

    strcpy(head->path_name, "/");

    head->value = NULL;

    head->next_right = head->next_down = NULL;

    head->id = ++nodes_number;


    /* Inserts the head on the tables */
    return head;
}


/*
int list_length(Link head) {
    int count=0;
    Link x;
    for(x = head; x != NULL; x = x->next)
        count++;
    return count;
}



Link list_insert_begin(Link head, char* text){
    Link x = NEW(text);
    x->next = head;
    return x;
}

Link list_insert_end(Link head, char* text){
    Link x;
    if(head == NULL)
        return NEW(text);
    for(x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEW(text);
    return head;
}
*/

/* Insert a node on the right of the rightest node */
Link list_insert_right_end(Link head, Link x){
    /* If the down element of parent is NULL, a.k.a., it has no children,
     * x becomes the new child */
    Link aux;
    if(head == NULL){
        head = x;
        return head;
    }
    /* Else, head remains unaltered. Updates the rightest node. */
    for(aux = head; aux->next_right != NULL; aux = aux->next_right);
    aux->next_right = x;
    return head;
}

/* To prevent headaches during debugging */
/*
void print_list(Link head){
    Link t;
    printf("[");
    if (head != NULL) {
        for (t = head; t->next_right != NULL; t = t->next_right)
            printf("[%s, %s], ", t->path_name, t->value);
        printf("[%s, %s]]\n", t->path_name, t->value);
        return;
    }
    printf("WIP BipBop I think it isnt supposed to be here hehe\n");
}
*/




/* The node is not fred on purpose. It is fred afterwards on the main function */
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


/* Frees a node and all the nodes to his right and down.

    ROOT
     |
     V
     * -> * -> * -> *
     |              |
     V              V
     * -> *         * -> * -> *

 * */

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

int length(Link head) {
    int count = 0;
    Link x;

    for(x = head; x != NULL; x = x->next_right)
        count++;
    return count;
}

void print_list_basic(Link *head, int len, int last_path_i){

    int i;

    for(i = 0; i < len; i++)
        printf("%s\n", head[i]->path_name + last_path_i);


/*
*//* Verifies if head is NULL *//*
if (head == NULL){
    return;
}
*//*prints the list *//*
for(; head != NULL; head = head->next){
    printf("%s\n", get_last_path(head->ptr->path_name));
}*/

}