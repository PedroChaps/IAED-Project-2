#include "terminal_read.h"

#include <stdio.h>
#include <string.h>



/* Reads a command from the terminal */
int command_read(){
    char command_buffer[MAX_COMMAND_SIZE];
    scanf("%s", command_buffer);

    if(strcmp(command_buffer, "help") == 0){
        return HELP;
    }
    else if(strcmp(command_buffer, "quit") == 0){
        return QUIT;
    }
    else if(strcmp(command_buffer, "set") == 0){
        return SET;
    }
    else if(strcmp(command_buffer, "print") == 0){
        return PRINT;
    }
    else if(strcmp(command_buffer, "find") == 0){
        return FIND;
    }
    else if(strcmp(command_buffer, "list") == 0){
        return LIST;
    }
    else if(strcmp(command_buffer, "search") == 0){
        return SEARCH;
    }
    else if(strcmp(command_buffer, "delete") == 0){
        return DELETE;
    }

    else if(strcmp(command_buffer, "deletee") == 0){
        return SHH_DELETE_CANT_SEE_THIS;
    }


    return -1;
}

char fix_slashes(char *path){

}

/* Reads a path, fixing all the slashes */
int read_path(char Buffer[]){

    char z;
    int i = 1;
    int SLASH_INSERTED_BEFORE = FALSE;
    /*Starts by inserting a slash */
    Buffer[0] = '/';
    /* ignores all the starting spaces */
    while ((z = getchar()) == ' ');
    /* ignores all the starting slashes */
    while (z == '/')
        z = getchar();
    /* while not in the end of the path or the size exceeded */
    while (z != ' ' && z != '\t' && z != '\n'){

        /* if z is a slash, only inserts one */
        if (z == '/'){
            if (SLASH_INSERTED_BEFORE == FALSE) {
                Buffer[i++] = z;
                SLASH_INSERTED_BEFORE = TRUE;
            }
        }
        /* else inserts the character normally */
        else{
            Buffer[i++] = z;
            SLASH_INSERTED_BEFORE = FALSE;
        }

        z = getchar();
    }

    /* Verifies if the last character was a slash */
    if (Buffer[i-1] == '/'){
        Buffer[i-1] = '\0';
    }
    else {
        Buffer[i] = '\0';
    }
    /* Returns the index where the \0 was inserted */
    return i;
}

void read_value(char Buffer[], int i){
    char z;

    /* ignores all the starting spaces */
    while ((z = getchar()) == ' ');

    /* Fills the buffer */
    while (z != '\n'){
        Buffer[i++] = z;
        z = getchar();
    }

    /* Checks if multiple spaces / tabs were inserted on the end.
     * Places '\0' on the last character */
    while(Buffer[i--] == ' ' || Buffer[i] == '\t');
    Buffer[i+1] = '\0';

}
