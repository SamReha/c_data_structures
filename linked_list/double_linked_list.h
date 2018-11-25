#ifndef LL_H
#define LL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	Interface:
	ll* new_ll();
	
	ll* free_ll();

	unsigned long ll_get_size(ll* list);
	
	void ll_append(ll* list, void* data);
	
	void* ll_get(ll* list, unsigned int index);
	
	void* ll_set(ll* list, unsigned int index, void* data);
	
	void* ll_remove(ll* list, unsigned int index);
	
	void* ll_remove_data(ll* list, void* data);
	
	Bool ll_has(ll* list, void* data);
	
	// void* ll_peak_head(ll* list);
	
	// void* ll_pop_head(ll* list);
	
	// void* ll_peak_tail(ll* list);
	
	// void* ll_pop_tail(ll* list);
*/

// Internal Node
typedef struct _D_Linked_List_Node {
	struct _D_Linked_List_Node* next;
	struct _D_Linked_List_Node* prev;
	void* data;
} _D_Linked_List_Node;

_D_Linked_List_Node* _d_ll_node_new(void* data) {
	_D_Linked_List_Node* self = malloc(sizeof(_D_Linked_List_Node));
	self->data = data;
	self->next = NULL;
	self->prev = NULL;
	
	return self;
}

void* _d_ll_node_free(_D_Linked_List_Node* self) {
	if (self) free(self);
	return NULL;
}

// Linked List
typedef struct D_Linked_List {
	_D_Linked_List_Node* head;
	_D_Linked_List_Node* tail;
	unsigned long _size;
} D_Linked_List;

D_Linked_List* d_ll_new() {
	D_Linked_List* list = malloc(sizeof(D_Linked_List));
	list->head = NULL;
	list->tail = NULL;
	list->_size = 0;
}

D_Linked_List* d_ll_free(D_Linked_List* list) {
	if (list) {
		_D_Linked_List_Node* head = list->head;
		while (head != NULL) {
			_D_Linked_List_Node* next = head->next;
			// free(head->data); NO - freeing data is the client's job. They may want to use it after freeing the list.
			free(head);
			head = next;
		}
		
		free(list);
	}

	return NULL;
}

unsigned long d_ll_get_size(D_Linked_List* list) {
	return list->_size;
}

void d_ll_append(D_Linked_List* list, void* data) {
	_D_Linked_List_Node* node = _d_ll_node_new(data);
	
	if (list->_size == 0) {
		list->head = list->tail = node;
	} else {
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	
	list->_size++;
}

void* d_ll_get(D_Linked_List* list, unsigned int index) {
	if (index >= list->_size) return NULL;
	
	_D_Linked_List_Node* ret = list->head;
	while (index > 0) {
		ret = ret->next;
		index--;
	}
	
	return ret->data;
}

// Returns the data to be overwritten so client can easily free it.
void* d_ll_set(D_Linked_List* list, unsigned int index, void* data) {
	if (index >= list->_size) return NULL;
	
	_D_Linked_List_Node* ret = list->head;
	while (index > 0) {
		ret = ret->next;
		index--;
	}
	
	void* ret_data = ret->data;
	ret->data = data;
	
	return ret_data;
}

// Returns the data to be overwritten so client can easily free it.
void* d_ll_remove(D_Linked_List* list, unsigned int index) {
	if (index >= list->_size) return NULL;
	
	_D_Linked_List_Node* remove = list->head;
	while (index > 0) {
		remove = remove->next;
		index--;
	}
	
	if (remove == list->tail) {
		list->tail = list->tail->prev;
		
		// If list->tail exists, set it's next pointer.
		// Else, list is now empty, so set head to NULL
		if (list->tail) {
			list->tail->next = NULL;
		} else list->head = NULL;
	} else if (remove == list->head) {
		list->head = list->head->next;
		list->head->prev = NULL;
	} else {
		remove->prev->next = remove->next;
		remove->next->prev = remove->prev;
	}
	
	void* ret = remove->data;
	free(remove);
	list->_size--;
	
	return ret;
}

// Returns the data to be overwritten so client can easily free it.
void* d_ll_remove_data(D_Linked_List* list, void* data) {
	if (list->_size == 0) return NULL;
	
	_D_Linked_List_Node* remove = list->head;
	while (remove->data != data) {
		remove = remove->next;
		
		if (remove == NULL) return NULL;
	}
	
	if (remove == list->tail) {
		list->tail = list->tail->prev;
		if (list->tail) list->tail->next = NULL;
	} else if (remove == list->head) {
		list->head = list->head->next;
		list->head->prev = NULL;
	} else {
		remove->prev->next = remove->next;
		remove->next->prev = remove->prev;
	}
	
	void* ret = remove->data;
	free(remove);
	list->_size--;
	
	return ret;
}

bool d_ll_has(D_Linked_List* list, void* data) {
	_D_Linked_List_Node* head = list->head;
	
	while (head != NULL) {
		if (head->data == data) return true;
		head = head->next;
	}
	
	return false;
}

/* These would be better served if implemented on a singly-linked list, or better yet their own data structure
void* d_ll_peak_head(D_Linked_List* list) {
	if (list->_size == 0) return NULL;
	
	return list->head->data;
}
	
void* d_ll_pop_head(D_Linked_List* list) {
	if (list->_size == 0) return NULL;
	
	void* ret = list->head->data;
	d_ll_remove(list, 0);
	return ret;
}

void* d_ll_peak_tail(D_Linked_List* list) {
	if (list->_size == 0) return NULL;
	
	return list->tail->data;
}

void* d_ll_pop_tail(D_Linked_List* list) {
	if (list->_size == 0) return NULL;
	
	void* ret = list->tail->data;
	d_ll_remove(list, list->_size-1);
	return ret;
}
*/

// Mostly for debug
void d_ll_print(D_Linked_List* list) {
	if (list == NULL) return;
	
	_D_Linked_List_Node* head = list->head;
	while (head != NULL) {
		printf("%p ", head->data);
		head = head->next;
	}
	printf("\n");
}

#endif // LL_H
