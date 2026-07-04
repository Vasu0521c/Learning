#include<stdio.h>
#include<stdlib.h>

#include "vector.h"

void test();

node* create_tree() {

	node *newnode = malloc(sizeof(node));
	newnode -> value  = 0;
	newnode -> parent = NULL;
	newnode -> left   = NULL;
	newnode -> right  = NULL;
	return newnode;
}

void insert(node *tree, int value) {
	
	node *root = tree;
	if(root -> value == 0) {
		root -> value = value;
		return;
	}
	node *newnode   = create_tree();
	newnode -> value = value;
	while(1) {
		if((root -> value) > value) {
			if((root -> left) == NULL) {
				root -> left      = newnode; 
				newnode -> parent = root;
				return;
			}
			root = root -> left;
		}
		else {
			if((root -> right) == NULL) {
				root -> right     = newnode;
				newnode -> parent = root;
				return;
			}
			root = root -> right;
		}
	}
}

node* search(node *tree, int target) {
	
	node *root = tree;
	if(root -> value == target) {
		return root;
	}
	while(1) {
		if(root -> value < target) {
			if(root -> value == target) {
				return root;
			}
			else if((root -> right) == NULL) {
				return NULL;
			}
			root = root -> right;
		}
		else {
			if(root -> value == target) {
				return root;
			}
			else if((root -> left) == NULL) {
				return NULL;
			}
			root = root -> left;
		}
	}
}

int find_height(node *tree, int target) {

	int height    = 0;
	node *current = tree;
	while(current -> value != target) {
		if(current -> right != NULL && current -> value < target)
			current = current -> right;
		else if(current -> left != NULL && current -> value > target)
			current = current -> left;
		else
			return -1;
		height++;
	}
	return height;
}

void delete(node *tree, int target) {

	node *root   = search(tree, target);
	node *temp   = root;
	node *temp_a = root;
	if(root -> right != NULL) {
		temp_a         = root -> right;
		temp -> value  = root -> right -> value;
		temp -> parent = root -> right -> parent;
		temp -> left   = root -> right -> left;
		temp -> right  = root -> right -> right;
		free(temp_a);
		return;
	}
	else if(root -> left != NULL) {
		temp_a         = root -> left;
		temp -> value  = root -> left -> value;
		temp -> parent = root -> left -> parent;
		temp -> left   = root -> left -> left;
		temp -> right  = root -> left -> right;
		free(temp_a);
		return;
	}
	else
		root -> value = 0;
	return;
}

void pre_order(node *tree) {

	node *root    = tree;
	vectar *stack = create_vectar();
	push(stack, root);
	while((stack -> length) > 0) {
		node current = stack -> nodes[(stack -> length) - 1];
		printf("%d, ", current.value);
		stack_pop(stack);
		if(current.right != NULL) {
			push(stack, current.right);
		}
		if(current.left != NULL) {
			push(stack, current.left);
		}

	}
}

void in_order(node *tree) {

	node *current_node = tree;
	vectar *stack = create_vectar();
	push(stack, current_node);
	while(current_node -> left != NULL) {
		current_node = current_node -> left;
		push(stack, current_node);
	}
	while(stack -> length > 0) {
		node current = stack -> nodes[(stack -> length) - 1];
		node *temp   = &current;
		printf("%d, ",temp -> value);
		stack_pop(stack);
		if(temp -> right != NULL) {
			temp = temp -> right;
			push(stack, temp);
			while(temp -> left != NULL) {
				temp = temp -> left;
				push(stack, temp);
			}
		}
	}
}

void wiki_in_order(node *tree) {
	node *current_node = tree;
	vectar *stack      = create_vectar();
	while(stack -> length > 0 || current_node != NULL) {
		if(current_node != NULL) {
			push(stack, current_node);
			current_node = current_node -> left;
		}
		else {
			int temp     = stack -> nodes[(stack -> length) - 1].value;
			current_node = &stack -> nodes[(stack -> length) - 1];
			stack_pop(stack);
			printf("%d, ", temp);
			current_node = current_node -> right;
		}
	}
}

void post_order(node *tree) {

	node *current_node = tree;
	vectar *stack      = create_vectar();
	vectar *stack_b    = create_vectar();
	push(stack, current_node);
	while(stack -> length > 0) {
		node current = stack -> nodes[(stack -> length) - 1];
		stack_pop(stack);
		node *temp = &current;
		push(stack_b, temp);
		if(current.left != NULL) {
			temp = current.left;
			push(stack, temp);
		}
		if(current.right != NULL) {
			temp = current.right;
			push(stack, temp);
		}
	}
	while(stack_b -> length > 0) {
		int temp = stack_b -> nodes[(stack_b -> length) - 1].value;
		printf("%d, ",temp);
		stack_pop(stack_b);
	}
}

void wiki_post_order(node *tree) {

	node *current_node = tree;
	node last_visited;
	vectar *stack      = create_vectar();
	while(stack -> length > 0 || current_node != NULL) {
		if(current_node != NULL) {
			push(stack, current_node);
			current_node = current_node -> left;
		}
		else {
			node peak = stack -> nodes[(stack -> length) - 1];
			if(((peak.right) != NULL) && (last_visited.value != (peak.right -> value)))
				current_node = peak.right;
			else {
				printf("%d, ", peak.value);
				last_visited = stack -> nodes[(stack -> length) - 1];
				stack_pop(stack);
			}
		}
	}
}

void recursive_pre_order(node *current_node) {

	if(current_node == NULL) {
		return;
	}
	printf("%d, ", current_node -> value);
	recursive_pre_order(current_node -> left);
	recursive_pre_order(current_node -> right);
}

