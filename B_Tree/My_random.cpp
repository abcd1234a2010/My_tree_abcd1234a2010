#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "My_random.hpp"

int random_list_gen(int **random_list, int length, int rand_min, int rand_max){

    int x;
    
    srand( time(NULL) );

    *random_list=(int *)malloc(length*sizeof(int));

    for(int i=0;i<length;i++){

        x = rand();

        (*random_list)[i]=x%(rand_max-rand_min)+rand_min;

    }

}