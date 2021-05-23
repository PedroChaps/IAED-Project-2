#ifndef IAEDPROJ2_TERMINAL_READ_H
#define IAEDPROJ2_TERMINAL_READ_H

/* Defines that are used to identify the command that was read */
#define HELP 1
#define QUIT 2
#define SET 3
#define PRINT 4
#define FIND 5
#define LIST 6
#define SEARCH 7
#define DELETE 8
#define IGNORE -1

/* Used to verify if a slash was inserted before */
#define TRUE 1
#define FALSE 0

/* Max buffer size */
#define BUFFER_SIZE 65535

#define IST 1
#define OTHER_UNIVERSITIES 0

/* Functions to read a command, path or value from the terminal. */
int command_read();
int read_path(char Buffer[]);
void read_value(char Buffer[], int i);

#endif
