//
// Created by pedro on 19/05/2021.
//

#ifndef IAEDPROJ2_TERMINAL_READ_H
#define IAEDPROJ2_TERMINAL_READ_H

#define MAX_COMMAND_SIZE 7

#define HELP 1
#define QUIT 2
#define SET 3
#define PRINT 4
#define FIND 5
#define LIST 6
#define SEARCH 7
#define DELETE 8
#define SHH_DELETE_CANT_SEE_THIS 9

#define TRUE 1
#define FALSE 0

int command_read();
int read_path(char Buffer[]);
void read_value(char Buffer[], int i);

#endif //IAEDPROJ2_TERMINAL_READ_H
