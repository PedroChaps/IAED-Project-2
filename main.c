#include "main_functions.h"
#include "terminal_read.h"

/* ist199298 - Pedro Chaparro */



/*
The goal of this program is to have a hierarchy system like a file system which stores paths and values.
To have an efficient program, the following structures were implemented:

~~~~~~~~~ ~~~~~~~~~ Linked List with two Nexts ~~~~~~~~~ ~~~~~~~~~

The main structure can be defined as a linked List but each node has two "nexts", one that points to the right,
which represents nodes in the same deepness, and other that points down, which represents the next deepness.

The Node also has two strings, the path and value, and an identifier (which purpose is to distinguish how old a node is).

When the first path of a certain deepness of a certain parent is created, e.g., "/usr/local/bin", it's parent is "/usr/local".
So, the node's which path is "usr/local" next_down will point to "usr/local".

If a new node of the same parent is created, e.g., "/usr/local/etc", this new node will be inserted on the right of the
previously created Node which path is "usr/local".

Here is a sketch:
(/, /a, /a/b, /a/b/c, /b, /c, /c/x, /c/y)
    ┌───┐
    │ / │
    └─┬─┘
      │
    ┌─v─┐   ┌────┐  ┌────┐
    │/a ├───> /b ├──> /c │
    └─┬─┘   └────┘  └──┬─┘
      │                │
   ┌──v──┐          ┌──v──┐     ┌─────┐
   │/a/b │          │/c/x ├─────>/c/y │
   └──┬──┘          └─────┘     └─────┘
      │
      │
   ┌──v───┐
   │/a/b/c│
   └──────┘

~~~~~~~~~ ~~~~~~~~~ Hash Tables ~~~~~~~~~ ~~~~~~~~~


To easily access the nodes, two hash tables were created, one that stores nodes by Path and other that stores nodes by Value.

For instance, if the objective is to verify if the path "/usr/local/bin" has already been created, instead of searching the
whole List for the path the alternative is to hash("/usr/local/bin") and search the given index of the table for the node.
The value's table (and Node's identifier) only purpose is to find the oldest node that has a certain value.

To create the hash tables, an auxiliary simple List structure was created.



 */


int main() {

    /* Creates the Hierarchy List */
    Link Hierarchy_lst = start_list();

    int i;

    /* The buffer and a pointer to the buffer */
    char buffer_fixed[BUFFER_SIZE];
    char *buffer = buffer_fixed;

    char *aux;

    while (IST > OTHER_UNIVERSITIES) {
        /* Depending on the command, a path, a value or a path and a value are
         * read and the associated functions are called. */
        switch (command_read()) {

            case HELP:
                help();
                break;

            case QUIT:
                quit(Hierarchy_lst);
                break;

            case SET:
                /* i is the index of where the '\0' was inserted on the buffer.
                 * Used to tell read_value where it can store the value on
                 * the buffer (so only a buffer is necessary). */
                i = read_path(buffer);

                /* Inserts the value on the next index */
                read_value(buffer, i+1);

                /* aux points to the value read */
                aux = &buffer[i+1];
                set(buffer, aux);
                break;

            case PRINT:
                print(Hierarchy_lst);
                break;

            case FIND:
                read_path(buffer);
                find(buffer_fixed);
                break;

            case LIST:
                read_path(buffer);
                list(buffer_fixed);
                break;

            case SEARCH:
                read_value(buffer, 0);
                search(buffer_fixed);
                break;

            case DELETE:
                read_path(buffer);
                delete(buffer_fixed);
                break;

        }

    }
}






