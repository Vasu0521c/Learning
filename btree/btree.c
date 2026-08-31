#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {

    int  key,
         order;

    struct Node  *child,
                 *sibling;
};

Node* new_node();
Node* insert_as_sibling(Node *start, int value);
Node* insert_as_child(Node *root, int value);
Node* find_insert_position(Node *root, int value);
Node* find_element(Node **node, int target);

void  delete_element(Node *realtive, Node *target);
void  insert_value(Node *btree, int value);
void  remove_value(Node *btree, int value);
void  test();

int   get_child_count(Node *node);

Node* new_node() {

    Node *newnode = malloc(sizeof(Node));

    if (newnode == NULL) {
        perror("Memory allocation failed, malloc() function failed\n");
        exit(1);
    }

    newnode -> child   = NULL;
    newnode -> sibling = NULL;
    newnode -> key     = 0;
    newnode -> order   = 0;
    return newnode;
}


Node* insert_as_sibling(Node *start, int value) {

    Node *current  = start;
    Node *previous = start;
    Node *newnode  = new_node();

    while (current != NULL) {

        if (current -> key < value) {
            previous = current;
            current  = current -> sibling;
            continue;
        }

        newnode -> key     = current -> key;
        newnode -> sibling = current -> sibling;
        current -> sibling  = newnode;

        return current;
    }

    previous -> sibling = newnode; 
    return newnode;
}


Node* insert_as_child(Node *node, int value) {
    
    if (node -> child != NULL) {
        return insert_as_sibling(node -> child, value);
    }

    node -> child = new_node();
    return node -> child;
}


Node* find_insert_position(Node *root, int value) {

    Node *current, *previous;
    current = root;

    while (current != NULL) {

        if (current -> key > value) {
            current = insert_as_child(current, value);
            return current;
        }

        previous = current;
        current  = current -> sibling;
    }

    previous -> sibling = new_node();
    return previous -> sibling;
}


void insert_value(Node *tree, int value) {

    Node *temp = tree;

    if (temp -> key) 
        temp = find_insert_position(temp, value);

    temp -> key = value;
}


Node* find_element(Node **node, int target) {

    Node *current = *node;
    Node *previous = current;

    while (current != NULL) {

        if (current -> key == target) {
            *node = previous;
            return current;
        }

        if (current -> key > target) {
            previous = current;
            current = current -> child;
            continue;
        }

        previous = current;
        current = current -> sibling;
    }

    return NULL;
}


int get_child_count(Node *child) {

    int length = 0;

    while (child != NULL) {
        length++;
        child = child -> sibling;
    }

    return length;
}


void delete_elelment(Node *relative, Node *target) {

    Node *current, *dummy;
    int  isChild, child_count;

    if (current -> order)
        (current -> order)--;

    if (relative -> child == target) {
        isChild = 1;
    }

    child_count = get_child_count(current);
    switch (child_count) {
        case 0:

            if (isChild) {
                relative -> child = current -> sibling;
                free(current);
                return;
            }

            relative -> sibling = current -> sibling;
            return;

        case 1:
            dummy = current -> child;
            current -> key = dummy -> key;
            free(dummy);
            current -> child = NULL;
            return;

        case 2:
            dummy = current -> child;
            current -> key = dummy -> sibling -> key;
            free(dummy -> sibling);
            dummy -> sibling = NULL;
            return;

        default:
            dummy = current->child;

            while(dummy -> sibling -> sibling != NULL)
                dummy = dummy -> sibling;

            current -> key = dummy -> sibling -> key;
            free(dummy -> sibling);
            dummy->sibling = NULL;
            return;
    }
}


void remove_value(Node *tree, int value) {

    Node *temp = tree;
    Node *target;

    if (temp -> key == value) {
        delete_element(NULL, target);
        return;
    }

    target = find_element(&temp, value);

    if (target == NULL) {
        perror("No such element exist\n");
        return;
    }

    delete_element(temp, target);
    return;
}


int main() {

    test();
    return 0;
}


void test() {

    Node *btree = new_node();

    if (btree == NULL) {
        printf("Node creation failed\n");
        exit(1);
    }

    printf("Node creation test 1 passed\n");
    
    insert_value(btree, 10);

    if (btree -> key != 10) {
        printf("Node insert_valueion test 1 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 1 passed\n");

    insert_value(btree, 8);

    if (btree -> child -> key != 8) {
        printf("Node insert_valueion test 2 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 2 passed\n");

    insert_value(btree, 18);

    if (btree -> sibling -> key != 18) {
        printf("Node insert_valueion test 3 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 3 passed\n");

    insert_value(btree, 20);

    if (btree -> sibling -> sibling -> key != 20) {
        printf("Node insert_valueion test 4 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 4 passed\n");

    insert_value(btree, 5);

    if (btree -> child -> key != 5) {
        printf("Node insert_valueion test 5 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 5 passed\n");

    insert_value(btree, 15);

    if (btree -> sibling -> child -> key != 15) {
        printf("Node insert_valueion test 6 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 6 passed\n");

    insert_value(btree, 3);

    if (btree -> child  -> key != 3) {
        printf("Node insert_valueion test 7 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 7 passed\n");

    insert_value(btree, 12);

    if (btree -> sibling -> child -> key != 12) {
        printf("Node insert_valueion test 8 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 8 passed\n");

    insert_value(btree, 25);

    if (btree -> sibling -> sibling -> sibling -> key != 25) {
        printf("Node insert_valueion test 9 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 9 passed\n");

    insert_value(btree, 7);

    if (btree -> child -> sibling -> sibling -> key != 7) {
        printf("Node insert_valueion test 10 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 10 passed\n");

    insert_value(btree, 2);

    if (btree -> child -> key != 2) {
        printf("Node insert_valueion test 11 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 11 passed\n");

    insert_value(btree, 30);

    if (btree -> sibling -> sibling -> sibling -> sibling -> key != 30) {
        printf("Node insert_valueion test 12 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 12 passed\n");

    insert_value(btree, 6);

    if (btree -> child -> sibling -> sibling -> sibling -> key != 6) {
        printf("Node insert_valueion test 13 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 13 passed\n");

    insert_value(btree, 11);

    if (btree -> sibling -> child -> key != 11) {
        printf("Node insert_valueion test 14 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 14 passed\n");

    insert_value(btree, 22);

    if (btree -> sibling -> sibling -> sibling -> child -> key != 22) {
        printf("Node insert_valueion test 15 failed\n");
        exit(1);
    }

    printf("Node insert_valueion test 15 passed\n");
}
