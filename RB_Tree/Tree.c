#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"

void traversal(RBT *t){

    if(t==NULL){

        return;

    }

    traversal(t->left);
    printf("%d %d %d %d %d\n",
    t->parent?t->parent->data:-1,
    t->data,
    t->black_num,
    t->left?t->left->data:-1,
    t->right?t->right->data:-1
    );
    traversal(t->right);

}

void init(RBT *b){

    b->right=NULL;
    b->left=NULL;
    b->parent=NULL;
    b->black_num=0;
    b->data=-1;
    b->isroot=0;

}

void rotation(RBT *up,RBT *down,RBT **t){

    if(down->left==up){

        down->left=up->right;
        
        if(up->right!=NULL){

            up->right->parent=down;
        
        }

        up->right=down;
        up->parent=down->parent;
        
        if(down->parent!=NULL){
        
            if(down->parent->left==down){

                down->parent->left=up;

            }

            else{

                down->parent->right=up;

            }

        }

        down->parent=up;   

        if(down->isroot==1){

            down->isroot=0;
            up->isroot=1;
            *t=up;

        }

    }

    if(down->right==up){

        down->right=up->left;
        
        if(up->left!=NULL){

            up->left->parent=down;
        
        }

        up->left=down;
        up->parent=down->parent;
        
        if(down->parent!=NULL){
        
            if(down->parent->right==down){

                down->parent->right=up;

            }

            else{

                down->parent->left=up;

            }

        }

        down->parent=up;   

        if(down->isroot==1){

            down->isroot=0;
            up->isroot=1;
            *t=up;

        }

    }

}

void check(RBT *b,RBT **t){

    if(!b->parent){

        return;

    }

    if(b->parent->black_num){

        return;

    }


    RBT *grandparent=b->parent->parent;

    if(grandparent==NULL){

        return;

    }

    RBT *parent=b->parent;
    RBT *uncle=(grandparent->right==parent)?grandparent->left:grandparent->right;

    if(parent->right==b){

        if(grandparent->left==parent){

            if(uncle==NULL||uncle->black_num==1){ // R\R/B\B

                rotation(b,parent,t);
                rotation(b,grandparent,t);

                b->black_num=1;
                grandparent->black_num=0;

            }

            else{ // R\R/B\R

                parent->black_num=1;
                uncle->black_num=1;
                grandparent->black_num=0;

                if(grandparent->isroot==1){

                    grandparent->black_num=1;
                    return;

                }

                check(grandparent,t);

            }

        }

        if(grandparent->right==parent){

            if(uncle==NULL||uncle->black_num==1){ // R\R\B/B

                rotation(b,parent,t);

                check(parent,t);

            }

            else{ // R\R\B/R

                parent->black_num=1;
                uncle->black_num=1;
                grandparent->black_num=0;

                if(grandparent->isroot==1){

                    grandparent->black_num=1;
                    return;

                }

                check(grandparent,t);
                
            }

        }

    }

    else if(parent->left==b){

        if(grandparent->left==parent){

            if(uncle==NULL||uncle->black_num==1){ // R\R/B\B

                rotation(b,parent,t);

                check(parent,t);

            }

            else{ // R\R/B\R

                parent->black_num=1;
                uncle->black_num=1;
                grandparent->black_num=0;

                if(grandparent->isroot==1){

                    grandparent->black_num=1;
                    return;

                }

                check(grandparent,t);

            }

        }

        if(grandparent->right==parent){

            if(uncle==NULL||uncle->black_num==1){ // R\R\B/B

                rotation(b,parent,t);
                rotation(b,grandparent,t);

                b->black_num=1;
                grandparent->black_num=0;

            }

            else{ // R\R\B/R

                parent->black_num=1;
                uncle->black_num=1;
                grandparent->black_num=0;

                if(grandparent->isroot==1){

                    grandparent->black_num=1;
                    return;

                }

                check(grandparent,t);            

            }

        }

    }

}

