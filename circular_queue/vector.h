#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	int *data;
	int length;
	int size;
} vectar;


vectar* create_vectar();
vectar* create_vectar_with_size(int size);
void clear(vectar *vec);
void pop(vectar *vec);
void push(vectar *vec, int data);
int compare(vectar *vec_a, vectar *vec_b);
vectar* reverse(vectar *vec);
vectar* clone(vectar *vec);
void insert_at(vectar *vec, int index, int data);
void remove_at(vectar *vec, int index);
void display(vectar *vec);
void reverse_display(vectar *vec);

#endif
