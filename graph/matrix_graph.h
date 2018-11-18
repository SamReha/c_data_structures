// Alright, let's fuckin do this.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	void* data;
} _Matrix_Node;


_Matrix_Node* new_Matrix_Node(void* data) {
	_Matrix_Node* self = malloc(sizeof(_Matrix_Node));
	self->data = data;
	
	return self;
}

_Matrix_Node* free_Matrix_Node(_Matrix_Node* m_n) {
	free(self);
	
	return NULL;
}

typedef struct {
	unsigned long max_size;
	_Matrix_Node* nodes;
	bool** edges;
} Matrix_Graph;

MatrixGraph* new_Matrix_Graph(unsigned int max_size) {
	MatrixGraph* self = malloc(sizeof(Matrix_Graph));
	
	self->max_size = max_size;
	self->nodes = calloc(max_size, sizeof(_Matrix_Node));
	self->edges = calloc(max_size, sizeof(bool*));
	
	for (int i = 0; i < max_size; i++) self->edges[i] = calloc(max_size, sizeof(bool));
	
	return self;
}

void* free_Matrix_Graph(Matrix_Graph* self) {
	free(self->nodes);
	
	for (int i = 0; i < self->max_size; i++) free(self->edges[i]);
	free(self->edges);
	
	return NULL;
}

bool matrix_graph_has_edge(Matrix_Graph* self, unsigned int n_1, unsigned int n_2) {
	if (n_1 >= self->max_size) return false;
	if (n_1 >= self->max_size) return false;
	
	return self->edges[n_1][n_2];
}

void matrix_graph_set_edge(Matrix_Graph* self, unsigned int n_1, unsigned int n_2, bool state) {
	if (n_1 >= self->max_size) return;
	if (n_1 >= self->max_size) return;
	
	self->edges[n_1][n_2] = state;
}

void matrix_graph_set_bi_edge(Matrix_Graph* self, unsigned int n_1, unsigned int n_2, bool state) {
	if (n_1 >= self->max_size) return;
	if (n_1 >= self->max_size) return;
	
	self->edges[n_1][n_2] = state;
	self->edges[n_2][n_1] = state;
}

l_list* matrix_graph_get_neighbors(Matrix_Graph* self, unsigned int n) {
	l_list* neighbors = new_l_list();
	
	if (n >= self->max_size) return neighbors;
	
	for (unsigned int i = 0; i < self->max_size; i++) {
		if (self->edges[n][i]) ll_append(neighbors, self->nodes[i]);
	}
	
	return neighbors;
}

bool matrix_graph_is_connected(Matrix_Graph* self, unsigned int n_1, unsigned int n_2) {
	if (n_1 >= self->max_size) return false;
	if (n_1 >= self->max_size) return false;
	
	MatrixGraphNode* node_1 = &(self->nodes[n_1]);
	MatrixGraphNode* node_2 = &(self->nodes[n_2]);
	
	l_list* to_visit = new_l_list();
	l_list* visited = new_l_list();

	while (visited->size < self->max_size + 1) {
		if (node_1 == node_2) return true;
		
		// Add new_friends to to_visit
		l_list* new_friends = matrix_graph_get_neighbors(self, n_1);
		ll_node* friend = new_friends->head;
		while (friend != NULL) {
			if (!ll_in(to_visit, friend->data)) ll_append(to_visit, friend->data);
			friend = friend->next;
		}
		ll_free(new_friends);
		
		// Visit a node
		ll_node* visit = to_visit->head;
		if (visit == NULL) break;
		
		node_1 = &(self->nodes[*(int*)visit->data]);
		ll_append(visited, visit->data);
		ll_remove(to_visit, to_visit->head);
	}
	
	ll_free(to_visit);
	ll_free(visited);
	
	return false;
}

void matrix_graph_print(Matrix_Graph* graph) {
	printf("Graph:\n");
	
	for (int n = 0; n < graph->max_size; n++) {
		l_list* neighbors = matrix_graph_get_neighbors(graph, n);
		
		if (neighbors->size > 0) {
			printf("%d: ", n);
			
			ll_node* neighbor = neighbors->head;
			while (neighbor != NULL) {
				MatrixGraphNode* node = (MatrixGraphNode*)(neighbor->data);
				printf("%d ", node->data);
				neighbor = neighbor->next;
			}
			printf("\n");
		}
		
		ll_free(neighbors);
	}
	
	fflush(stdout);
}
#endif // GRAPH_H