void insert(int a,RBT *b,RBT **t){

    if(b->data==-1){
    
        b->data=a;
    
        check(b,t);

    }

    else{

        if(b->data<a){

            if(!b->right){

                b->right=malloc(1*sizeof(RBT));
                init(b->right);
                b->right->parent=b;

            }

            insert(a,b->right,t);

        }


        if(b->data>a){

            if(!b->left){



                b->left=malloc(1*sizeof(RBT));
                init(b->left);
                b->left->parent=b;

            } 

            insert(a,b->left,t);

        }

    }

}

void delete_node(int data, RBT* t, RBT** root){

    RBT* target_node=t;
    RBT* replace_node;
    int swap_value;

    while(target_node->data!=data){

        if(data>target_node->data){

            target_node=target_node->right;

        }


        else{

            target_node=target_node->left;

        }

        if(target_node==NULL){

            return;

        }

    }

    if(target_node->left!=NULL){

        replace_node=target_node->left;

        while(replace_node->right!=NULL){

            replace_node=replace_node->right;

        }

    }

    else if(target_node->right!=NULL){

        replace_node=target_node->right;

        while(replace_node->left!=NULL){

            replace_node=replace_node->left;

        }

    }

    else{

        replace_node=target_node;

    }

    swap_value=replace_node->data;
    replace_node->data=target_node->data;
    target_node->data=swap_value;

    if(t->right==NULL&&t->left==NULL){

        if(t==*root){

        t->data=-1;
        return;

        }

    }

    if(replace_node->black_num==0){ //case 1 BR

        if(replace_node->parent->right==replace_node){

            replace_node->parent->right=NULL;

        }

        else if(replace_node->parent->left==replace_node){

            replace_node->parent->left=NULL;

        }

        free(replace_node);

        return;

    }

    else if(replace_node->right||replace_node->left){ // case 2 BB

        if(replace_node->left){

            if(replace_node->parent->right==replace_node){

                replace_node->parent->right=replace_node->left;
                replace_node->left->parent=replace_node->parent;
                replace_node->left->black_num=1;

            }

            else{

                replace_node->parent->left=replace_node->left;
                replace_node->left->parent=replace_node->parent;
                replace_node->left->black_num=1;

            }


        }


        else{

            if(replace_node->parent->right==replace_node){

                replace_node->parent->right=replace_node->right;
                replace_node->right->parent=replace_node->parent;
                replace_node->right->black_num=1;

            }

            else{

                replace_node->parent->left=replace_node->right;
                replace_node->right->parent=replace_node->parent;
                replace_node->right->black_num=1;

            }

        }


        free(replace_node);

        return;

    }

    else{
        
        judge_handle(replace_node,root);

        if(replace_node->parent->right==replace_node){

            replace_node->parent->right=NULL;

        }

        if(replace_node->parent->left==replace_node){

            replace_node->parent->left=NULL;

        }

        free(replace_node);
        return;

    }

}

void judge_handle(RBT* t, RBT** root){

    RBT* sibling=get_sibling(t);

    if(t->isroot==1){

        printf("root in judge handle\n");
        exit(-1);

    }

    else if(sibling==NULL){

        printf("no sibling\n");
        exit(-1);

    }

    if(t->parent->black_num==1&&sibling->black_num==1){ //BBB

        BBB_handle(t,root);

    }

    else if(t->parent->black_num==0&&sibling->black_num==1){ //BRB

        BRB_handle(t,root);

    }

    else if(t->parent->black_num==1&&sibling->black_num==0){ //RBB

        RBB_handle(t,root);

    }

}

void BBB_handle(RBT* t, RBT** root){

    RBT* sibling=get_sibling(t);

    if((sibling->left==NULL||sibling->left->black_num==1)&&(sibling->right==NULL||sibling->right->black_num==1)){

        sibling->black_num=0;

        if(t->parent->isroot!=1){
       
            judge_handle(t->parent,root);

        }

    }

    else{

        RBT* far_nephew=get_far_nephew(t);
        RBT* near_nephew=get_near_nephew(t);

        if(!far_nephew||far_nephew->black_num==1){

            rotation(near_nephew,sibling,root);
            near_nephew->black_num=1;
            sibling->black_num=0;
            rotation(get_sibling(t),t->parent,root);

        }

        else{
        
            rotation(sibling,t->parent,root);

        }

        t->parent->parent->black_num=1;
        get_sibling(t->parent)->black_num=1;
        
    }


}

