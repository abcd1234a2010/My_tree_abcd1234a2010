#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

typedef struct Btree{

    vector <int> keylist;
    int degree;
    bool isroot;
    bool isleaf;
    vector <*struct Btree> childlist;
    struct Btree *parent;
    int PCrelation;
    int traversal_id;

}BT;

void insert(int data, BT* Tree, BT** root);

void delete_node(int data, BT* Tree, BT** root);

void traversal(BT *t);

void print_node(BT *t);

void check_valid(BT *t, int isroot);

void _check_valid(BT *t,int isroot,int *black_hight,int );