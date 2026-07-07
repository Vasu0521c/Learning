#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_length(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}

char* long_com_prefix(char **str, int size) {
    
    char *checker_str = str[0];
    if(size == 0)
        return checker_str;
    int shortest_length = get_length(str[0]);
    int i = 0;
    while(i < size) {
        if(shortest_length  > get_length(str[i])) {
            shortest_length = get_length(str[i]);
            checker_str     = str[i];
        }
        i++;
    }
    char *arr = malloc(sizeof(char) * shortest_length + 2);
    i = 0;
    while(i < shortest_length) {
        int j = 0;
        while(j < size) {
            if(checker_str[i] != str[j][i]) {
                break;
            }
            j++;
        }
        if(j != size) {
            break;
        }
        arr[i] = checker_str[i];
        i++;
    }
    arr[i] = '\0';
    return arr;
}

void test();

int main() {

    char *arr_of_str[] = {"flower", "flow", "flicker", "flu"};
    int size           = sizeof(arr_of_str) / sizeof(arr_of_str[0]);
    char *ser = long_com_prefix(arr_of_str, size);
    printf("%s\n\n", ser);
    test();
    return 0;
}

void test() {

    char *arr1[] = {"flower", "flow", "flight"};
    char *res1 = long_com_prefix(arr1, sizeof(arr1) / sizeof(arr1[0]));
    if (strcmp(res1, "fl") != 0) {
        printf("failed\n");
        free(res1);
        exit(1);
    }
    printf("pass\n");
    free(res1);

    char *arr2[] = {"go", "go", "go", "go", "go"};
    char *res2 = long_com_prefix(arr2, sizeof(arr2) / sizeof(arr2[0]));
    if (strcmp(res2, "go") != 0) {
        printf("failed\n");
        exit(1);
    }
    printf("pass\n");
    free(res2);

    char *arr3[] = {"abc", "abc", "abc"};
    char *res3 = long_com_prefix(arr3, sizeof(arr3) / sizeof(arr3[0]));
    if (strcmp(res3, "abc") != 0) {
        printf("failed\n");
        free(res3);
        exit(1);
    }
    printf("pass\n");
    free(res3);
}
