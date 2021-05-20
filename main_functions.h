#ifndef IAEDPROJ2_MAIN_FUNCTIONS_H
#define IAEDPROJ2_MAIN_FUNCTIONS_H

#include "list.h"


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
#define COMMAND6_I "Lista todos os componentes de um caminho."
#define COMMAND7_I "Procura o caminho dado um valor."
#define COMMAND8_I "Apaga um caminho e todos os subcaminhos."

#define ERROR1 "not found\n"
#define ERROR2 "no data\n"

#define LAST_CALL 1
#define FOUND 1
#define NOT_FOUND 0
#define MAX_LEN_COMMAND strlen(COMMAND8)
#define MAX_LEN_COMMAND_I strlen(COMMAND3_I)
#define COMMAND_NR 8
/*
char COMMAND_LST[COMMAND_NR][100] = {COMMAND1,
                                              COMMAND2,
                                              COMMAND3,
                                              COMMAND4,
                                              COMMAND5,
                                              COMMAND6,
                                              COMMAND7,
                                              COMMAND8};

char COMMAND_LST_I[COMMAND_NR][100] = {COMMAND1_I,
                                                  COMMAND2_I,
                                                  COMMAND3_I,
                                                  COMMAND4_I,
                                                  COMMAND5_I,
                                                  COMMAND6_I,
                                                  COMMAND7_I,
                                                  COMMAND8_I};
*/
void help();
void find(char *path, S_Link *Table, int M);
void print_all_hierarchy(Link head);
void list(char *path, S_Link *Table, int M);
void set(char *path, char *val, S_Link *Table, int M);
void delete(char *path, S_Link *Table, int M);
void WIP_print_all_hierarchy_including_no_values(Link head);
void quit(S_Link *Table, int M);
#endif //IAEDPROJ2_MAIN_FUNCTIONS_H
