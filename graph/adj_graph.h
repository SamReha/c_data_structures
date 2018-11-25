#ifndef ADJ_GRAPH_H
#define ADJ_GRAPH_H

typedef struct {
	void* data;
	D_Linked_List* neighbors;
} _Adj_Graph_Node;

_Adj_Graph_Node* _adj_graph_node_new(void* data) {
	_Adj_Graph_Node* self = malloc(sizeof(_Node));
	self->neighbors = new_d_linked_list();
	self->data = data;
	
	return self;
}

_Adj_Graph_Node* _adj_graph_node_free(_Node* self) {
	self->neighbors = free_D_Linked_List(self->neighbors);
	free(self);
	
	return NULL;
}

typedef struct {
	unsigned long _size;
	unsigned long _max_size;
	_Adj_Graph_Node* _nodes;
} Adj_Graph;

Adj_Graph* adj_graph_new(unsigned long max_size) {
	Adj_Graph* self = malloc(sizeof(Adj_Graph));
	self->_nodes = calloc(max_size, sizeof(void*));
	self->_max_size = max_size;
	self->_size = 0;
	
	return self;
}

Adj_Graph* adj_graph_free(Adj_Graph* self) {
	for (int i = 0; i < self->_max_size; i++) {
		if (self->_nodes[i]) _adj_graph_node_free(self->_nodes[i]);
	}
	free(self->_nodes);
	free(self);
	
	return NULL;
}

#endif
