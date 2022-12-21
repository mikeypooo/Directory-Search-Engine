#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.h"

int main(void){
    int num_buckets;

    printf("How many buckets?\n");
    scanf("%d", &num_buckets);
    int numberbucket = num_buckets;
    struct hashmap *hm = hm_create(numberbucket);

    //go to training
    training(hm);

    char last = '\0';
    char tempo[100];
    scanf("%c", tempo);

    //loops while the latest inputed char is not capital X, keep reading to hm
    while (last != 'X'){
        read(hm);
        printf("\nPress <enter> to continue - Press X to exit:\n");
        scanf("%c", &last);
        if (last == 'X'){
            hm_destroy(hm);
            exit(0);
        }
    }
    return 0;
    
}