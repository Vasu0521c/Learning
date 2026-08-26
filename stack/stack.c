#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void test();

int peak(vectar* vec) {

	return vec -> data[vec -> length - 1];
}

int main() {
	
	test();
	return 0;
}

void test() {

	vectar *vec_b = create_vectar();
	push(vec_b, 10);
	if((vec_b -> data[vec_b -> length - 1]) != 10) {
		printf("push test 1 failed\n");
		exit(1);
	}	else {
		printf("push test 1 passed\n");
	}
	push(vec_b, 20);
	if((vec_b -> data[vec_b -> length - 1]) != 20) {
		printf("push test 2 failed\n");
		exit(1);
	}	else {
		printf("push test 2 passed\n");
	}
	push(vec_b, 30);
	if((vec_b -> data[vec_b -> length - 1]) != 30) {
		printf("push test 3 failed\n");
		exit(1);
	}	else {
		printf("push test 3 passed\n");
	}
	push(vec_b, 40);
	if((vec_b -> data[vec_b -> length - 1]) != 40) {
		printf("push test 4 failed\n");
		exit(1);
	}	else {
		printf("push test 4 passed\n");
	}

	int leng = vec_b -> length;
	pop(vec_b);
	if(vec_b -> length == leng && (vec_b -> data[vec_b -> length] == 40)) {
		printf("pop test 1 failed\n");
		exit(1);
	}	else {
		printf("pop test 1 passed\n");
	}
	if(peak(vec_b) != 30) {
		printf("peak test 1 failed\n");
		exit(1);
	}	else {
		printf("peak test 1 passed\n");
	}

	pop(vec_b);
	if(vec_b -> length == leng && (vec_b -> data[vec_b -> length] == 30)) {
		printf("pop test 2 failed\n");
		exit(1);
	}	else {
		printf("pop test 2 passed\n");
	}
	 
	if(peak(vec_b) != 20) {
		printf("peak test 2 failed\n");
		exit(1);
	}	else {
		printf("peak test 2 passed\n");
	}
	if(peak(vec_b) != 10) {
		printf("peak test 2 failed\n");
		exit(1);
	}	else {
		printf("peak test 2 passed\n");
	}
}

