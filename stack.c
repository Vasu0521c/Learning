#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

int* extend_array(int* stack) {

}

void test(int *stack);
int* push(int value, int *stack);

int* push(int value, int *stack) {

	if(stack != NULL) {
		stack++;
	}

	return stack;
}

void display(int *stack) {

	while(stack != NULL) {
		printf("%d, ", *stack);
		stack--;
	}
	return;
}


int main() {
	test(stack);
	return 0;
}

void test() {

	int stack[10] = {};
	stack = push(10, stack);
	if(stack != 10) {
		printf("stack push failed\n");
		exit(1);
	}	else {
	printf("push test 1 passed\n");
	}
	stack = push(0, stack);
	if(stack != 0) {
		printf("push test 2 failed\n");
		exit(1);
	}	else {
		printf("push test 2 passed\n");
	}
	stack = push(1, stack);
	if(stack != 1) {
		printf("push test 3 failed\n");
		exit(1);
	}	else {
		printf("push test 3 passed\n");
	}
	display(stack);

}
