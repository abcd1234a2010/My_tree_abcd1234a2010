#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct RBtree{

    int black_num;
    int data;
    int isroot;
    struct RBtree *left;
    struct RBtree *right;
    struct RBtree *parent;

}RBT;

void insert(int data, RBT* Tree, RBT** root);

void delete_node(int data, RBT* Tree, RBT** root);

void traversal(RBT *t);

void check_valid(RBT *t, int isroot);

void _check_valid(RBT *t,int isroot,int *black_hight,int );

void delete_node(int data, RBT* t, RBT** root);

void judge_handle(RBT* t, RBT** root);

void BBB_handle(RBT* t, RBT** root);

void BRB_handle(RBT* t, RBT** root);

void RBB_handle(RBT* t, RBT** root);

RBT* get_sibling(RBT* t);

RBT* get_near_nephew(RBT* t);

RBT* get_far_nephew(RBT* t);