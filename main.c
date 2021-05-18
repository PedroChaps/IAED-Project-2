#include "main_functions.h"


/*
 [X] help
 [ ] quit
 [ ] set
 [~] print      confirm if it works after set is complete
 [X] find       most likely works, but confirm after set is complete
 [~] list       haven't tested yet (fuk set) ;- ;
 [ ] search
 [ ] delete

 *TO DO*
 -> Em cada Malloc, verificar se existe memoria;
 -> Dar free de memoria em cada funcao que faz malloc (para cada Malloc tem que
    haver um free).;
 -> Usar Valgrind para ver se existem fugas de memoria;




 */


int main() {
    Link Hierarchy_lst = create_list();
    S_Link* Table = create_hash_table();
    S_Link sorted_list = create_simple_list();

    Link x = new_node("/bom", "oi :D", Hierarchy_lst, Table);
    Link y = new_node("/tarde", "boas", Hierarchy_lst, Table);
    Link z = new_node("/noite", "aca", Hierarchy_lst, Table);
    //lista = list_insert_right_end(lista->next_down, x);
    //print_list(Hierarchy_lst->next_down);

    char *ptr = find_hash_value("/usr", Table, HASH_SIZE);

    //help();

    //find("/bom", Table, HASH_SIZE);

    //print_all_hierarchy(Hierarchy_lst);


    printf("Hello, World!\n");

    return 0;
}