void BRB_handle(RBT* t, RBT** root){

    RBT* sibling=get_sibling(t);
    
    if((sibling->left==NULL||sibling->left->black_num==1)&&(sibling->right==NULL||sibling->right->black_num==1)){

        sibling->black_num=0;
        t->parent->black_num=1;

    }

    else{

        RBT* far_nephew=get_far_nephew(t);
        RBT* near_nephew=get_near_nephew(t);

        if(!far_nephew||far_nephew->black_num==1){

            rotation(near_nephew,sibling,root);
            near_nephew->black_num=1;
            sibling->black_num=0;
            rotation(get_sibling(t),t->parent,root);

        }

        else{
        
            rotation(sibling,t->parent,root);

        }

        t->parent->black_num=1;
        t->parent->parent->black_num=0;
        get_sibling(t->parent)->black_num=1;
        
    }
    
}

void RBB_handle(RBT* t, RBT** root){

    RBT* sibling=get_sibling(t);
    rotation(sibling,t->parent,root);
    sibling->black_num=1;
    t->parent->black_num=0;
    t->parent->parent->black_num=1;
    BRB_handle(t,root);

}

RBT* get_sibling(RBT* t){

    if(!t->parent){

        return NULL;

    }

    if(t->parent->right==t){

        return t->parent->left;

    }

    else if(t->parent->left==t){

        return t->parent->right;

    }

}

RBT* get_near_nephew(RBT* t){

    if(get_sibling(t)==NULL){

        return NULL;

    }

    if(t->parent->right==t){

        return get_sibling(t)->right;

    }

    if(t->parent->left==t){

        return get_sibling(t)->left;

    }

}

RBT* get_far_nephew(RBT* t){

    if(get_sibling(t)==NULL){

        return NULL;

    }

    if(t->parent->right==t){

        return get_sibling(t)->left;

    }

    if(t->parent->left==t){

        return get_sibling(t)->right;

    }

}

void check_valid(RBT *t, int isroot){

    int black_hight=-1;

    _check_valid(t,isroot,&black_hight,0);

}

void _check_valid(RBT *t, int isroot,int *black_hight,int black_count){

    if(t==NULL){

        return;

    }

    if(isroot==1){
        
        if(t->black_num!=1){

            printf("%d red root\n",t->data);
            
            exit(-1);

        }

        if(t->isroot!=1){

            printf("%d not root\n",t->data);

            exit(-1);

        }

    }

    if(t->black_num==0){

        if(t->left!=NULL&&t->left->black_num==0){

            printf("%d left red collision\n",t->data);

            exit(-1);

        }

        if(t->right!=NULL&&t->right->black_num==0){

            printf("%d red collision\n",t->data);

            exit(-1);

        }

    }

    if(t->left!=NULL&&t!=t->left->parent){

        printf("%d left child error\n",t->data);

        exit(-1);

    }

    if(t->right!=NULL&&t!=t->right->parent){

        printf("%d right child error\n",t->data);

        exit(-1);

    }

    if(t->left!=NULL&&t->left->data>t->data){

        printf("%d left value error\n",t->data);

        exit(-1);

    }

    if(t->right!=NULL&&t->right->data<t->data){

        printf("%d right value error\n",t->data);

        exit(-1);

    }

    if(t->black_num==1){

        black_count++;

    }

    if(t->left==NULL){
    
        if(*black_hight==-1){

            *black_hight=black_count;

        }

        else{

            if(black_count!=*black_hight){

                printf("%d left black hight error\n",t->data);
                exit(-1);

            }

        }

    }

    if(t->right==NULL){
    
        if(*black_hight==-1){

            *black_hight=black_count;

        }

        else{

            if(black_count!=*black_hight){

                printf("%d right black hight error\n",t->data);
                exit(-1);
            
            }

        }

    }

    _check_valid(t->left,0,black_hight,black_count);
    _check_valid(t->right,0,black_hight,black_count);


} 