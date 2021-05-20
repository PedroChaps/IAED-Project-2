#include "list.h"



Link list_insert_end(Link head, char* text);
Link list_insert_right_end(Link head, Link x);

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
Link new_node(char *path, char *val, Link parent, S_Link* table){

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

    /* Inserts x on the rightest end of the parent's children */
    parent->next_down = list_insert_right_end(parent->next_down, x);
    /* Inserts x on the hash table */
    insert_hash_table(x, table, HASH_SIZE);
    return x;
}

Link create_list(S_Link* table){

    Link head = (Link) malloc(sizeof(Node));
    verify_memory(head);

    /* Saves the starting information */
    head->path_name = (char *) malloc(sizeof("/"));
    verify_memory(head->path_name);

    strcpy(head->path_name, "/");
    head->value = NULL;
    head->next_right = head->next_down = NULL;

    insert_hash_table(head, table, HASH_SIZE);
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


Link search_list_by_path(S_Link head, char *path){

    S_Link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->path_name, path) == 0)
            return t->ptr;
    return NULL;

}


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
    //free(node->value);

    node->path_name = NULL;
    node->value = NULL;

    free(node);
    node = NULL;

    return node;
}

/* --------------------- Simple List -------------------------- */
S_Link create_simple_list(){

    S_Link head = (S_Link) malloc(sizeof(s_Node));
    verify_memory(head);

    head->next = NULL;
    head->ptr = NULL;

    return head;
}

S_Link insert_sorted(Link ptr, S_Link head){

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

S_Link remove_elem(S_Link head, Link ptr_rm){
    S_Link t, prev;

    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if(t->ptr == ptr_rm) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            free(t);
            break;
        }
    }
    return head;
}