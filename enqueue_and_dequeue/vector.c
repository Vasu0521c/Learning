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

	vectar *new_vectar = malloc(sizeof(vectar));
	new_vectar -> data = malloc((2 * size) * sizeof(int));
	new_vectar -> size = size * 2;
	return new_vectar;
}

void clear(vectar *vec) {
	
	if(vec -> length == 0) {
		return;
	}
	int i = 0;
	while(i <= (vec -> length)) {
		vec -> data[i] = 0;
		i++;
	}
	vec -> length = 0;
	return;
}

void pop(vectar *vec) {

	if(vec -> size == 0) {
		return;
	}
	vec -> data[vec -> length - 1] = 0;
	vec -> length--;
	return;
}

void push(vectar *vec, int data) {

	if(vec -> size == 0) {
		vec -> data = malloc(sizeof(int));
		vec -> size = 1;
	}
	if(vec -> length == vec -> size) {
		int *temp = malloc((vec -> size * 2) * sizeof(int));
		memcpy(temp, vec -> data, (vec -> size * sizeof(int)));
		free(vec -> data);
		vec -> data = temp;
		vec -> size *= 2;
	}
	vec -> data[vec -> length] = data;
	vec -> length++;
	return;
}

int compare(vectar *vec_a, vectar *vec_b) {

	if((vec_a -> length) != (vec_b -> length)) {
		return 0;
	}
	int i = 0;
	while(i < (vec_a -> size)) {
		if((vec_a -> data[i]) != (vec_b -> data[i]))
			return 0;
		i++;
	}
	return 1;
}

vectar* reverse(vectar *vec) {

	if((vec -> length) == 0) {
		return create_vectar();
	}
	vectar *reversed_vec   = create_vectar_with_size(vec -> size);
	reversed_vec -> size   = vec -> size;
	reversed_vec -> length = vec -> length;
	int vec_length         = vec -> length - 1;
	int i = vec_length;
	while(i >= 0) {
		reversed_vec -> data[vec_length - i] = vec -> data[i];
		i--;
	}
	return reversed_vec;
}

void self_reverse(vectar *vec) {

	int i = 0;
	int length = (vec -> length) - 1;
	while(i < length) {
		int temp            = vec -> data[i];
		vec -> data[i]      = vec -> data[length];
		vec -> data[length] = temp;
		i++;
		length--;
	}
	return;
}

vectar* clone(vectar *vec) {

	if((vec -> length) == 0) {
		return create_vectar_with_size(vec -> size);
	}
	vectar *cloned_vec   = create_vectar_with_size(vec -> size);
	cloned_vec -> length = vec -> length;
	cloned_vec -> size   = vec -> size;
	int i                = vec -> length - 1;
	while(i >= 0) {
		cloned_vec -> data[i] = vec -> data[i];
		i--;
	}
	return cloned_vec;
}

void insert_at(vectar *vec, int index, int data) {
	
	if(index > (vec -> length)) {
		return;
	}
	if(index == (vec -> length)) {
		vec -> data[index] = data;
		return;
	}
	int i = index;
	int temp = (vec -> data[i]);
	while(i < (vec -> length - 1)) {
		vec -> data[i] = data; 
		data           = temp;
		temp           = vec -> data[i+1];
		i++;
	}
	return;
	
}

void remove_at(vectar *vec, int index) {

	if(index > (vec -> length - 1)) {
		return;
	}
	int i = index;
	while(i < (vec -> length - 1)) {
		vec -> data[i] = vec -> data[i + 1];
		i++;
	}
	vec -> data[i] = 0;
	return;
}

void display(vectar *vec) {

	int i = 0;
	while (i < (vec -> length - 1)) {
		printf("%d, ", vec -> data[i]);
		i++;
	}
	printf("%d\n", vec -> data[i]);
	return;
}
