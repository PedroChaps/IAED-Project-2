#include "main_functions.h"
#include "terminal_read.h"

/* ist199298 - Pedro Chaparro */

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






