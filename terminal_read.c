#include "terminal_read.h"

#include <stdio.h>
#include <string.h>



/* Reads a command from the terminal */
int command_read(){
    char command_buffer[BUFFER_SIZE];

    /* Scans the command and compares it with the available commands */
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

    /* If the command isn't one of the available, ignores it */
    return IGNORE;
}



/* Reads a path, fixing all the slashes from the path.
 * The path "/////a/////////b//c/" becomes "/a/b/c" */
int read_path(char Buffer[]){
    char z;
    int i = 1;
    /* Control variable that checks if a slash was already inserted*/
    int SLASH_INSERTED_BEFORE = FALSE;

    /*Starts by inserting a slash on the buffer */
    Buffer[0] = '/';

    /* ignores all the starting spaces */
    while ((z = getchar()) == ' ' || z =='\t');
    /* ignores all the starting slashes */
    while (z == '/')
        z = getchar();

    /* while not in the end of the path */
    while (z != ' ' && z != '\t' && z != '\n'){

        /* if z is a slash, inserts it only if one hadn't been inserted before*/
        if (z == '/'){
            if (SLASH_INSERTED_BEFORE == FALSE) {
                Buffer[i++] = z;
                /* Updates the state variable */
                SLASH_INSERTED_BEFORE = TRUE;
            }
        }
        /* else inserts the character normally and changes the state variable */
        else{
            Buffer[i++] = z;
            SLASH_INSERTED_BEFORE = FALSE;
        }
        /* Gets a new character */
        z = getchar();
    }

    /* Verifies if the last character was a slash */
    if (Buffer[i-1] == '/'){
        Buffer[i-1] = '\0';
    }
    else {
        Buffer[i] = '\0';
    }
    /* Returns the index where '\0' was inserted */
    return i;
}


/* Reads a value after index i */
void read_value(char Buffer[], int i){
    char z;

    /* ignores all the starting spaces */
    while ((z = getchar()) == ' ' || z == '\t');

    /* Fills the buffer, after the index i */
    while (z != '\n'){
        Buffer[i++] = z;
        z = getchar();
    }

    /* Checks if multiple spaces / tabs were inserted on the end.
     * Places '\0' on the last space/tab inserted */
    while(Buffer[--i] == ' ' || Buffer[i] == '\t');
    Buffer[i+1] = '\0';

    /* Before, I had "Buffer[i--]" which made me pass in -7 tests.
     *
     * It took me COUNTLESS hours searching the whole code to find a possible
     * bug, a print where it shouldn't be, etc .
     *
     * But it was here, on line 110 of this file, on a simple misplaced
     * "--", where the bug was hidden. :(
     *
     * Sorry for breaking the professionalism but I really had to say this to
     * feel a little better. :D */
}
