# Directory-Search-Engine
This report will go through the flow process and explanation of each function for the search engine



TO RUN THE PROGRAM

in terminal write, "make" then "./main" 



FLOW AND EXPLANATION

as soon as the program starts, main.c is the first file to run which holds the main method that creates a hashmap with a number of buckets specified by the user. Then it calls training, which is pointer to the hashmap that has just been created. Training uses the populate function to populate the hashmap with all the files inside of p5 directory. It should not matter how many files are in the directory because we use glob_t. After the training function, we go back to main with the hashmap stored as the return value. From here we get a user input and using the read function thats located in the getrank.c file where we put query letters into a character array. If the user presses “X” we call hm_destroy which destroys the hashmap and frees all memory. If the user input is not  “X”, then we call the rank function which gets the tf-idf scores and sorts each file based on the inputs in query[] and the hashmap. From there we print out our results into a new file called search_scores.txt where the most relevant document will be at the top of the list and the least relevant at the bottom. After that we return back to main once more and we keep looping until the user presses “X”. After the user presses “X”, we hm_destroy again and free all da memory and destroy our hashmap.


Hashmap.c contents

struct hashmap *hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void hm_destroy(struct hashmap *hm);
void hm_remove(struct hashmap *hm, char *word, char *document_id);
int hash_code(struct hashmap *hm, char *word);
int hash_search(struct hashmap *hm, char *w, char *docID);

Training.c contents

int SearchFile(char *docID, char *word);
void populate(struct hashmap *hm, char *docID);
struct hashmap *training(struct hashmap *hm);

Getrank.c contents

void read(struct hashmap *hm);
