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

        for(i=0;i<head->childlist.size();i++){

            q.push(head->childlist[i]);
            head->childlist[i]->traversal_id=j;
            j++;           

        }

        print_node(head);

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

    printf("traversal_id=%d isroot=%d isleaf=%d parent_id=%d\n",t->traversal_id,t->isroot,t->isleaf,parent_id);

    printf("keylist ");

    for(i=0;i<t->keylist.size();i++){

        printf("%d ",t->keylist[i]);

    }

    printf("\n");

    printf("childlist_traversal_id ");

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

    if(!b->isleaf){

        insert(a,b->childlist[index],t);

    }
    
    else{

        b->keylist.insert(b->keylist.begin()+index,a);

        if(b->keylist.size() >= b->degree*2-1){

            split_child(b,t);

        }

    }

}

void split_child(BT* t, BT** root){

    if(t->isroot==1){

        BT* right;
        int i,j;

        t->parent=(BT*)malloc(sizeof(BT));
        *root=t->parent;
        init(t->parent,t->degree,1,0);
        t->parent->keylist.push_back(t->keylist[t->degree-1]);
        t->parent->childlist.push_back(t);
        t->PCrelation=0;

        right=(BT*)malloc(sizeof(BT));
        init(right,t->degree,0,t->isleaf);
        t->parent->childlist.push_back(right);
        right->PCrelation=1;
        right->parent=t->parent;

        for(i=t->degree;i<t->degree*2-1;i++){

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

        t->parent->isroot=1;
        t->isroot=0;

    }

   else{
      
        BT* right;
        int i,j;

        if(t->PCrelation==t->parent->keylist.size()){

            t->parent->keylist.push_back(t->keylist[t->degree-1]);
        
        }

        else{

            t->parent->keylist.insert(t->parent->keylist.begin()+t->PCrelation,t->keylist[t->degree-1]);
            
        }

        right=(BT*)malloc(sizeof(BT));
        init(right,t->degree,0,t->isleaf);

        if(t->PCrelation+1==t->parent->childlist.size()){

            t->parent->childlist.push_back(right);

        }

        else{

            t->parent->childlist.insert(t->parent->childlist.begin()+t->PCrelation+1,right);
        
        }
        
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

        for(i=t->degree,j=0;i<=t->degree*2-1;i++,j++){

            right->keylist.push_back(t->keylist[i]);

        }

        t->keylist.resize(t->degree-1);
        right->keylist.resize(t->degree-1);

        for(i=right->PCrelation+1;i<=t->childlist.size();i++){

            t->parent->childlist[i]->PCrelation=i;

        }

    }

    if(t->parent->keylist.size()==t->degree*2-1){

        split_child(t->parent,root);

    }

}

void check_valid(BT *root){

    vector<pair<BT*,int>> stack;
    BT* now_node;
    int i;

    stack.push_back(make_pair(root,0));

    while(stack.size()!=0){

        pair<BT*,int> now_item=stack.back();
        now_node=now_item.first;
        int now_flag=now_item.second;

        if(now_node->childlist.size()!=0&&now_flag==0){

            stack[stack.size()-1].second=1;

            for(i=0;i<now_node->childlist.size(),i++){
            
                stack.push_back(now_node->childlist[now_node->childlist.size()-1-i]);

            }

            continue;

        }

        else{

            stack.pop_back();
            
            need_root=stack.size()==0;
            need_leaf=now_node->childlist.size()==0;

            check_valid_2(now_node,need_root,need_leaf);

        }

    }

}

void check_valid_2(BT *now_node, bool need_root, bool need_leaf){

    int i;

    if(now_node->isroot!=need_root){

        printf("isroot error\n");

    }

    if(now_node->isleaf!=need_leaf){

        printf("isleaf error\n");

    }

    if(now_node->isleaf==0&&now_node->keylist.size()+1!=now_node->childlist.size()){

        printf("keylist or childlist error\n");

    }

    for(i=0;i<now_node->childlist.size();i++){

        if(now_node->childlist[i]->PCrelation!=i){

            printf("PCrelation error when index = %d and PCrelation = %d\n",i,now_node->childlist[i]->PCrelation);

        }

    }

    for(i=0;i<now_node->keylist.size()-1;i++){

        if(now_node->keylist[i]>now_node->keylist[i+1]){

            printf("keylist sort error\n");

        }

    }


    for(i=0;i<now_node->childlist.size();i++){

        if(i==0){

            if(now_node->childlist[i]->keylist[keylist.size()-1]>now_node->keylist[i]){

                printf("head childlist value error\n");

            }
        
        }


        if(i==now_node->childlist.size()-1){

            if(now_node->childlist[i]->keylist[0]<now_node->keylist[i-1]){

                printf("tail childlist value error\n");

            }
        
        }

        if(now_node->childlist[i]->keylist[0]<now_node->keylist[i-1]&&
            now_node->childlist[i]->keylist[keylist.size()-1]>now_node->keylist[i]){

                printf("middle childlist value error\n");

        }
    
    }

}

void delete_node()