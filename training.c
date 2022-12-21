#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glob.h>
#include "hashmap.h"



//This function searches through the File for a word
int SearchFile(char *docID, char *word){
  int numOccurrences = 0;


  // Open the file for reading
  FILE *file = fopen(docID, "r");
  if (file == NULL)
  {
    // Handle error
    printf("Error: unable to open file '%s'\n", docID);
    return 0;
  }

  // Read each line of the file
  char line[256];
  while (fgets(line, sizeof(line), file))
  {
    // Split the line into words
    char *token = strtok(line, " ");
    while (token != NULL)
    {
      // Check if the current word matches the search word
      if (strcmp(token, word) == 0){
        numOccurrences++;
      }
      // Move to the next word
      token = strtok(NULL, " ");
    }
  }

  // Close the file
  fclose(file);

  return numOccurrences;
}





// This function populates hashmap with a certain document
void populate(struct hashmap *hm, char *docID){
    FILE *fptr;
    int len = 200;
    char temp[len];
    fptr = fopen(docID, "r");
    int p = 1; //itterator

    //if file DNE
    if (fptr == NULL){
        printf("ERROR!\n");
        return;
    }

    //READ EACH LINE
    int m;
    while (fgets(temp, len, fptr) != NULL){
        for (m = 0; m < len; m++){
            if (temp[m] == '\n'){
                temp[m + 0] = '\0';
            }
        }
        char delim[] = " ";
        //to go word by word
        char *wordByWord = strtok(temp, delim);
        while (wordByWord != NULL){
            char *word = strdup(wordByWord);
            if (wordByWord != NULL){
                strcpy(word, wordByWord);
                hm_put(hm, word, docID, 1);
            }
            wordByWord = strtok(NULL, delim);
        }
        p++;
        memset(temp, 0, sizeof temp);
    }
    //Close the file
    fclose(fptr);
}





//This function uses populate to populate hashmap with all files
struct hashmap *training(struct hashmap *hm){
    glob_t val;
    char *directory = "p5docs/*.txt";
    glob(directory, 0, NULL, &val);
    int numFiles;
    numFiles = (int)val.gl_pathc;
    // Loop through the file paths and populate the hashmap
    for (int i = 0; i < numFiles; i++) {
        populate(hm, val.gl_pathv[i]);
    }
    return hm;
    
}