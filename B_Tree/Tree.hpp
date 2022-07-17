#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

typedef struct Btree{

    vector <int> keylist;
    int degree;
    bool isroot;
    bool isleaf;
    vector <struct Btree*> childlist;
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

void split_child(BT* t, BT** root);

void init(BT *b, int degree,bool isroot,bool isleaf);