 #include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%d", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}
//List_test function
void list_test() {

    List my_list = new_list();

    printf("Testing insert_at_front...\n");

    insert_at_front(&my_list, 5);
    insert_at_front(&my_list, 3);
    insert_at_front(&my_list, 7);
    insert_at_front(&my_list, 2);
    insert_at_front(&my_list, 0);

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("Result: ");

    print_list(&my_list);

    destroy_list(&my_list);
}

//Option helper functions
void option_insert(List* self) {

    int x;
    printf("Enter number: ");
    scanf("%d", &x);

    insert_at_front(self, x);
}

void option_delete(List* self) {

    int x;
    printf("Delete number: ");
    scanf("%d", &x);

    delete_list(self, x);
}

void option_print(List* self) {

    print_list(self);
}

void list_adhoc_test() {

    List my_list = new_list();

    int quit = 0;

    while (!quit) {

        int option;

        printf("\n===== MENU =====\n");
        printf("0. Quit\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Reverse Test\n");
        printf("5. Merge Test\n");

        printf("Enter option: ");
        scanf("%d", &option);

        if (option == 0) {
            quit = 1;
        }
        else if (option == 1) {
            option_insert(&my_list);
        }
        else if (option == 2) {
            option_delete(&my_list);
        }
        else if (option == 3) {
            option_print(&my_list);
        }

        // ✅ REVERSE TEST
        else if (option == 4) {
            List rev = reverse(&my_list);

            printf("Reversed list: ");
            print_list(&rev);

            destroy_list(&rev);
        }

        // ✅ MERGE TEST
        else if (option == 5) {

            List l2 = new_list();

            int n, val;

            printf("How many elements for second list? ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++) {
                printf("Enter value: ");
                scanf("%d", &val);
                insert_in_order(&l2, val);
            }

            printf("List 1: ");
            print_list(&my_list);

            printf("List 2: ");
            print_list(&l2);

            List merged = merge(&my_list, &l2);

            printf("Merged list: ");
            print_list(&merged);

            destroy_list(&l2);
            destroy_list(&merged);
        }

        else {
            printf("Invalid option!\n");
        }
    }

    destroy_list(&my_list);
}
//Reverse list function
List reverse(List* self)
{
    List newList = new_list();

    ListNodePtr current = self->head;

    while (current != NULL)
    {
        insert_at_front(&newList, current->data);
        current = current->next;
    }

    return newList;
}
// Merge function for ordered list
List merge(List* a, List* b)
{
    List result = new_list();

    ListNodePtr ca = a->head;
    ListNodePtr cb = b->head;

    while (ca != NULL && cb != NULL)
    {
        if (ca->data < cb->data)
        {
            insert_in_order(&result, ca->data);
            ca = ca->next;
        }
        else
        {
            insert_in_order(&result, cb->data);
            cb = cb->next;
        }
    }

    while (ca != NULL)
    {
        insert_in_order(&result, ca->data);
        ca = ca->next;
    }

    while (cb != NULL)
    {
        insert_in_order(&result, cb->data);
        cb = cb->next;
    }

    return result;
}