#include <stdio.h>
#include <assert.h> 

#include "ll.h"

int main(void) {
	ll* list = new_ll();
	
	int* n = malloc(sizeof(int));
	*n = 8;
	
	assert(ll_get_size(list) == 0);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	
	ll_append(list, n);
	assert(ll_get_size(list) == 1);
	assert(list->head != NULL);
	assert(list->tail != NULL);
	
	free(ll_remove(list, 0));
	assert(ll_get_size(list) == 0);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	
	assert(ll_get_size(list) == 0);
	
	list = free_ll(list);
	assert(list == NULL);
	
	printf("Test executed.\n");
	return 0;
}