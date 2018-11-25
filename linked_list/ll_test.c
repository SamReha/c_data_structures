#include <stdio.h>
#include <assert.h> 

#include "double_linked_list.h"

int main(void) {
	int* n = malloc(sizeof(int));
	*n = 8;
	
	// Test list create
	D_Linked_List* list = d_ll_new();
	assert(d_ll_get_size(list) == 0);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	
	// Test append to empty list
	d_ll_append(list, n);
	assert(d_ll_get_size(list) == 1);
	assert(list->head != NULL);
	assert(list->tail != NULL);
	
	// Test remove only element in list
	free(d_ll_remove(list, 0));
	assert(d_ll_get_size(list) == 0);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	
	// Test remove from empty list
	free(d_ll_remove(list, 0));
	assert(d_ll_get_size(list) == 0);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	
	// Repopulate list (test append at empty and append at non-empty)
	for (int i = 0; i < 10; i++) {
		int* test = malloc(sizeof(int));
		*test = i;
		d_ll_append(list, test);
	}
	
	assert(d_ll_get_size(list) == 10);
	
	// Test remove tail from list
	free(d_ll_remove(list, d_ll_get_size(list)-1));
	assert(d_ll_get_size(list) == 9);
	
	// Test remove mid element from list
	free(d_ll_remove(list, 5));
	assert(d_ll_get_size(list) == 8);
	
	// Test remove head from list
	free(d_ll_remove(list, 0));
	assert(d_ll_get_size(list) == 7);
	
	d_ll_print(list);
	
	// Test d_ll_get
	for (int i = 0; i < d_ll_get_size(list); i++) {
		int* test = (int*)d_ll_get(list, i);
		printf("%d ", *test);
	}
	printf("\n");
	
	// Test d_ll_set
	int* two_hundo = malloc(sizeof(int));
	*two_hundo = 200;
	free(d_ll_set(list, 2, two_hundo));
	
	for (int i = 0; i < d_ll_get_size(list); i++) {
		int* test = (int*)d_ll_get(list, i);
		printf("%d ", *test);
	}
	printf("\n");
	assert(*((int*)d_ll_get(list, 2)) == 200);
	
	// Test depopulate list
	while (d_ll_get_size(list) > 0) free(d_ll_remove(list, 0));
	assert(d_ll_get(list, 0) == NULL);
	
	// Test populate some data
	int* test_1 = malloc(sizeof(int));
	int* test_2 = malloc(sizeof(int));
	int* test_3 = malloc(sizeof(int));
	int* test_4 = malloc(sizeof(int));
	int* test_5 = malloc(sizeof(int));
	
	*test_1 = 1234;
	*test_2 = 1337;
	*test_3 = 2894;
	*test_4 = 0xDEAD;
	*test_5 = 0XBEEF;
	
	d_ll_append(list, test_1);
	d_ll_append(list, test_2);
	d_ll_append(list, test_3);
	d_ll_append(list, test_4);
	d_ll_append(list, test_5);
	
	// Test d_ll_remove_data
	// Test remove tail from list
	free(d_ll_remove_data(list, test_3));
	assert(d_ll_get_size(list) == 4);
	
	// Test remove mid element from list
	free(d_ll_remove_data(list, test_5));
	assert(d_ll_get_size(list) == 3);
	
	// Test remove head from list
	free(d_ll_remove_data(list, test_1));
	assert(d_ll_get_size(list) == 2);
	
	d_ll_print(list);
	assert(d_ll_get(list, 0) == test_2);
	assert(d_ll_get(list, 1) == test_4);
	
	// Test d_ll_has
	assert(d_ll_has(list, test_2) == true);
	assert(d_ll_has(list, test_4) == true);
	assert(d_ll_has(list, test_1) == false);
	assert(d_ll_has(list, test_3) == false);
	assert(d_ll_has(list, test_5) == false);
	
	// Test depopulate list
	while (d_ll_get_size(list) > 0) free(d_ll_remove(list, 0));
	assert(d_ll_get(list, 0) == NULL);
	
	// Test free list
	list = d_ll_free(list);
	assert(list == NULL);
	
	printf("Test executed.\n");
	return 0;
}