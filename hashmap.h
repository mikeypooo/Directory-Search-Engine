#ifndef HASHMAP_H
#define HASHMAP_H

struct llnode
{
        char *word;          //KEY
        char *document_id;   //KEY
        int num_occurrences; //VALUE
        struct llnode *next;
};

struct hashmap
{
        struct llnode **map;
        int num_buckets;
        int num_elements;
};
//hashmap.c
struct hashmap *hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void hm_destroy(struct hashmap *hm);
void hm_remove(struct hashmap *hm, char *word, char *document_id);
int hash_code(struct hashmap *hm, char *word);
int hash_search(struct hashmap *hm, char *w, char *docID);
//training.c
int SearchFile(char *docID, char *word);
void populate(struct hashmap *hm, char *docID);
struct hashmap *training(struct hashmap *hm);
//getrank.c
void read(struct hashmap *hm);
void rank(struct hashmap *hm, char *query);


#endif