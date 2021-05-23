#ifndef IAEDPROJ2_MAIN_FUNCTIONS_H
#define IAEDPROJ2_MAIN_FUNCTIONS_H

#include "hash.h"

/* All the commands and their descriptions */
#define COMMAND1 "help"
#define COMMAND2 "quit"
#define COMMAND3 "set"
#define COMMAND4 "print"
#define COMMAND5 "find"
#define COMMAND6 "list"
#define COMMAND7 "search"
#define COMMAND8 "delete"

#define COMMAND1_I "Imprime os comandos disponíveis."
#define COMMAND2_I "Termina o programa."
#define COMMAND3_I "Adiciona ou modifica o valor a armazenar."
#define COMMAND4_I "Imprime todos os caminhos e valores."
#define COMMAND5_I "Imprime o valor armazenado."
#define COMMAND6_I "Lista todos os componentes imediatos de um sub-caminho."
#define COMMAND7_I "Procura o caminho dado um valor."
#define COMMAND8_I "Apaga um caminho e todos os subcaminhos."


/* The two possible errors */
#define ERROR1 "not found\n"
#define ERROR2 "no data\n"

/* Used in a state variable */
#define FOUND 1
#define NOT_FOUND 0

/* All the main functions */
void help();
void quit(Link Hierarchy_list);
void set(char *path, char *val);
void print(Link head);
void find(char *path);
void list(char *path);
void search(char *value);
void delete(char *path);

#endif
