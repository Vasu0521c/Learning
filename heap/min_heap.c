#include <stdio.h>
#include "/home/darkking/Projects/custom_header_files/C_headers/intVector.h"

void heap_up(vectar *heap, int index) {

    while(index > 0) {

        int parent = (index - 1) / 2;

        if(heap -> data[parent] <= heap -> data[index]) {
            break;
        }

        int temp = heap -> data[parent];
        heap -> data[parent] = heap -> data[index];
        heap -> data[index] = temp;

        index = parent;
    }

    return;
}


void heap_down(vectar *heap, int index) {

    while(1) {

        int left = (2 * index) + 1;
        int right = (2 * index) + 2;

        int smallest = index;

        if(left < heap -> length &&
           heap -> data[left] < heap -> data[smallest]) {

            smallest = left;
        }

        if(right < heap -> length &&
           heap -> data[right] < heap -> data[smallest]) {

            smallest = right;
        }

        if(smallest == index) {
            break;
        }

        int temp = heap -> data[index];
        heap -> data[index] = heap -> data[smallest];
        heap -> data[smallest] = temp;

        index = smallest;
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


int pop_first(vectar *heap) {

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

    return 0;
}

