#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vector.h"

void test();

vectar* queue_pop(vectar *vec) {

	if(vec -> length == 0) {
		return vec;
	}
	vectar *vec_b   = create_vectar_with_size(vec -> size / 2);
	vec_b -> length = vec -> length;
	memcpy(vec_b -> data, (vec -> data) + 1, vec -> size * sizeof(int)); 
	free(vec);
	vec_b -> length -= 1;
	return vec_b;
}

int access_data(vectar *vec, int index) {
	
	if(index > vec -> length)
		index %= vec -> length;
	return vec -> data[index];
}

int peak(vectar *vec) {

	return vec -> data[0];
}

int main() {

	test();
	return 0;
}

void test() {

	vectar *vec = create_vectar();
	push(vec, 10);
	if(vec -> data[vec -> length - 1] != 10) {
		printf("push test 1 failed\n");
		exit(1);
	}	else {
		printf("push test 1 passed\n");
	}
	push(vec, 20);
	if(vec -> data[vec -> length - 1] != 20) {
		printf("push test 2 failed\n");
		exit(1);
	}	else {
		printf("push test 2 passed\n");
	}
	push(vec, 30);
	if(vec -> data[vec -> length - 1] != 30) {
		printf("push test 3 failed\n");
		exit(1);
	}	else {
		printf("push test 3 passed\n");
	}
	push(vec, 40);
	if(vec -> data[vec -> length - 1] != 40) {
		printf("push test 4 failed\n");
		exit(1);
	}	else {
		printf("push test 4 passed\n");
	}
	if(access_data(vec, 14) != 30) {
		printf("circular test failed\n");
		exit(1);
	}	else {
		printf("circulare test passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> data[0] != 20) {
		printf("pop test 1 failed\n");
		exit(1);
	}	else {
		printf("pop test 1 passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> data[0] != 30) {
		printf("pop test 2 failed\n");
		exit(1);
	}	else {
		printf("pop test 2 passed\n");
	}
	if(access_data(vec, 14) != 30) {
		printf("circular test failed\n");
		exit(1);
	}	else {
		printf("circulare test passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> data[0] != 40) {
		printf("pop test 3 failed\n");
		exit(1);
	}	else {
		printf("pop test 3 passed\n");
	}
	if(peak(vec) != 40) {
		printf("peak test failed\n");
		exit(1);
	}	else {
		printf("peak test passed\n");
	}
	push(vec, 20);
	if(vec -> data[vec -> length - 1] != 20) {
		printf("push test 5 failed\n");
		exit(1);
	}	else {
		printf("push test 5 passed\n");
	}
	push(vec, 30);
	if(vec -> data[vec -> length - 1] != 30) {
		printf("push test 6 failed\n");
		exit(1);
	}	else {
		printf("push test 6 passed\n");
	}
	push(vec, 40);
	if(vec -> data[vec -> length - 1] != 40) {
		printf("push test 7 failed\n");
		exit(1);
	}	else {
		printf("push test 7 passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> data[0] != 20) {
		printf("pop test 4 failed\n");
		exit(1);
	}	else {
		printf("pop test 4 passed\n");
	}
	if(peak(vec) != 20) {
		printf("peak test failed\n");
		exit(1);
	}	else {
		printf("peak test passed\n");
	}
	printf("\nAll tests are passed\n");


}
