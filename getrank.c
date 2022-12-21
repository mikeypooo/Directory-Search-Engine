#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glob.h>
#include "hashmap.h"

//This function reads the user input query and then calls rank 
void read(struct hashmap *hm){
    int len = 100;
    char query[len];
    printf("Enter the search string or X to exit:\n");
    fgets(query, len, stdin);
    if (query[0] == 'X'){
        hm_destroy(hm);
        exit(0);
    }
    printf("QUERY: %s\n", query);
    rank(hm, query);
}





//this function reads through each directory and compares the tf-idf values of each user inputed word and determines word significance
void rank(struct hashmap *hm, char *query){
    int size;
    glob_t val;
    char *directory = "p5docs/*.txt";
    glob(directory, 0, NULL, &val);
    const int numFiles = (int)val.gl_pathc-1;

    printf("Searching %d files...\n\n", numFiles);
    int len = 100;
    char delimiter[] = " ";

    for (int i = 0; i < len ; i++){

        if (query[i] == '\n'){
            query[i + 0] = '\0';
            query[i + 1] = '\n';
        }
    }

    int searchCounts[numFiles][len];
    int notFound = 0;



    //num of occurence counter
    for (int i = 0; i < numFiles; i++){
        int counter = 0;
        char *editable = strdup(query);
        char *wordByWord = strtok(editable, delimiter);
        while (wordByWord != NULL){
            char *word = strdup(wordByWord);
            if (wordByWord != NULL){
                strcpy(word, wordByWord);
                searchCounts[i][counter] = hash_search(hm, word, val.gl_pathv[i]);
                if (searchCounts[i][counter] != 0)
                {
                    notFound++;
                }
                counter++;
            }
            wordByWord = strtok(NULL, delimiter);
        }
        searchCounts[i][counter] = -1;
        size = counter;
    }




    //when no words are found
    if (notFound == 0)
    {
        printf("No file is relevant.\n");
        return;
    }

    int docNumFound = 0;



    //idf val
    double idf[size];
    for (int i = 0; i < size; i++){
        for (int j = 0; j < numFiles; j++){
            if (searchCounts[j][i] != 0){
                docNumFound++;
            }
        }
        if (docNumFound != 0){
            double temp = 3.0 / docNumFound;
            idf[i] = log(temp);
        }
        else{
            idf[i] = 0;
        }
        docNumFound = 0;
    }




    //get the tf-idf values
    double tfidf[numFiles][size];
    for (int i = 0; i < size; i++){
        for (int j = 0; j < numFiles; j++){
            tfidf[j][i] = searchCounts[j][i] * idf[i];
            //printf("tf-idf: %.3f\n",tfidf[j][i] );
        }
    }


    //zeroing out the sorted array to be used
    double sort[numFiles];
    for (int i = 0; i < numFiles; i++){
        sort[i] = 0;
    }




    //sum of tfidf
    int counter = 0;
    for (int k = 0; k < numFiles; k++){
        while (counter != size){
            sort[k] = tfidf[k][counter] + sort[k];
            counter++;
        }
        counter = 0;
    }




    //save doc names to be printed
    char *docs[numFiles];
    for (int i = 0; i < numFiles; i++){
        docs[i] = val.gl_pathv[i];
    }



    //sort the ranking
    for (int i = 0; i < numFiles - 1; i++){
        for (int j = 0; j < numFiles - i - 1; j++){
            if (sort[j] > sort[j + 1]){
                //swap
                double temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
                char *temp1 = docs[j];
                docs[j] = docs[j + 1];
                docs[j + 1] = temp1;
            }
        }
    }
    


    //adding to search_scores.txt located in directory p5
    FILE *fptr;
    fptr = fopen("p5docs/search_scores.txt", "a");

    if (fptr == NULL){
        printf("ERROR!\n");
        return;
    }
    for (int i = numFiles-1; i > -1; i--){
        fprintf(fptr, "%s:%.3f\n", docs[i], sort[i]);
    }
    fclose(fptr);

}