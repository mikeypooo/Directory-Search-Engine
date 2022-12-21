#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"







struct hashmap* hm_create(int num_buckets){
  //2113 code
  int i;
  struct hashmap * hm = malloc(sizeof(struct hashmap));
    hm->map = calloc(num_buckets, sizeof(struct llnode));
    hm->num_buckets = num_buckets;
    //fill map with null pointers using for loop
    for(i=0; i < hm->num_buckets; i++) {
        hm->map[i] = NULL;
    }
    hm->num_elements = 0; //this value changes
  return hm;
}







int hm_get(struct hashmap* hm, char* word, char* document_id){
    int counter = 0;
    int get = hash_code(hm,word);
    struct llnode* now = hm->map[get];

    //check buckets to see if matching word
    while(now->next != NULL && now != NULL){
        if(strcmp(now->word, word)==0 && strcmp(now->document_id,document_id)==0){
            counter = now->num_occurrences;
            return counter;
        }
        now = now->next;
    }

    if(strcmp(now->word, word)==0 && strcmp(now->document_id,document_id) == 0){ 
        counter = now->num_occurrences;
        return counter;
    }

    if(hm->map[get] == NULL || now == NULL){
        return -1; 
    }
    return -1;
}










void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){
    int hash_key = hash_code(hm, word); //uses hash function to get key 
    struct llnode * it = hm -> map[hash_key]; //creates new node variable if key exists 
    if(it){
        //if exact word and document id are found, the number of elements and occurrences increment 
        if (!strcmp(it->document_id,document_id) && !strcmp(it->word,word)){ 
            hm -> num_elements++; //if found increment elements 
            it -> num_occurrences++; //increment number of occurences
            return; 
        }
    }
    //add new node
    struct llnode * nnode = malloc(sizeof(struct llnode)); //allocate memory for the new added node
    nnode->word = strdup(word); //copy word from input to the new node
    nnode->document_id = strdup(document_id); //copy document id from input to the new node
    hm->map[hash_key] = nnode; 
    nnode->next = it; //set new node to the next value
    nnode->num_occurrences = num_occurrences; //set number of occurences to new node
    hm->num_elements++; //increment number of elements since there is an additional node 
}








void hm_remove(struct hashmap* hm, char* word, char* document_id){
    int hash_key = hash_code(hm, word); //uses hash function to get key 
    struct llnode * it = hm -> map[hash_key]; //creates new node variable if key exists
    struct llnode * temp; //temp variable is initialized
    if(it == NULL){
        return; //if node of linked list is null, return 
    }
    //iterates through linked list until document id and word are found 
    while(it){
        if (!strcmp(it->document_id,document_id) && !strcmp(it->word,word)){ 
            temp = it; //sets it to temp 
            it = it -> next; //unlinks the node to be deleted
            free(temp -> word); //frees word
            free(temp -> document_id); //frees document id 
            free(temp); //frees node
            hm -> num_elements--; //decrements number of elements 
            return; 
        }
        it = it -> next; //goes to next node
    }
}









void hm_destroy(struct hashmap* hm){
  // Free the memory for each node in the linked list
  for (int i = 0; i < hm->num_buckets; i++) {
    struct llnode *node = hm->map[i];
    while (node) {
      struct llnode *temp = node;
      node = node->next;
      free(temp->word);
      free(temp->document_id);
      free(temp);
    }
  }
  // Free the memory for the array of linked list nodes
  free(hm->map);

  // Free the memory for the hashmap struct itself
  free(hm);
}









int hash_code(struct hashmap* hm, char* word){
    int i = 0;
    int j;
    int sum = 0;
    int len = strlen(word);
    //iterate through each letter add sum
    while(i < len){
        sum += word[i];
        i++;
    }
    //sum % all the buckets
    j = sum % hm->num_buckets;
    return j;
}



//This function searches through the hashmap for a word
int hash_search(struct hashmap *hm, char *w, char *docID){
    //allocate space in memory
	struct llnode *nodeCheck = (struct llnode *)malloc(sizeof(struct llnode));
	nodeCheck->word = w;
	nodeCheck->document_id = docID;
	//go through all buckets
	for (int i = 0; i < hm->num_buckets; i++){
		struct llnode *curCounter = hm->map[i]; 
		while (curCounter != NULL){
			if ((strcmp(nodeCheck->word, curCounter->word) == 0) && ((strcmp(nodeCheck->document_id, curCounter->document_id) == 0)))
			{
				return curCounter->num_occurrences;
			}
			curCounter = curCounter->next;
		}
	}
	return 0;
}