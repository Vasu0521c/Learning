#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node node;

struct node{

	int data;
	node *next;
	node *previous;
};

typedef struct {

	node *head;
	node *tail;
	int size;
} d_list;

void test();
void push(d_list *dll, int data);
void pop(d_list *dll);
int  compare(d_list *dll_a, d_list *dll_b);
void insert_at(d_list *dll, int index, int data);
void remove_at(d_list *dll, int index);
d_list* clone(d_list *dll);
d_list* reverse(d_list *dll);
int value_at(d_list *dll, int index);

node* create_node() {
	
	node *created_node = malloc(sizeof(node));
	memset(created_node, 0, sizeof(node));
	return created_node;
}

d_list* create_list() {

	d_list *created_list = malloc(sizeof(d_list));
	memset(created_list, 0, sizeof(d_list));
	return created_list; 
}

int compare(d_list *dll_a, d_list *dll_b) {

	if((dll_a -> size) != (dll_b -> size)) {
		return 0;
	}
	node *temp_a = dll_a -> head;
	node *temp_b = dll_b -> head;
	while(temp_a != NULL) {
		if(temp_a -> data != temp_b -> data)
			return 0;
		temp_a = temp_a -> next;
		temp_b = temp_b -> next;
	}
	return 1;
}

int rever_compare(d_list *dll_a, d_list *dll_b) {

	if((dll_a -> size) != (dll_b -> size)) {
		return 0;
	}
	node *temp_a = dll_a -> tail;
	node *temp_b = dll_b -> head;
	while(temp_a != NULL) {
		if((temp_a -> data) != (temp_b -> data)) 
			return 0;
		temp_a = temp_a -> previous;
		temp_b = temp_b -> next;
	}
	return 1;

}

void push(d_list *dll, int data) {

	if(dll -> head == NULL) {
		dll -> head             = create_node();
		dll -> head -> data     = data;
		dll -> head -> previous = NULL;
		dll -> tail             = dll -> head;
		dll -> size             = 1;
		return;
	}
	dll -> size += 1;
	node *temp          = create_node();
	temp -> data        = data;
	dll -> tail -> next = temp;
	temp -> next        = NULL;
	temp -> previous    = dll -> tail;
	dll -> tail         = temp;
	return;

}

void pop(d_list *dll) {

	node *temp_a   = dll -> tail;
	node *temp_b   = dll -> tail -> previous;
	temp_b -> next = NULL;
	dll -> tail    = temp_b;
	dll -> size   -= 1;
	free(temp_a);
	return;
}

void insert_at(d_list *dll, int index, int data) {

	if(index > (dll -> size)) {
		return;
	}
	node *temp   = create_node();
	temp -> data = data;
	if(index == 0) {
		if(dll -> head == NULL) {
			dll -> head = temp;
			dll -> tail = temp;
			dll -> size = 1;
			return;
		}
		temp -> next            = dll -> head;
		dll -> head -> previous = temp;
		dll -> head             = temp;
		dll -> size += 1;
		return;
	}
	if(index == (dll -> size)) {
		dll -> tail -> next = temp;
		temp -> previous    = dll -> tail;
		dll -> tail         = temp;
		dll -> size += 1;
		return;
	}
	node *itera = dll -> head;
	int i = 0;
	while(i != index) {
		itera = itera -> next;
		i++;
	}
	temp -> previous         = itera -> previous;
	temp -> next             = itera;
	temp -> previous -> next = temp;
	dll -> size             += 1;
	return;

}

void remove_at(d_list *dll, int index) {

	if((dll -> size) <= 0)
		return;
	if(index > (dll -> size)) {
		return;
	}
	if(index == 0) {
		node *temp               = dll -> head;
		dll -> head              = temp -> next;
		temp -> next -> previous = NULL;
		dll -> size             -= 1;
		free(temp);
		return;
	}
	if(index == (dll -> size)) {
		node *temp               = dll -> tail;
		temp -> previous -> next = NULL;
		dll -> tail              = temp -> previous;
		dll -> size             -= 1;
		free(temp);
		return;
	}
	node *itera = dll -> head;
	int i = 0;
	while(i != index) {
		itera = itera -> next;
		i++;
	}
	itera -> previous -> next = itera -> next;
	itera -> next -> previous = itera -> previous;
	dll -> size              -= 1;
	free(itera);
	return;
}

d_list* clone(d_list *dll) {

	d_list *cloned_dll = create_list();
	cloned_dll -> head = create_node();
	cloned_dll -> tail = cloned_dll -> head;
	cloned_dll -> size = dll -> size;
	node *temp         = dll -> head;
	while(temp -> next != NULL) {
		node *newnode              = create_node();
		cloned_dll -> tail -> data = temp -> data;
		cloned_dll -> tail -> next = newnode;
		newnode -> previous        = cloned_dll -> tail;
		cloned_dll -> tail         = cloned_dll -> tail -> next;
		temp                       = temp -> next;
	}
	cloned_dll -> tail -> data = temp -> data;
	return cloned_dll;
}

