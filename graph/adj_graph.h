#ifndef ADJ_GRAPH_H
#define ADJ_GRAPH_H

typedef struct {
	void* data;
	D_Linked_List* neighbors;
} _Node;

_Node* new_Node(void* data) {
	_Node* self = malloc(sizeof(_Node));
	self->neighbors = new_d_linked_list();
	self->data = data;
	
	return self;
}

_Node* free_Node(_Node* self) {
	self->neighbors = free_D_Linked_List(self->neighbors);
	free(self);
	
	return NULL;
}

typedef struct {
	unsigned long size;
	unsigned long max_size;
	_Node* nodes;
} AdjGraph;

#endif
