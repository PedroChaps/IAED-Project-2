#include "main_functions.h"
#include "terminal_read.h"
#include <stdio.h>
#define BUFFER_SIZE 65535

/*
 [X] help
 [X] quit
 [X] set
 [X] print      confirm if it works after set is complete
 [X] find       most likely works, but confirm after set is complete
 [X] list       haven't tested yet (fuk set) ;- ; . Devo ter que mudar, é O(N^3)
 [ ] search
 [X] delete

 [X] read input

 *TO DO*
 -> Em cada Malloc, verificar se existe memoria;
 -> Dar free de memoria em cada funcao que faz malloc (para cada Malloc tem que
    haver um free).;
 -> Usar Valgrind para ver se existem fugas de memoria;

 -> list sem nada



 */


int main() {

    int command, i;
    char buffer_fixed[BUFFER_SIZE];
    char *buffer = buffer_fixed;
    char *aux;

    Link Hierarchy_lst = start_list();
    if (Hierarchy_lst == OUT_OF_MEMORY)
        quit(Hierarchy_lst);
    /*test_stuff(Table, Hierarchy_lst, sorted_list);*/



    while (1) {

        switch (command = command_read()) {

            case HELP:
                help();
                break;

            case QUIT:
                quit(Hierarchy_lst);
                return 0;
                break;

            case SET:
                /* Index of where the \0 was inserted on the buffer */
                i = read_path(buffer);
                /* Inserts the value on the next index */
                read_value(buffer, i + 1);
                aux = &buffer[i + 1];
                set(buffer, aux, Hierarchy_lst);
                break;

            case PRINT:
                print_all_hierarchy(Hierarchy_lst);
                break;

            case FIND:
                read_path(buffer);
                find(buffer_fixed);
                break;

            case LIST:
                read_path(buffer);
                list(buffer_fixed, Hierarchy_lst);
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
        buffer_fixed[0] = '\0';
    }
}


/* Tentar descomentar no quit(). Se ganhei 1 teste por causa disso, o bug
 * deve estar no delete





 */



/*
int test_stuff(S_Link* Table, Link Hierarchy_lst, S_Link sorted_list){



    char *str_path = (char*) malloc(sizeof("/a"));
    strcpy(str_path, "/a/b/f");
    char *str_val = (char*) malloc(sizeof("hi"));
    strcpy(str_val, "hi");
    set(str_path, str_val, Table, HASH_SIZE);

    char *str_path1 = (char*) malloc(sizeof("/a"));
    strcpy(str_path1, "/b");
    char *str_val1 = (char*) malloc(sizeof("hi"));
    strcpy(str_val1, "boas");
    set(str_path1, str_val1, Table, HASH_SIZE);

    char *str_path2 = (char*) malloc(sizeof("/c/d"));
    strcpy(str_path2, "/c/d");
    char *str_val2 = (char*) malloc(sizeof("teste"));
    strcpy(str_val2, "teste");
    set(str_path2, str_val2, Table, HASH_SIZE);

    print_all_hierarchy(Hierarchy_lst);
WIP_print_all_hierarchy_including_no_values(Hierarchy_lst);
    printf("\n");
    */
/*
printf("\n");
list("/a/b", Table, HASH_SIZE);
*/
/*
char *str_path3 = (char*) malloc(sizeof("/a"));
strcpy(str_path, "/c/d");
char *str_val3 = (char*) malloc(sizeof("hi"));
strcpy(str_val, "teste");
new_node()
*/
/*
    char buffer1[100];
    char buffer2[100];
    char buffer3[100];
    scanf("%s", buffer1);
    scanf("%s", buffer2);
    scanf("%s", buffer3);
    printf("%s %s", buffer1, buffer3);

    print_all_hierarchy(Hierarchy_lst);
WIP_print_all_hierarchy_including_no_values(Hierarchy_lst);

    quit(Table, HASH_SIZE);

*/
/* Nova hash table para organizar os valores: guardo os pointers;
 * Contador para o nr nodes: Serial code;
 *
 * Double link list OPT
 *
 *
 * */
/*
lista = list_insert_right_end(lista->next_down, x);
print_list(Hierarchy_lst->next_down);

printf("%s\n", get_last_path("/a/b/c/d/e"));
help();

find("/bom", Table, HASH_SIZE);

print_all_hierarchy(Hierarchy_lst);

list("/", Table, HASH_SIZE);*/
/*
    printf("Hello, World!\n");

}
*/



/* set /a/b/c 5
 *
 * /a/b/c existe?
 *
 * i = hash("/a/b/c")
 * procurar table[i] algum no com "/a/b/c"
 *
 *
 * */
