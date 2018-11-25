#ifndef VARIABLE_ARRAY_H
#define VARIABLE_ARRAY_H

typedef struct {
	unsigned long _size;
	unsigned long _max_size;
	
	void* _buffer;
} Variable_Array;

Variable_Array* var_array_new(unsigned long max_size) {
	Variable_Array* v_array = malloc(sizeof(Variable_Array));
	v_array->_size = 0;
	v_array->_max_size = max_size;
	v_array->_buffer = calloc(max_size, sizeof(void*));
	
	return v_array;
}

Variable_Array* var_array_free(Variable_Array* v_array) {
	free(v_array->_buffer);
	free(v_array);
	
	return NULL;
}

void var_array_resize(Variable_Array* v_array, unsigned long new_size) {
	// Create new buffer
	void* new_buffer = calloc(new_size, sizeof(void*));
	
	if (!new_buffer) return;
	
	// Copy over old data
	for (unsigned long i = 0; i < new_size && i < v_array->_max_size; i++) {
		new_buffer[i] = v_array->_buffer[i];
	}
	
	// Free old buffer and replace with new buffer
	free(v_array->_buffer);
	v_array->_buffer = new_buffer;
	v_array->_max_size = new_size;
	if (v_array->_size > v_array->_max_size) v_array->_size = v_array->_max_size;
}

unsigned long var_array_get_size(Variable_Array* v_array) {
	return v_array->_size;
}

unsigned long var_array_get_capacity(Variable_Array* v_array) {
	return v_array->_max_size;
}

void* var_array_get(Variable_Array* v_array, unsigned long index) {
	if (index >= v_array->_size) return NULL;
	
	return v_array->_buffer[index];
}

void* var_array_set(Variable_Array* v_array, unsigned long index, void* data) {
	if (index >= v_array->_size) return NULL;
	
	void* old_data = v_array->_buffer[index];
	v_array->_buffer[index] = data;
	return old_data;
}

void* var_array_add(Variable_Array* v_array, unsigned long index, void* data) {
	if (index > v_array->_size) return NULL;
	
	// If we're out of space, we need to resize
	if (index == v_array->_max_size) var_array_resize(v_array, varray->_max_size*2);
	
	// Open up a space for the new element
	for (unsigned long i = v_array->size - 1; i >= index; i--) v_array->_buffer[i++] = v_array->_buffer[i];
	
	v_array->_buffer[index] = data;
	v_array->_size++;
	
	return data;
}

void* var_array_remove(Variable_Array* v_array, unsigned long index) {
	if (index >= v_array->_size) return NULL;
	
	// Pack down the array, overwritting the element to remove
	void* element = v_array->_buffer[index];
	for (unsigned long i = index; i < v_array->_size; i++) v_array->_buffer[i] = v_array->_buffer[i++];
	
	// If the array has gotten tiny, let's shrink it
	v_array->_size--;
	if (v_array->_size < v_array->_max_size/2) var_array_resize(v_array, varray->_max_size/2);
	
	// Send the removed element back to the client
	return element;
}

#endif // VARIABLE_ARRAY_H