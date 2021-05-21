#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int nodes_number;

/* WIP meio que copiei por ti Andre ;- ; */
void verify_memory(void *ptr){
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

    /* Fills x's information */
    x->path_name = (char *) malloc(sizeof(char) * (strlen(path) + 1));
    verify_memory(x->path_name);
    strcpy(x->path_name, path);

    if (val != NULL) {
        x->value = (char *) malloc(sizeof(char) * (strlen(val) + 1));
        verify_memory(x->value);
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
    verify_memory(head);


    nodes_number = 0;
    /* Saves the starting information */
    head->path_name = (char *) malloc(sizeof("/"));
    verify_memory(head->path_name);

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

    free(node->path_name);
    /*WIP free(node->value);*/

    node->path_name = NULL;
    node->value = NULL;

    free(node);
    node = NULL;

    return node;
}

