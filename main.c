#include "main_functions.h"


/*
 [X] help
 [ ] quit
 [X] set
 [X] print      confirm if it works after set is complete
 [X] find       most likely works, but confirm after set is complete
 [~] list       haven't tested yet (fuk set) ;- ; . Devo ter que mudar, é O(N^3)
 [ ] search
 [ ] delete

 *TO DO*
 -> Em cada Malloc, verificar se existe memoria;
 -> Dar free de memoria em cada funcao que faz malloc (para cada Malloc tem que
    haver um free).;
 -> Usar Valgrind para ver se existem fugas de memoria;




 */


int main() {

    S_Link* Table = create_hash_table();
    Link Hierarchy_lst = create_list(Table);
    S_Link sorted_list = create_simple_list();
    /*
    Link z = new_node("/n", "aca", Hierarchy_lst, Table);
    Link x = new_node("/b", "oi :D", Hierarchy_lst, Table);
    Link y = new_node("/t", "boas", Hierarchy_lst, Table);
    */

    char *str_path = (char*) malloc(sizeof("/a"));
    strcpy(str_path, "/a/b/f");
    char *str_val = (char*) malloc(sizeof("hi"));
    strcpy(str_val, "hi");
    set(str_path, str_val, Table, HASH_SIZE);

    char *str_path1 = (char*) malloc(sizeof("/a"));
    strcpy(str_path, "/b");
    char *str_val1 = (char*) malloc(sizeof("hi"));
    strcpy(str_val, "boas");
    set(str_path, str_val, Table, HASH_SIZE);

    char *str_path2 = (char*) malloc(sizeof("/a"));
    strcpy(str_path, "/c/d");
    char *str_val2 = (char*) malloc(sizeof("hi"));
    strcpy(str_val, "teste");
    set(str_path, str_val, Table, HASH_SIZE);

    print_all_hierarchy(Hierarchy_lst);

    printf("\n");
    list("/b", Table, HASH_SIZE);













    //lista = list_insert_right_end(lista->next_down, x);
    //print_list(Hierarchy_lst->next_down);

    //printf("%s\n", get_last_path("/a/b/c/d/e"));
    //help();

    //find("/bom", Table, HASH_SIZE);

    //print_all_hierarchy(Hierarchy_lst);

    //list("/", Table, HASH_SIZE);

    printf("Hello, World!\n");

    return 0;
}
