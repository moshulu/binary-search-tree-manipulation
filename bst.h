#include <stdio.h>
#include <stdlib.h>
#define length(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
typedef int boolean;

typedef struct {
    int key;
    int value;
} Data;

typedef struct node {
    Data info;
    struct node * left;
    struct node * right;
} Tree;