d_list* reverse(d_list *dll) {

	d_list *reversed_dll = create_list();
	reversed_dll -> head = create_node();
	reversed_dll -> tail = reversed_dll -> head;
	reversed_dll -> size = dll -> size;
	node *temp           = dll -> tail;
	while(temp -> previous != NULL) {
		node *newnode                = create_node();
		reversed_dll -> tail -> data = temp -> data;
		reversed_dll -> tail -> next = newnode;
		newnode -> previous          = reversed_dll -> tail;
		reversed_dll -> tail         = reversed_dll -> tail -> next;
		temp = temp -> previous;
	}
	reversed_dll -> tail -> data = temp -> data;
	return reversed_dll;
}

void display(d_list *dll) {

	if(dll -> head == NULL) {
		return;
	}
	node *temp = dll -> head;
	while(temp -> next != NULL) {
		printf("%d -> ", temp -> data);
		temp = temp -> next;
	}
	printf("%d\n", temp -> data);
	return;
}


int value_at(d_list *dll, int index) {

	if(index > (dll -> size)) 
		return 1;
	node *temp = dll -> head;
	int i = 0;
	while(i != index) {
		temp = temp -> next;
		i++;
	}
	return temp -> data;
}

int main() {

	test();
	return 0;
}

void test() {

	d_list *dll_a = create_list();
	d_list *dll_b = create_list();
	push(dll_a, 10);
	push(dll_b, 10);
	if(compare(dll_a, dll_b) != 1) {
		printf("push test 1 failed\n");
		exit(1);
	}	else {
		printf("push test 1 passed\n");
	}
	push(dll_a, 20);
	push(dll_b, 20);
	if(compare(dll_a, dll_b) != 1) {
		printf("push test 2 failed\n");
		exit(1);
	}	else {
		printf("push test 2 passed\n");
	}
	push(dll_a, 30);
	push(dll_b, 30);
	if(compare(dll_a, dll_b) != 1) {
		printf("push test 3 failed\n");
		exit(1);
	}	else {
		printf("push test 3 passed\n");
	}
	push(dll_a, 40);
	push(dll_b, 40);
	if(compare(dll_a, dll_b) != 1) {
		printf("push test 4 failed\n");
		exit(1);
	}	else {
		printf("push test 4 passed\n");
	}
	push(dll_a, 50);
	push(dll_b, 50);
	if(compare(dll_a, dll_b) != 1) {
		printf("push test 5 failed\n");
		exit(1);
	}	else {
		printf("push test 5 passed\n");
	}
	
	pop(dll_a);
	int i = 10;
	node *temp = dll_a -> head;
	while(i < 50) {
		if(temp -> data != i) {
			printf("pop test 1 failed\n");
			exit(1);
		}
		temp = temp -> next;
		i += 10;
	}
	printf("pop test 1 passed\n");
	pop(dll_a);
	i = 10;
	temp = dll_a -> head;
	while(i < 40) {
		if(temp -> data != i) {
			printf("pop test 2 failed\n");
			exit(1);
		}
		temp = temp -> next;
		i += 10;
	}
	printf("pop test 2 passed\n");

	insert_at(dll_a, 0, 0);
	if(value_at(dll_a, 0) != 0) {
		printf("inseert test failed\n");
		exit(1);
	}	else {
		printf("insert test 1 passed\n");
	}

	insert_at(dll_a, 0, 2);
	if(value_at(dll_a, 0) != 2) {
		printf("inseert test 2 failed\n");
		exit(1);
	}	else {
		printf("insert test 2 passed\n");
	}
	insert_at(dll_a, 5, 55);
	if(value_at(dll_a, 5) != 55) {
		printf("inseert test 3 failed\n");
		exit(1);
	}	else {
		printf("insert test 3 passed\n");
	}
	insert_at(dll_a, 51, 55);
	if(value_at(dll_a, 51) != 1) {
		printf("inseert test 4 failed\n");
		exit(1);
	}	else {
		printf("insert test 4 passed\n");
	}

	remove_at(dll_a, 0);
	if(value_at(dll_a, 0) == 2) {
		printf("rempve test 1 failed\n");
		exit(1);
	}	else {
		printf("remove teste 1 passed\n");
	}

	remove_at(dll_a, 5);
	if(value_at(dll_a, 5) != 1) {
		printf("rempve test 2 failed\n");
		exit(1);
	}	else {
		printf("remove teste 2 passed\n");
	}

	remove_at(dll_a, 0);
	if(value_at(dll_a, 0) == 0) {
		printf("rempve test 3 failed\n");
		exit(1);
	}	else {
		printf("remove teste 3 passed\n");
	}
	i = 100;
	while(i < 150) {
		push(dll_a, i);
		i += 10;
	}

	d_list *dll_c = reverse(dll_a);
	if(rever_compare(dll_c, dll_a) != 1) {
		printf("reverse test 1 failed\n");
		exit(1);
	}	else {
		printf("reverse test 1 passed\n");
	}
	dll_c = reverse(dll_c);
	if(compare(dll_a, dll_c) != 1) {
		printf("reverse test 2 failed\n");
		exit(1);
	}	else {
		printf("reverse test 2 passed\n");
	}

	d_list *dll_d = clone(dll_a);
	if(compare(dll_a, dll_c) != 1) {
		printf("clone test 1 failed\n");
		exit(1);
	}	else {
		printf("clone test 1 passed\n");
	}

	return;
}
