#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

//====================================================================================================//

// Structures

struct Node{

    char   chr;
    Node  *child;
    Node  *sibling;
};


//====================================================================================================//

// Functions Forward Declaraitions //

Node* new_node();
Node* find_sibling(Node *node, char target);
Node* find_char(Node *node, char target);
Node* get_last_child(Node *node);
Node* get_last_sibling(Node *node);
Node* assign_char(Node *node, char value);

char* append_char(char *chr, char c);

int  string_exist(Node *node, char *input);

void insert(Node *Trie_root, char *input);
void display(Node *Trie_root);
void test();


//====================================================================================================//

// Constructors //

Node* new_node() {

    Node *new_node      = malloc(sizeof(Node));
    new_node -> child   = NULL;
    new_node -> sibling = NULL;
    new_node -> chr     = '\0';
    return new_node;
}


//=====================================================================================================//

// Main Operations //

void insert(Node *Trie_root, char *input) {

    Node *temp, *dummy;
    int  length, cond_decider;
    char *str  = input;
    temp = Trie_root;
    length = strlen(input);

    while (length--) {

        dummy = find_char(temp, str[0]);

        if (dummy == NULL) {
            temp = assign_char(temp, str[0]);
            str++;
            continue;
        }

        cond_decider = string_exist(dummy, str);
        switch (cond_decider) {
            case 0:
                temp = assign_char(temp, str[0]);
                str++;
                continue;
            case -1:
                if (temp -> child == NULL)
                    temp -> child = dummy;
                return;
            default: {

                if (temp -> child == NULL) {
                    if(temp != dummy)
                        temp -> child = dummy;
                    else {
                        temp = assign_char(temp, str[0]);
                        str++;
                        continue;
                    }
                }

                int temp_length = (int)strlen(str);
                temp = get_last_child(dummy);
                str += temp_length - cond_decider;
                length -= temp_length - cond_decider - 1;
            }
        }
    }
}


//======================================================================================================//

// Main Funcion //
 
int main() {

    test();
    return 0;
}


//=======================================================================================================//

// Helping Functions //


Node *assign_char(Node *node, char value) {

    if (node -> child != NULL) {
        node = get_last_sibling(node -> child);
        node -> sibling = new_node();
        node = node -> sibling;
    } else {
        node -> child = new_node();
        node = node -> child;
    }

    node -> chr = value;
    return node;
}


Node* find_char(Node *node, char target) {

    Node *temp = node;
    Node *dummy;

    if (temp -> chr == target) {
        return node;
    }

    while (temp != NULL) {
        dummy = find_sibling(temp, target);

        if(dummy != NULL)
            return dummy;

        temp = temp -> child;
    }

    return NULL;
}


Node* find_sibling(Node *child, char target) {

    Node *temp      = child;
    int temp_length = 0;

    while (temp != NULL) {

        if(temp -> chr == target) {
            return temp;
        }

        temp = temp -> sibling;
    }
    return NULL;
}


int string_exist(Node *node, char *input) {

    char *temp = input;
    int length = strlen(input);

    while (node != NULL && length--) {

        if (node -> chr != *temp) {
            return 0;
        }

        temp++;
        node = node -> child;
    }

    if (!length) {
        return -1;
    }

    return length;
}


void display(Node *Trie_root) {

    Node *temp = Trie_root;

    while (temp != NULL) {

        if (temp -> sibling) {
            display(temp -> sibling);
        }

        printf("%c\n", temp -> chr);
        temp = temp -> child;
    }

}


Node* get_last_child(Node *node) {

    while (node -> child != NULL) {
        node = node -> child;
    }

    return node;
}


Node* get_last_sibling(Node *node) {

    while (node -> sibling != NULL) {
        node = node -> sibling;
    }

    return node;
}

//==========================================================================================================//

// Testing Functions //
 
void test() {

    Node *trie = new_node();
    char input_a[6] = "hello";
    char input_b[7] = "ehello";
    char input_c[7] = "hello2";
    char input_d[8] = "somehow";
    char input_e[5] = "some";
    insert(trie, input_a);
    insert(trie, input_b);
    insert(trie, input_c);
    insert(trie, input_d);
    insert(trie, input_e);
    display(trie);
}
