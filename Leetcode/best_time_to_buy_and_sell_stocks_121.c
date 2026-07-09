#include<stdio.h>

void test();
int max_profits(int *arr, int length) {
    if(length <= 1)
        return 0;

    int min    = 0;
    int result = 0;
    
    for(int i = 1; i < length; i++) {
        if(arr[min] > arr[i]) {
            min = i;
        }
        else if(result < (arr[i] - arr[min])) {
            result = arr[i] - arr[min];
        }
    }
    return result;
}

int main() {

    test();
    return 0;
}

void test() {

    int tc1[] = {7, 1, 5, 3, 6, 4};
    printf("Test Case 1 (Expected 5): %d\n", max_profits(tc1, 6));

    int tc2[] = {7, 6, 4, 3, 1};
    printf("Test Case 2 (Expected 0): %d\n", max_profits(tc2, 5));

    int tc3[] = {3, 3, 3, 3, 3};
    printf("Test Case 3 (Expected 0): %d\n", max_profits(tc3, 5));

    int tc4[] = {2, 7};
    printf("Test Case 4 (Expected 5): %d\n", max_profits(tc4, 2));

    int tc5[] = {2, 5, 1, 3, 8, 1};
    printf("Test Case 5 (Expected 7): %d\n", max_profits(tc5, 6));

    return;
}
