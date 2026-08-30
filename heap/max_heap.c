#include <stdio.h>
#include <stdlib.h>
#include "/home/darkking/Projects/custom_header_files/C_headers/intVector.h"

void test();

void heap_up(vectar *heap, int index) {

    while(index > 0) {

        int parent = (index - 1) / 2;

        if(heap -> data[parent] >= heap -> data[index]) {
            break;
        }

        int temp = heap -> data[parent];
        heap -> data[parent] = heap -> data[index];
        heap -> data[index]  = temp;

        index = parent;
    }

    return;
}

void heap_down(vectar *heap, int index) {

    while(1) {

        int left  = (2 * index) + 1;
        int right = (2 * index) + 2;

        int largest = index;

        if(left < heap -> length &&
           heap -> data[left] > heap -> data[largest]) {

            largest = left;
        }

        if(right < heap -> length &&
           heap -> data[right] > heap -> data[largest]) {

            largest = right;
        }

        if(largest == index) {
            break;
        }

        int temp = heap -> data[index];
        heap -> data[index]   = heap -> data[largest];
        heap -> data[largest] = temp;

        index = largest;
    }

    return;
}

void insert(vectar *heap, int data) {

    push(heap, data);
    heap_up(heap, heap -> length - 1);

    return;
}

int peek(vectar *heap) {

    if(heap -> length == 0) {
        return 0;
    }

    return heap -> data[0];
}

int heap_pop_first(vectar *heap) {

    if(heap -> length == 0) {
        return 0;
    }

    int value = heap -> data[0];

    heap -> length--;

    if(heap -> length == 0) {
        return value;
    }

    heap -> data[0] = heap -> data[heap -> length];

    heap_down(heap, 0);

    return value;
}

void display_heap(vectar *heap) {

    display(heap);

    return;
}

int main() {

    test();
    return 0;
}

void test() {

    vectar *vec = new_vectar();
    insert(vec, 15);

    if(vec -> data[0] != 15) {
        printf("Test 1 insertion failed\n");
        exit(1);
    }
    else {
        printf("Test 1 insertion passed\n");
    }

    insert(vec, 10);
    /* if(vec -> data[0] != 15) { */
    /*     printf("Test 2 insertion failed\n"); */
    /*     exit(1); */
    /* } */
    /* else { */
    /*     printf("Test 2 insertion passed\n"); */
    /* } */

    insert(vec, 20);
    /* if(vec -> data[0] != 15) { */
    /*     printf("Test 3 insertion failed\n"); */
    /*     exit(1); */
    /* } */
    /* else { */
    /*     printf("Test 3 insertion passed\n"); */
    /* } */

    insert(vec, 50);
    /* if(vec -> data[0] != 15) { */
    /*     printf("Test 4 insertion failed\n"); */
    /*     exit(1); */
    /* } */
    /* else { */
    /*     printf("Test 4 insertion passed\n"); */
    /* } */

    insert(vec, 30);
    /* if(vec -> data[0] != 15) { */
    /*     printf("Test 5 insertion failed\n"); */
    /*     exit(1); */
    /* } */
    /* else { */
    /*     printf("Test 5 insertion passed\n"); */
    /* } */
    display_heap(vec);
    printf("\n");
}
