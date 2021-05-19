#include "simple_list.h"


S_Link NEW(Link node_ptr)
{
    S_Link x = (S_Link) malloc(sizeof(s_Node));
    x->ptr = node_ptr;
    x->next = NULL;

    return x;
}


S_Link insertBegin(S_Link head, Link node_ptr)
{
    S_Link x = NEW(node_ptr);
    x->next = head;
    return x;
}

/* Searches a list for a specified path.
 * Returns the node pointer that points to the path.
 * If it doesn't exist, returns NULL. */
Link search_list_by_path(S_Link head, char *path){

    S_Link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->ptr->path_name, path) == 0)
            return t->ptr;
    return NULL;

}