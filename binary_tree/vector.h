#ifndef VECTOR_H
#define VECTOR_H
typedef struct node node;

struct node{
	int value;
	node *parent;
	node *left;
	node *right;
};

typedef struct {
	node *nodes;
	int length;
	int size;
} vectar;


vectar* create_vectar();
vectar* create_vectar_with_size(int size);
void pop(vectar *vec);
void stack_pop(vectar *vec);
void push(vectar *vec, node *nodes);

#endif
