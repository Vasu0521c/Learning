#include<stdio.h>
#include<stdlib.h>

int compare(int *arr_a, int l_a, int *arr_b, int l_b) {

    if (l_a != l_b)
        return 0;

    for(int i = 0; i < l_a; i++)
        if(arr_a[i] != arr_b[i])
            return 0;

    return 1;
}

int* find_product(int *arr, int length) {

    int *result    = malloc(sizeof(int) * length);
    int i          = 0;
    int multiplier = 1;

    while (i < length) {
        result[i]   = multiplier;
        multiplier *= arr[i];
        i++;
    }

    multiplier = 1;
    i--;
    
    while (i >= 0) {
        result[i]  *= multiplier;
        multiplier *= arr[i];
        i--;
    }

    return result;
}

void test();

int main() {

    test();
    return 0;
}

void test() {
    int input1[] = {1, 2, 3, 4};
    int expected1[] = {24, 12, 8, 6};
    int *res1 = find_product(input1, 4);
    if (res1 != NULL && compare(res1, 4, expected1, 4)) printf("Test 1 Passed\n");
    else printf("Test 1 Failed\n");
    free(res1);

    int input2[] = {-1, 1, 0, -3, 3};
    int expected2[] = {0, 0, 9, 0, 0};
    int *res2 = find_product(input2, 5);
    if (res2 != NULL && compare(res2, 5, expected2, 5)) printf("Test 2 Passed\n");
    else printf("Test 2 Failed\n");
    free(res2);

    int input3[] = {0, 4, 0, 5};
    int expected3[] = {0, 0, 0, 0};
    int *res3 = find_product(input3, 4);
    if (res3 != NULL && compare(res3, 4, expected3, 4)) printf("Test 3 Passed\n");
    else printf("Test 3 Failed\n");
    free(res3);

    int input4[] = {7, 3};
    int expected4[] = {3, 7};
    int *res4 = find_product(input4, 2);
    if (res4 != NULL && compare(res4, 2, expected4, 2)) printf("Test 4 Passed\n");
    else printf("Test 4 Failed\n");
    free(res4);

    int input5[] = {-2, 3, -4, 2};
    int expected5[] = {-24, 16, -12, 24};
    int *res5 = find_product(input5, 4);
    if (res5 != NULL && compare(res5, 4, expected5, 4)) printf("Test 5 Passed\n");
    else printf("Test 5 Failed\n");
    free(res5);
}
