#include <stdio.h>
#include "list.h"

int main() {

    // Unit test
    list_test();  

    // Create lists for merge/reverse tests
    List l1 = new_list();
    List l2 = new_list();

    // Fill l1
    insert_in_order(&l1, 1);
    insert_in_order(&l1, 5);
    insert_in_order(&l1, 9);

    // Fill l2
    insert_in_order(&l2, 2);
    insert_in_order(&l2, 6);
    insert_in_order(&l2, 10);

    // Print original lists
    printf("\nList l1: ");
    print_list(&l1);
    printf("List l2: ");
    print_list(&l2);

    // Reverse l1
    List rev_l1 = reverse(&l1);
    printf("\nReversed l1: ");
    print_list(&rev_l1);

    // Merge l1 and l2
    List merged = merge(&l1, &l2);
    printf("\nMerged l1 and l2: ");
    print_list(&merged);

    // Optional: destroy lists if you want to free memory
    // destroy_list(&l1);
    // destroy_list(&l2);
    // destroy_list(&rev_l1);
    // destroy_list(&merged);

    return 0;
}