void recursive_in_order(node *current_node) {
	
	if(current_node == NULL) {
		return;
	}
	recursive_in_order(current_node -> left);
	printf("%d, ", current_node -> value);
	recursive_in_order(current_node -> right);

}

void recursive_post_order(node *current_node) {

	if(current_node == NULL) {
		return;
	}
	recursive_post_order(current_node -> left);
	recursive_post_order(current_node -> right);
	printf("%d, ", current_node -> value);
}

void breadth_first_search(node *tree) {

	vectar *queue = create_vectar();
	node *root    = tree;
	push(queue, root);
	while(queue -> length > 0) {
		node current = queue -> nodes[0];
		printf("%d, ", queue -> nodes[0].value);
		if(current.left != NULL) {
			node *left = current.left;
			push(queue, left);
		}
		current = queue -> nodes[0];
		if(current.right != NULL) {
			node *right = current.right;
			push(queue, right);
		}
		pop(queue);
	}
}

int minimum(node *tree) {

	if(tree == NULL)
		return 0;
	node *curr_node = tree;
	while(curr_node -> left != NULL) {
		curr_node = curr_node -> left;
	}
	return curr_node -> value;
}

int maximum(node *tree) {

	if(tree == NULL)
		return 0;
	node *curr_node = tree;
	while(curr_node -> right != NULL) {
		curr_node = curr_node -> right;
	}
	return curr_node -> value;
}

void node_count(node *tree, int nodes_count[]) {

	vectar *queue = create_vectar();
	int leafs     = 0;
	int non_leafs = 0;
	node *root    = tree;
	push(queue, root);
	while(queue -> length > 0) {
		node current = queue -> nodes[0];
		if(current.left == NULL && current.right == NULL) {
			leafs++;
		}
		else {
			non_leafs++;
		}
		if(current.left != NULL) {
			node *left = current.left;
			push(queue, left);
		}
		current = queue -> nodes[0];
		if(current.right != NULL) {
			node *right = current.right;
			push(queue, right);
		}
		pop(queue);
	}
	nodes_count[0] = leafs;
	nodes_count[1] = non_leafs;
	return;
}

int main() {

	test();
	return 0;
}

void test() {

	node *tree = create_tree();
	insert(tree, 50);
	if(tree -> value != 50) {
		printf("\ninsert test 1 failed\n");
		exit(1);
	}	else {
		printf("\ninsert test 1 passed\n");
	}
	insert(tree, 30);
	if(tree -> left -> value != 30) {
		printf("insert test 2 failed\n");
		exit(1);
	}	else {
		printf("insert test 2 passed\n");
	}
	insert(tree, 60);
	if(tree -> right -> value != 60) {
		printf("insert test 3 failed\n");
		exit(1);
	}	else {
		printf("insert test 3 passed\n");
	}
	node *temp_ptr = search(tree, 50);
	if((temp_ptr -> value) != 50) {
		printf("search test 1 failed\n");
		exit(1);
	}	else {
		printf("search test 1 passed\n");
	}
	temp_ptr = search(tree, 60);
	if((temp_ptr -> value) != 60) {
		printf("search test 2 failed\n");
		exit(1);
	}	else {
		printf("search test 2 passed\n");
	}
	temp_ptr = search(tree, 30);
	if((temp_ptr -> value) != 30) {
		printf("search test 3 failed\n");
		exit(1);
	}	else {
		printf("search test 3 passed\n");
	}
	temp_ptr = search(tree, 130);
	if(temp_ptr != NULL) {
		printf("search test 4 failed\n");
		exit(1);
	}	else {
		printf("search test 4 passed\n");
	}
/*
	delete(tree, 60);
	temp_ptr = search(tree, 60);
	if(temp_ptr != NULL) {
		printf("delete test 1 failed\n");
		exit(1);
	}	else {
		printf("delete test 1 passed\n");
	}
	delete(tree, 50);
	temp_ptr = search(tree, 50);
	if(temp_ptr != NULL) {
		printf("delete test 2 failed\n");
		exit(1);
	}	else {
		printf("delete test 2 passed\n");
	}
*/
	insert(tree, 100);
	insert(tree, 10);
	insert(tree, 40);
	insert(tree, 70);
	insert(tree, 90);
	insert(tree, 5);
	insert(tree, 15);
	insert(tree, 42);
	insert(tree, 78);
	insert(tree, 94);
	temp_ptr = search(tree, 90);
	if((temp_ptr -> value) != 90) {
		printf("search test 3 failed\n");
		exit(1);
	}	else {
		printf("search test 3 passed\n");
	}
	if(find_height(tree, 90) != 4) {
		printf("height test 1 failed\n");
		exit(1);
	}	else {
		printf("heigth test 1 passed\n");
	}

	if(find_height(tree, 10) != 2) {
		printf("height test 2 failed\n");
		exit(1);
	}	else {
		printf("heigth test 2 passed\n");
	}
	int nodes_count[2];
	node_count(tree, nodes_count);
	if(nodes_count[0] != 5) {
		printf("node count test 1 failed\n");
		exit(1);
	}	else {
		printf("node count test 1 passed\n");
	}
	if(nodes_count[1] != 8) {
		printf("node count test 2 failed\n");
		exit(1);
	}	else {
		printf("node count test 2 passed\n");
	}
	if((nodes_count[0] + nodes_count[1]) != 13) {
		printf("node count test 3 failed\n");
		exit(1);
	}	else {
		printf("node count test 3 passed\n");
	}
	if(minimum(tree) != 5) {
		printf("minimum test 1 failed\n");
		exit(1);
	}	else {
		printf("minimum test 1 passed\n");
	}
	if(maximum(tree) != 100) {
		printf("maximum test 1 failed\n");
		exit(1);
	}	else {
		printf("maximum test 1 passed\n");
	}
	printf("\nAll test are passed\n\n");
}
