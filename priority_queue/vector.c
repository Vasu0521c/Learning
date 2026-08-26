#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

vectar* create_vectar() {
	
	vectar *new_vectar = malloc(sizeof(vectar));
	memset(new_vectar, 0, sizeof(vectar));
	return new_vectar;
}

queue* create_queue(int data, int priority) {

	queue *new_queue      = malloc(sizeof(queue));
	new_queue -> data     = data;
	new_queue -> priority = priority;
	return new_queue;
}

vectar* create_vectar_with_size(int size) {

	vectar *new_vectar = malloc(sizeof(vectar));
	new_vectar -> que  = malloc((size * 2) * (sizeof(queue)));
	new_vectar -> size = size * 2;
	return new_vectar;
}

void clear(vectar *vec) {
	
	if(vec -> length == 0) {
		return;
	}
	int i = 0;
	while(i <= (vec -> length)) {
		vec -> que[i].data = 0;
		i++;
	}
	vec -> length = 0;
	return;
}

void pop(vectar *vec) {

	if(vec -> size == 0) {
		return;
	}
	vec -> que[vec -> length - 1].data = 0;
	vec -> length--;
	return;
}

void push(vectar *vec, int data, int priority) {

	if(vec -> size == 0) {
		vec -> que = malloc(sizeof(queue));
		memset(vec -> que, 0, sizeof(queue));
		vec -> size = 1;
	}
	if(vec -> length == vec -> size) {
		queue *temp = malloc((vec -> size * 2) * sizeof(queue));
		memcpy(temp, vec -> que, ((vec -> size) * sizeof(queue)));
		free(vec -> que);
		vec -> que   = temp;
		vec -> size *= 2;
	}
	if(vec -> length != 0) {
		int i = 0;
		while(i < vec -> length) {
			if(vec -> que[i].priority > priority) {
				while (i <= vec -> length) {
					int temp_d             = vec -> que[i].data;
					int temp_p             = vec -> que[i].priority;
					vec -> que[i].data     = data;
					vec -> que[i].priority = priority;
					data                   = temp_d;
					priority               = temp_p;
					i++;
				}
				vec -> length += 1;
				return;
			}
			i++;
		}
	}
	vec -> que[vec -> length].data = data;
	vec -> que[vec -> length].priority = priority;
	vec -> length += 1;
	return;
}

int compare(vectar *vec_a, vectar *vec_b) {

	if((vec_a -> length) != (vec_b -> length)) {
		return 0;
	}
	int i = 0;
	while(i < (vec_a -> size)) {
		if((vec_a -> que[i].data) != (vec_b -> que[i].data))
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
		reversed_vec -> que[vec_length - i].data = vec -> que[i].data;
		i--;
	}
	return reversed_vec;
}

void self_reverse(vectar *vec) {

	int i = 0;
	int length = (vec -> length) - 1;
	while(i < length) {
		int temp                = vec -> que[i].data;
		vec -> que[i].data      = vec -> que[length].data;
		vec -> que[length].data = temp;
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
		cloned_vec -> que[i].data = vec -> que[i].data;
		i--;
	}
	return cloned_vec;
}

void insert_at(vectar *vec, int index, int data) {
	
	if(index > (vec -> length)) {
		return;
	}
	if(index == (vec -> length)) {
		vec -> que[index].data = data;
		return;
	}
	int i = index;
	int temp = (vec -> que[i].data);
	while(i < (vec -> length - 1)) {
		vec -> que[i].data    = data; 
		data                  = temp;
		temp                  = vec -> que[i+1].data;
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
		vec -> que[i].data = vec -> que[i + 1].data;
		i++;
	}
	vec -> que[i].data = 0;
	return;
}

void display(vectar *vec) {

	int i = 0;
	while (i < (vec -> length)) {
		printf("data : %d,  priority : %d\n", vec -> que[i].data, vec -> que[i].priority);
		i++;
	}
	return;
}
