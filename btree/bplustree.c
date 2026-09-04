#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {

    int          key,
                 order;

    struct Node *child,
                 *sibling,
                 *next;
};

Node* new_node();
Node* find_leaf(Node *root, int value);
Node* get_element(Node *root, int value);

void insert_as_sibling(Node *page, int value);
void insert_child(Node *page, int value, Node *child);
void split_page(Node *page, Node **right, int *separator);
void split_root(Node *root, Node *right);
Node* copy_page(Node *page);
void free_entries(Node *node);

int get_child_count(Node *node);
int contains(Node *root, int value);
int insert_recursive(Node *page, int value, Node **right, int *separator);

void insert_value(Node *root, int value);
void print_tree(Node *root, int level);
void print_leaves(Node *root);
void free_tree(Node *root);
void test();

Node* new_node() {

    Node *newnode = malloc(sizeof(Node));

    if (newnode == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    newnode -> key     = 0;
    newnode -> order   = 0;
    newnode -> child   = NULL;
    newnode -> sibling = NULL;
    newnode -> next    = NULL;

    return newnode;
}

int get_child_count(Node *node) {

    int length = 0;

    while (node != NULL) {
        length++;
        node = node -> sibling;
    }

    return length;
}

void insert_as_sibling(Node *page, int value) {

    Node *current = page;
    Node *newnode = new_node();

    if (value < current -> key) {
        newnode -> key     = current -> key;
        newnode -> sibling = current -> sibling;
        current -> key     = value;
        current -> sibling = newnode;
    } else {
        newnode -> key = value;

        while (current -> sibling != NULL &&
            current -> sibling -> key < value)
            current = current -> sibling;

        newnode -> sibling = current -> sibling;
        current -> sibling = newnode;
    }

    page -> order++;
}

void insert_child(Node *page, int value, Node *child) {

    Node *current = page;
    Node *newnode = new_node();

    newnode -> key   = value;
    newnode -> child = child;

    if (value < current -> key) {
        newnode -> key     = current -> key;
        newnode -> child   = current -> child;
        current -> key     = value;
        current -> child   = child;
        newnode -> sibling = current -> sibling;
        current -> sibling = newnode;
    } else {
        while (current -> sibling != NULL &&
            current -> sibling -> key < value)
            current = current -> sibling;

        newnode -> sibling = current -> sibling;
        current -> sibling = newnode;
    }

    page -> order++;
}

Node* find_leaf(Node *root, int value) {

    Node *current = root;

    while (current -> child != NULL) {
        while (current -> sibling != NULL &&
            current -> sibling -> key <= value)
            current = current -> sibling;

        current = current -> child;
    }

    return current;
}

Node* get_element(Node *root, int value) {

    Node *current = find_leaf(root, value);

    while (current != NULL && current -> key <= value) {
        if (current -> key == value)
            return current;

        current = current -> sibling;
    }

    return NULL;
}

int contains(Node *root, int value) {

    return get_element(root, value) != NULL;
}

void split_page(Node *page, Node **right, int *separator) {

    Node *current = page;
    int left_count = (3 + 1) / 2;
    int i;

    for (i = 1; i < left_count; i++)
        current = current -> sibling;

    *right = current -> sibling;
    current -> sibling = NULL;

    (*right) -> order = 3 + 1 - left_count;
    page -> order = left_count;
    *separator = (*right) -> key;

    if (page -> child == NULL) {
        (*right) -> next = page -> next;
        page -> next = *right;
    }
}

Node* copy_page(Node *page) {

    Node *copy = new_node();
    Node *current = page;
    Node *tail = copy;

    copy -> key   = page -> key;
    copy -> order = page -> order;
    copy -> child = page -> child;

    while (current -> sibling != NULL) {
        current = current -> sibling;
        tail -> sibling = new_node();
        tail = tail -> sibling;
        tail -> key   = current -> key;
        tail -> child = current -> child;
    }

    return copy;
}

void free_entries(Node *node) {

    Node *current = node;
    Node *next;

    while (current != NULL) {
        next = current -> sibling;
        free(current);
        current = next;
    }
}

void split_root(Node *root, Node *right) {

    Node *left = copy_page(root);
    Node *old = root -> sibling;
    Node *newroot = new_node();

    if (left -> child == NULL)
        left -> next = right;

    root -> key     = left -> key;
    root -> order   = 2;
    root -> child   = left;
    root -> sibling = newroot;
    root -> next    = NULL;

    newroot -> key   = right -> key;
    newroot -> order = 1;
    newroot -> child = right;

    free_entries(old);
}

int insert_recursive(Node *page, int value, Node **right, int *separator) {

    Node *entry;

    if (page -> child == NULL) {
        insert_as_sibling(page, value);

        if (page -> order <= 3)
            return 0;

        split_page(page, right, separator);
        return 1;
    }

    entry = page;

    while (entry -> sibling != NULL &&
        entry -> sibling -> key <= value)
        entry = entry -> sibling;

    if (!insert_recursive(entry -> child, value, right, separator))
        entry -> key = entry -> child -> key;
    else {
        entry -> key = entry -> child -> key;
        insert_child(page, *separator, *right);
    }

    if (page -> order <= 3)
        return 0;

    split_page(page, right, separator);
    return 1;
}

void insert_value(Node *root, int value) {

    Node *right;
    int separator;

    if (root -> order == 0) {
        root -> key = value;
        root -> order = 1;
        return;
    }

    if (contains(root, value))
        return;

    if (insert_recursive(root, value, &right, &separator))
        split_root(root, right);
}

void print_tree(Node *root, int level) {

    Node *current = root;

    while (current != NULL) {
        printf("%*s%d\n", level * 4, "", current -> key);

        if (current -> child != NULL)
            print_tree(current -> child, level + 1);

        current = current -> sibling;
    }
}

void print_leaves(Node *root) {

    Node *leaf = find_leaf(root, root -> key);

    while (leaf != NULL) {
        Node *next = leaf -> next;
        Node *current = leaf;

        printf("[");

        while (current != NULL) {
            printf("%d ", current -> key);
            current = current -> sibling;
        }

        printf("] ");
        leaf = next;
    }

    printf("\n");
}

void free_tree(Node *root) {

    Node *current = root;
    Node *next;

    while (current != NULL) {
        next = current -> sibling;

        if (current -> child != NULL)
            free_tree(current -> child);

        free(current);
        current = next;
    }
}

void test() {

    Node *btree = new_node();
    int values[] = {
        10, 8, 18, 20, 5,
        15, 3, 12, 25, 7,
        2, 30, 6, 11, 22
    };
    int expected[] = {
        2, 3, 5, 6, 7,
        8, 10, 11, 12, 15,
        18, 20, 22, 25, 30
    };
    Node *current;
    int i;

    for (i = 0; i < 15; i++) {
        insert_value(btree, values[i]);

        if (!get_element(btree, values[i])) {
            printf("Node insertion test %d failed\n", i + 1);
            free_tree(btree);
            return;
        }

        printf("Node insertion test %d passed\n", i + 1);
    }

    current = find_leaf(btree, expected[0]);
    i = 0;

    while (current != NULL) {
        Node *next = current -> next;

        while (current != NULL) {
            if (i == 15 || current -> key != expected[i]) {
                printf("Leaf test failed\n");
                free_tree(btree);
                return;
            }

            i++;
            current = current -> sibling;
        }

        current = next;
    }

    if (i != 15) {
        printf("Leaf test failed\n");
        free_tree(btree);
        return;
    }

    printf("Leaf test passed\n");
    print_leaves(btree);
    free_tree(btree);
}

int main() {

    test();
    return 0;
}
