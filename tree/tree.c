#include<stdio.h>
#include<stdlib.h>

#include "vector.h"

void test();

node* create_tree() {

	node *new_tree = malloc(sizeof(node));
	new_tree -> value     = 0;
	new_tree -> sibling   = NULL;
	new_tree -> child     = NULL;
	return new_tree;
}

void insert_as_child(node *tree, int data) {

	node *root = tree;
	if(root -> value == 0) {
		root -> value = data;
		return;
	}
	while(root -> child != NULL) {
		root = root -> child;
	}
	node *newnode    = create_tree();
	newnode -> value = data;
	root -> child    = newnode;
	return;
}

void insert_as_sibling(node *tree, int data) {

	node *root = tree;
	while(root -> sibling != NULL) {
		root = root -> sibling;
	}
	node *newnode    = create_tree();
	newnode -> value = data;
	root -> sibling  = newnode;
	return;
}

vectar* breadth_first_search(node *tree) {

	vectar *que  = create_vectar();
	node *root   = tree;
	push(que, root);
	while(que -> length > 0) {
		node current_node = que -> nodes[0];
		printf("%d ", current_node.value);
		pop(que);
		node *child_node = current_node.child;
		while(child_node != NULL) {
			push(que, child_node);
			child_node = child_node -> sibling;
		}
	}
}

int is_right(node *tree) {

	int i, j;
	i = j = 0;
	node *current_node = tree;
	while(i < 47) {
		if(current_node -> value %2 != 0) {
			return 0;
		}
		current_node = current_node -> child;
		i++;
	}
	return 1;
}

int is_left(node *tree) {

	int j = 0;
	node *current_node = tree -> child -> sibling;
	while(j < 47) {
		if(current_node -> value %2 == 0) {
			return 0;
		}
		current_node = current_node -> sibling;
		j++;
	}
	return 1;
}

int main() {

	test();
	return 0;
}

void test() {
	
	node *tree = create_tree();
	insert_as_child(tree, 2);
	if(tree -> value !=  2) {
		printf("Insert test 1 failed\n");
		exit(1);
	}	else {
		printf("Insert test 1 passed\n");
	}
	insert_as_child(tree, 4);
	if(tree -> child -> value != 4) {
		printf("Insert test 2 failed\n");
		exit(1);
	}	else {
		printf("Insert test 2 passed\n");
	}
	insert_as_sibling(tree -> child, 5);
	if(tree -> child -> sibling -> value != 5) {
		printf("Insert test 3 failed\n");
		exit(1);
	}	else {
		printf("Insert test 3 passed\n");
	}
	insert_as_sibling(tree -> child, 7);
	if(tree -> child -> sibling -> sibling -> value != 7) {
		printf("Insert test 4 failed\n");
		exit(1);
	}	else {
		printf("Insert test 4 passed\n");
	}
	int i = 10;
	while(i < 100) {
		if(i %2 == 0) {
			insert_as_child(tree, i);
		}
		else {
			insert_as_sibling(tree -> child, i);
		}
		i++;
	}
	if(is_left(tree) != 1 && is_right(tree) != 1) {
		printf("insertion failed\n");
		exit(1);
	}	else {
		printf("insertion passed\n");
	}

//	print_values(tree);
}

