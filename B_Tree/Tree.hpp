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
    int traversal_high;

}BT;

void insert(int data, BT* Tree, BT** root);

void delete_node(int data, BT* Tree, BT** root);

void traversal(BT *t);

void print_node(BT *t);

void check_valid(BT *root);

void check_valid_2(BT *now_node, bool need_root, bool need_leaf);

void split_child(BT* t, BT** root);

void init(BT *b, int degree,bool isroot,bool isleaf);

void handle_short(BT *b,BT **t);

void borrow(BT* from,BT* to,BT** t);

void merge(BT* left,BT* right,BT** t);

