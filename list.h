
#ifndef IAEDPROJ2_LIST_H
#define IAEDPROJ2_LIST_H

/* A node is made up of 4 components:
 *      The path's name;
 *      It's value;
 *      A pointer to the children (next deepness);
 *      A pointer to the next node on it's right;
 *      An identifier that tracks how old the node is.
*/
typedef struct node {
    char *path_name;
    char *value;
    struct node *next_down;
    struct node *next_right;
    long int id;
} Node;

typedef struct node* Link;


/* Check if out of memory */
void check_OOM(void *ptr);

/* Functions that operate lists/nodes */
Link new_node(char *path, char *val, Link parent);
Link free_node(Link node);
Link create_list();
Link list_insert_right_end(Link head, Link x);
Link remove_node_right(Link head, Link node_rm);

#endif
