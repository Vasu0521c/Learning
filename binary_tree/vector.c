#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

vectar* create_vectar() {
	
	vectar *new_vectar = malloc(sizeof(vectar));
	memset(new_vectar, 0, sizeof(vectar));
	return new_vectar;
}

vectar* create_vectar_with_size(int size) {

	vectar *new_vectar  = malloc(sizeof(vectar));
	new_vectar -> nodes = malloc((2 * size) * sizeof(node));
	memset(new_vectar -> nodes, 0, sizeof(2 * size * (sizeof(node))));
	new_vectar -> size = size * 2;
	return new_vectar;
}

void clear(vectar *vec) {
	
	vectar *clear = vec;
	if(vec -> length == 0) {
		return;
	}
	int i = 0;
	while(i <= (vec -> length)) {
		clear -> nodes = NULL;
		clear++;
		i++;
	}
	vec -> length = 0;
	return;
}

void pop(vectar *vec) {

	if(vec -> length == 0) {
		vec -> size = 0;
		return;
	}
	vec -> length--;
	node *temp   = malloc(sizeof(node) * (vec -> size + 1));
	memset(temp, 0, ((vec -> size + 1) * (sizeof(node))));
	memcpy(temp, vec -> nodes + 1, sizeof(node) * (vec -> length));
	free(vec -> nodes);
	vec -> nodes = temp;
}

void stack_pop(vectar *vec) {

	if(vec -> size == 0) {
		return;
	}
	node *temp   = malloc((sizeof(node)) * (vec -> size + 1));
	memset(temp, 0, ((vec -> size + 1) * (sizeof(node))));
	memcpy(temp, vec -> nodes, sizeof(node) * (vec -> length - 1));
	free(vec -> nodes);
	vec -> nodes = temp;
	vec -> length--;
	return;
}

void push(vectar *vec, node *data) {

	if(vec -> size == 0) {
		vec -> nodes = malloc(sizeof(node));
		vec -> size = 1;
		vec -> nodes -> value  = data -> value;
		vec -> nodes -> parent = data -> parent;
		vec -> nodes -> left   = data -> left;
		vec -> nodes -> right  = data -> right;
		vec -> length = 1;
		return;
	}
	if(vec -> length == vec -> size) {
		node *temp   = malloc((vec -> size * 2) * sizeof(node));
		memset(temp, 0, (vec -> size * 2) * sizeof(node));
		memcpy(temp, vec -> nodes, (vec -> length) * sizeof(node));
		free(vec -> nodes);
		vec -> nodes = temp;
		vec -> size *= 2;
	}
	vec -> length++;
	vec -> nodes[vec -> length - 1].value  = data -> value;
	vec -> nodes[vec -> length - 1].parent = data -> parent;
	vec -> nodes[vec -> length - 1].left   = data -> left;
	vec -> nodes[vec -> length - 1].right  = data -> right;
	return;
}
