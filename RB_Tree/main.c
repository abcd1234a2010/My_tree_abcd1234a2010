#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "My_random.h"
#include "Tree.h"

int main(int argc, char* argv[]) {

    int count = 0;
    int length= 0;
    RBT *Tree;
    int i;
    int *random_list;

    Tree=malloc(sizeof(RBT));

    Tree->black_num=1;
    Tree->data=-1;
    Tree->left=NULL;
    Tree->right=NULL;
    Tree->parent=NULL;
    Tree->isroot=1;

#ifdef DEBUG1

    length=10;

#elif defined DEBUG2||defined DEBUG3
    
    while (count < argc) {

        if (strcmp(argv[count], "-n") == 0) {

            length=atoi(argv[count+1]);

        }

        count++;

    }

#else

    while (count < argc) {

        if (strcmp(argv[count], "-n") == 0) {

            length=atoi(argv[count+1]);

        }

        count++;

    }

#endif

#ifdef DEBUG1

    int tmp[10]={1,5,2,8,9,7,6,3,4,10};
    int true_length=length;
    random_list=(int*)malloc(length*sizeof(int));
    for(int i=0;i<length;i++){

        random_list[i]=tmp[i];

    }
#elif defined DEBUG2

    int true_length = random_list_gen(&random_list,  length, 0, 500);

#elif defined DEBUG3

    length=20;
    int tmp[20]={169,388,344,381,362,396,60,171,59,180,221,33,253,174,89,8,499,3,226,201};
    int true_length=length;
    random_list=(int*)malloc(length*sizeof(int));
    for(int i=0;i<length;i++){

        random_list[i]=tmp[i];

    }

#else

    int true_length = random_list_gen(&random_list,  length, 0, 300000);

#endif

    for(i=0;i<true_length;i++){

        insert(random_list[i],Tree,&Tree);
        check_valid(Tree,1);
    //    traversal(Tree);
    //    printf("=================\n");

    }

    //traversal(Tree);

#ifdef DEBUG1

    delete_node(5, Tree, &Tree);    
    check_valid(Tree,1);
    traversal(Tree);
    printf("=================\n");
    delete_node(6, Tree, &Tree);    
    check_valid(Tree,1);
    traversal(Tree);
    printf("=================\n");
    delete_node(7, Tree, &Tree);   
    check_valid(Tree,1);
    traversal(Tree);
    printf("=================\n"); 
    delete_node(8, Tree, &Tree);
    check_valid(Tree,1);
    traversal(Tree);
    printf("=================\n");  
    delete_node(9, Tree, &Tree);
    check_valid(Tree,1);
    traversal(Tree);
    printf("=================\n");    

#elif defined DEBUG2||defined DEBUG3

    //for(i=0;i<true_length;i++){

      //  printf("%d,",random_list[i]);  

    //}

    //printf("\n");

    //traversal(Tree);
    //printf("=================\n");
    
    for(i=0;i<true_length;i++){

        delete_node(random_list[i],Tree,&Tree);
        check_valid(Tree,1);
        //traversal(Tree);
    //printf("=================\n");    

    }

#endif

}