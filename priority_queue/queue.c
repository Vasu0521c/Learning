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
	memcpy(vec_b -> que, (vec -> que) + 1, (vec -> size - 1) * sizeof(queue)); 
	free(vec);
	vec_b -> length -= 1;
	return vec_b;
}

int peak(vectar *vec) {

	return vec -> que[0].data;
}

int main() {

	test();
	return 0;
}

void test() {

	vectar *vec = malloc(sizeof(vectar));
	push(vec, 10, 2);
	if(vec -> que[vec -> length - 1].data != 10) {
		printf("push test 1 failed\n");
		exit(1);
	}	else {
		printf("push test 1 passed\n");
	}
	push(vec, 20, 1);
	if(vec -> que[vec -> length - 1].data != 10) {
		printf("push test 2 failed\n");
		exit(1);
	}	else {
		printf("push test 2 passed\n");
	}
	push(vec, 30, 4);
	if(vec -> que[vec -> length - 1].data != 30) {
		printf("push test 3 failed\n");
		exit(1);
	}	else {
		printf("push test 3 passed\n");
	}
	push(vec, 40, 3);
	if(vec -> que[vec -> length - 1].data != 30) {
		printf("push test 4 failed\n");
		exit(1);
	}	else {
		printf("push test 4 passed\n");
	}
	display(vec);
	vec = queue_pop(vec);
	if(vec -> que[0].data != 10) {
		printf("pop test 1 failed\n");
		exit(1);
	}	else {
		printf("pop test 1 passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> que[0].data != 40) {
		printf("pop test 2 failed\n");
		exit(1);
	}	else {
		printf("pop test 2 passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> que[0].data != 30) {
		printf("pop test 3 failed\n");
		exit(1);
	}	else {
		printf("pop test 3 passed\n");
	}
	if(peak(vec) != 30) {
		printf("peak test failed\n");
		exit(1);
	}	else {
		printf("peak test passed\n");
	}
	push(vec, 50, 1);
	if(vec -> que[vec -> length - 1].data != 30) {
		printf("push test 5 failed\n");
		exit(1);
	}	else {
		printf("push test 5 passed\n");
	}
	push(vec, 60, 2);
	if(vec -> que[vec -> length - 1].data != 30) {
		printf("push test 6 failed\n");
		exit(1);
	}	else {
		printf("push test 6 passed\n");
	}
	push(vec, 70, 3);
	if(vec -> que[vec -> length - 1].data != 30) {
		printf("push test 7 failed\n");
		exit(1);
	}	else {
		printf("push test 7 passed\n");
	}
	vec = queue_pop(vec);
	if(vec -> que[0].data != 60) {
		printf("pop test 4 failed\n");
		exit(1);
	}	else {
		printf("pop test 4 passed\n");
	}
	if(peak(vec) != 60) {
		printf("peak test failed\n");
		exit(1);
	}	else {
		printf("peak test passed\n");
	}
	printf("\nAll tests are passed\n");


}
