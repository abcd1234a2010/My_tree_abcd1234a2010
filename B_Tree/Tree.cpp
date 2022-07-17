#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.hpp"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

void traversal(BT *t){

    int j=1;
    queue<BT*> q;
    q.push(t);
    t->traversal_id=0;

    while(q.size()>0){
        
        int i;
        BT* head=q.front();
        q.pop();

        print_node(head);

        for(i=0;i<head->childlist.size();i++){

            q.push(head->childlist[i]);
            head->childlist[i]->traversal_id=j;
            j++;           

        }

    }

}

void init(BT *b, int degree,bool isroot,bool isleaf){

    b->degree=degree;
    b->isroot=isroot;
    b->isleaf=isleaf;
    b->parent=NULL;

}

void print_node(BT *t){

    int parent_id;
    int i;

    if(t->parent==NULL){

        parent_id=-1;

    }

    else{

        parent_id=t->parent->traversal_id;

    }

    printf("%d %d %d %d\n",t->traversal_id,t->isroot,t->isleaf,parent_id);

    for(i=0;i<=t->keylist.size();i++){

        printf("%d ",t->keylist[i]);

    }

    printf("\n");

    for(i=0;i<t->childlist.size();i++){

        printf("%d ",t->childlist[i]->traversal_id);

    }

    printf("\n");

}

void check(BT *b,BT **t){



}

void insert(int a,BT *b,BT **t){

    int index;
    vector<int>::iterator it_i;
    
    for(it_i=b->keylist.begin(); it_i!=b->keylist.end(); ++it_i){

        if(*it_i>a){

            break;

        }
        
    }

    index=it_i-b->keylist.begin();

    if(b->isleaf==0){

        insert(a,b->childlist[index],t);

    }

    else{

        b->keylist.insert(b->keylist.begin()+index,a);

        if(b->keylist.size()>=b->degree*2-1){

            split_child(b,t);

        }

    }

}

void split_child(BT* t, BT** root){

    if(t->isroot==1){

        BT* right;
        int i,j;

        t->parent=(BT*)malloc(sizeof(BT));
        init(t->parent,t->degree,1,0);
        t->parent->keylist.push_back(t->keylist[t->degree-1]);
        t->parent->childlist.push_back(t);
        t->PCrelation=0;

        right=(BT*)malloc(sizeof(BT));
        init(right,t->degree,0,t->isleaf);
        t->parent->childlist.push_back(right);
        right->PCrelation=1;
        right->parent=t->parent;

        for(i=t->degree;i<=t->degree*2-1;i++){

            right->keylist.push_back(t->keylist[i]);

        }

        t->keylist.resize(t->degree-1);

        if(t->isleaf==0){

            for(i=t->degree,j=0;i<=t->degree*2-1;i++,j++){

                right->childlist.push_back(t->childlist[i]);
                right->childlist[j]->PCrelation=j;
                right->childlist[j]->parent=right;

            }

            t->childlist.resize(t->degree);

        }

    }

   else{
      
        BT* right;
        int i,j;

        t->parent->keylist.insert(t->keylist.begin()+t->PCrelation-1,t->keylist[t->degree-1]);
        
        right=(BT*)malloc(sizeof(BT));
        init(right,t->degree,0,t->isleaf);
        t->parent->childlist.insert(t->parent->childlist.begin()+t->PCrelation+1,right);
        right->PCrelation=t->PCrelation+1;
        right->parent=t->parent;

        if(t->isleaf==0){

            for(i=t->degree,j=0;i<=t->degree*2-1;i++,j++){

                right->childlist.push_back(t->childlist[i]);
                right->childlist[j]->PCrelation=j;
                right->childlist[j]->parent=right;

            }

            t->childlist.resize(t->degree);

        }

        for(i=right->PCrelation+1;i<=t->childlist.size();i++){

            t->parent->childlist[i]->PCrelation=i;

        }

    }

}

void check_valid(BT *t, int isroot){


}

void _check_valid(BT *t, int isroot,int *black_hight,int black_count){


}
