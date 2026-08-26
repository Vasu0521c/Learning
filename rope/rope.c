#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/darkking/Projects/custom_header_files/C_headers/nodeVector.h"

#define MIN_WEIGHT 10
#define MAX_LENGTH 1024

//miscellanous functions
int str_length(char *string);
int str_compare(char *str_a, char *str_b);
char *display_string(Node *rope);

//constructors functions for struct
Node *new_Node();
Node *new_rope();
char *new_string(char *string, int size);

Node *string_insertion(Node *rope, char *string);

// Test function
void test();

int str_length(char *string) {

    int length = 0;

    while(string != NULL && *string != '\0') {

        string++;
        length++;
    }

    return length;
}

int str_compare(char *str_a, char *str_b) {

    int length = str_length(str_b);

    if (str_length(str_a) != length)
        return 0;

    while (length--) {

        if(*str_a != *str_b) {
            return 0;
        }

        str_a++;
        str_b++;
    }

    return 1;
}

Node *new_Node() {

    Node *new_Node = (Node*) malloc(sizeof(Node));
    memset(new_Node, 0, sizeof(Node));
    return new_Node;
}

Node *new_rope() {

    Node *initial_rope    = new_Node();
    initial_rope -> left  = new_Node();
    initial_rope -> right = new_Node();
    return initial_rope;
}

char *new_string(char *string, int size) {

    char *new_str = malloc(size);
    memcpy(new_str, string, size);
    return new_str;
}

Node *string_insertion(Node *rope, char *string) {

    int size    = str_length(string);
    int weight  = size / 2;

    if(size % 2 == 1) {
        rope -> left -> string = new_string(string, weight + 1);
        rope -> right -> string = new_string(string + weight + 1, weight);
    }

    else {
        rope -> left -> string = new_string(string, weight);
        rope -> right -> string = new_string(string + weight, weight);
    }

    rope -> left -> weight = weight;
    rope -> right -> weight = weight;

    rope -> weight = rope -> left -> weight;

    return rope;
}

char *display_string(Node *rope) {

    char *string = malloc(MAX_LENGTH);
    int initial  = 0;
    Node temp;

    vectar *vec = new_vectar();
    push(vec, *rope);

    while (vec -> length != 0) {
        temp = pop_first(vec);

        if (temp.string != NULL) {
            int length = str_length(temp.string);
            memcpy(string + initial, temp.string, length);
            initial += length;
        }

        if (temp.left != NULL)
            push(vec, *temp.left);
        if (temp.right != NULL)
            push(vec, *temp.right);

    }
    
    return string;
}

int main() {

    test();
    return 0;
}

void test() {

    char arr[] = "hello this is a ew string for testing";

    int length = str_length(arr);

    if (length != (int)strlen(arr)) {
        printf("Length calculations is wrong  \n");
        exit(1);
    } else {
        printf("Test case 1 passed\n");
    }

    Node *rope = new_rope();
    rope = string_insertion(rope, arr);

    char *string = display_string(rope);
    printf("size  %d\n", (int)strlen(arr));

    if (!str_compare(arr, string)) {
        printf("rope ds failed\n");
        printf("Failed String : %s\n", string);
        exit(1);
    } else {
        printf("Test case 2 passed\n");
    }
    free(string);
    free(rope);

    int ar[] = {2,4,5,3};
    ar[] = {1,2,2};

    arr[] = "hello this is a new string for testing";
    rope = new_rope();
    rope = string_insertion(rope, arrb);
    string = display_string(rope);

    if (!str_compare(arrb, string)) {
        printf("rope ds failed\n");
        printf("Failed String : %s\n", string);
        exit(1);
    } else {
        printf("Test case 2 passed\n");
    }
}
