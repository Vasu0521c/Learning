#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node node;

struct node{
	int data;
	node *next;
} ;

typedef struct {
	node *head;
	node *tail;
	int length;
} list;


void push(int data, list *linked_list);
int pop(list *linked_list);
int compare(list *linked_list_1, list *linked_list_2);
void display(list *linked_list);
void clone(list *linked_list_1, list *linked_list_2);
void insert_at(int index, int data, list *ll);
void remove_at(int index, list *ll);
int is_circular(list *ll);
void reverse(list *ll);

void test(list *linked_list_1, list *linked_list_2);

node* newnode() {
	node *creatednode = malloc(sizeof(node));
	memset(creatednode, 0, sizeof(node));
	return creatednode;
}

void push(int data,list *linked_list) {

	node *temp = newnode();

	if(linked_list -> length == 0) {
		temp -> data        = data;
		linked_list -> head = temp;
		linked_list -> tail = temp;
	}
	else {
		temp -> data                = data;
		linked_list -> tail -> next = temp;
		linked_list -> tail         = linked_list -> tail -> next;
	}
	linked_list -> length += 1;
}

int pop(list *linked_list) {

	if(linked_list -> tail == NULL) {
		return 0;
	}
	node *tem  = linked_list -> head;
	while((tem -> next) != linked_list -> tail)
		tem = tem -> next;
	tem -> next            = NULL;
	int freed_data         = linked_list -> tail -> data;
	free(linked_list -> tail);
	linked_list -> tail    = tem;
	linked_list -> length -= 1;
	return freed_data;
}

int compare(list *linked_list_1, list *linked_list_2) {

	if((linked_list_1 -> length) != (linked_list_2 -> length)) {
		return 1;
	}
	node *temp1 = linked_list_1 -> head;
	node *temp2 = linked_list_2 -> head;
	while(temp1 != NULL && temp2 != NULL) {
		if((temp1 -> data) != (temp2 -> data)) {
			return 1;
		}
		temp1 = temp1 -> next;
		temp2 = temp2 -> next;
	}
	return 0;
}

void display(list *linked_list) {
	
	node *temp = linked_list -> head;
	while(temp -> next != NULL) {
		printf("%d -> ", temp -> data);
		temp = temp -> next;
	}
	printf("%d \n", temp -> data);

}

void clone(list *linked_list_1, list *linked_list_2) {

	int len = linked_list_1 -> length;
	while(len > 1) {
		int x = pop(linked_list_1);
		len--;
	}
	linked_list_1 -> length = linked_list_2 -> length;
	node *temp1             = newnode();
	node *temp2             = linked_list_2 -> head;
	temp1 -> data           = temp2 -> data;
	linked_list_1 -> head   = temp1;
	len                     = linked_list_2 -> length;
	temp2                   = temp2 -> next;
	while(len > 1) {
		node *temp    = newnode();
		temp -> data  = temp2 -> data;
		temp2         = temp2 -> next;
		temp1 -> next = temp;
		temp1         = temp1 -> next;
		len--;
	}
}

void insert_at(int index, int value, list *ll) {

	node *temp    = newnode();
	node *temp1   = ll -> head; 
	ll -> length += 1;
	if(index > ll -> length) {
		return;
	}
	if(index == 0) {
		temp -> data = value;
		temp -> next = ll -> head;
		ll -> head   = temp;
	}
	else if(index == ll -> length) {
		temp -> data       = value;
		ll -> tail -> next = temp;
		ll -> tail         = temp;
	}
	else {
		int len = 0;
		while(index -1 != len) {
			temp1 = temp1 -> next;
			len++;
		}
		temp -> data  = value;
		temp -> next  = temp1 -> next;
		temp1 -> next = temp;
	}
	return;
}

void remove_at(int index, list *ll) {

	if(index > ll -> length) {
		return;
	}
	else if(index == 0) {
		node *temp   = ll -> head;
		ll -> head   = ll -> head -> next;
		temp -> next = NULL;
		free(temp);
	}
	else if(index == ll -> length) {
		node *temp = ll -> head;
		while((temp -> next) != (ll -> tail)) {
			temp = temp -> next;
		}
		node *temp1  = ll -> tail;
		temp -> next = NULL;
		ll -> tail   = temp;
		free(temp1);
	}
	else {
		int len    = 0;
		node *temp = ll -> head;
		while((index -1) != (len - 1)) {
			temp = temp -> next;
			len++;
		}
		node *temp2  = temp -> next;
		temp -> next = temp -> next -> next;
		free(temp2);

	}
}

int is_circular(list *ll) {
	if(ll -> tail -> next == ll -> head)
		return 1;
	return 0;

}

void reverse(list *ll) {

	node *head       = ll -> head;
	node *empty_node = NULL;
	node *first      = head;
	node *second     = head -> next;
	while(1) {
		first -> next = empty_node;
		if((second -> next) != NULL) {
			empty_node = second -> next;
		}
		else {
			head           = second;
			second -> next = first;
			break;
		}
		second -> next = first;
		first          = empty_node;
		empty_node     = second;
		if((first -> next) != NULL) {
			second = first -> next;
		}
		else {
			head          = first;
			first -> next = empty_node;
			break;
		}

	}
	ll -> head = head;
}

node* recur(node *head) {

	if(head -> next == NULL) {
		return head;
	}
	node *temp = recur(head -> next);
	head -> next -> next = head;
	head -> next = NULL;
	return temp;

}


int main() {
	list *linked_list_1 = malloc(sizeof(list));
	list *linked_list_2 = malloc(sizeof(list));
	memset(linked_list_1, 0, sizeof(list));
	memset(linked_list_2, 0, sizeof(list));
	int i = 10;
	while(i < 50) {
		push(i, linked_list_1);
		push(i, linked_list_2);
		i += 10;
	}
	push(12, linked_list_1);
	test(linked_list_1, linked_list_2);
	return 0;
}

void test(list *linked_list_1, list *linked_list_2) {

	if(pop(linked_list_1) != 12) {
		printf("pop failed\n");
		exit(1);
	}	else {
		printf("pop succeded\n");
	}
	if(compare(linked_list_1, linked_list_2) == 1) {
		printf("push failed\n");
		exit(1);
	}	else {
		printf("push passed\n");
	}
	clone(linked_list_1, linked_list_2);
	if(compare(linked_list_1, linked_list_2) == 1) {
		printf("clone failed\n");
		exit(1);
	}	else {
		printf("clone succeded\n");
	}
	insert_at(0, 15, linked_list_1);

	insert_at(0, 15, linked_list_1);
	insert_at(0, 1115, linked_list_1);
	insert_at(5, 615, linked_list_1);
	insert_at(4, 415, linked_list_1);
	insert_at(9, 115, linked_list_1);
	display(linked_list_1);
	remove_at(0, linked_list_1);
	remove_at(7, linked_list_1);
	remove_at(5, linked_list_1);
	remove_at(5, linked_list_1);
	remove_at(3, linked_list_1);
	display(linked_list_1);
	if(is_circular(linked_list_1) == 1) {
		printf("circular function failed\n");
		exit(1);
	}
	else {
		printf("circular function passed\n");
	}
	reverse(linked_list_1);
	display(linked_list_1);
	linked_list_1 -> head = recur(linked_list_1 -> head);
	
	
	display(linked_list_1);
}

