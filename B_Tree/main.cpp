#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "My_random.hpp"
#include "Tree.hpp"

#define DEFAULT_DEGREE 2

int main(int argc, char* argv[]) {

    int count = 0;
    int length=10;
    BT *Tree;
    int i;
    int *random_list;

    Tree=(BT*)malloc(sizeof(BT));

    init(Tree,DEFAULT_DEGREE,true,true);

#ifdef DEBUG1

    length=10;

#elif defined DEBUG2
    
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

    int tmp[10]={156,112,13,157,13,183,46,22,197,120};
    int true_length=length;
    random_list=(int*)malloc(length*sizeof(int));
    for(int i=0;i<length;i++){

        random_list[i]=tmp[i];

    }
#elif defined DEBUG2

    int true_length = random_list_gen(&random_list,  length, 0, 300000);

#else

    int true_length = random_list_gen(&random_list,  length, 0, 200);

#endif

    for(i=0;i<true_length;i++){

        printf("%d ",random_list[i]);

    }
    
    printf("\n");

    for(i=0;i<true_length;i++){

        insert(random_list[i],Tree,&Tree);
        check_valid(Tree);
        traversal(Tree);
        printf("=================\n");

    }

    //traversal(Tree);

// #ifdef DEBUG1

//     delete_node(5, Tree, &Tree);    
//     check_valid(Tree,1);
//     traversal(Tree);
//     printf("=================\n");
//     delete_node(6, Tree, &Tree);    
//     check_valid(Tree,1);
//     traversal(Tree);
//     printf("=================\n");
//     delete_node(7, Tree, &Tree);   
//     check_valid(Tree,1);
//     traversal(Tree);
//     printf("=================\n"); 
//     delete_node(8, Tree, &Tree);
//     check_valid(Tree,1);
//     traversal(Tree);
//     printf("=================\n");  
//     delete_node(9, Tree, &Tree);
//     check_valid(Tree,1);
//     traversal(Tree);
//     printf("=================\n");    

// #elif defined DEBUG2

    // for(i=0;i<true_length;i++){

    //     delete_node(random_list[i],Tree,&Tree);
    //     check_valid(Tree,1);
    //         traversal(Tree);
    // printf("=================\n");    

    // }

// #endif

}