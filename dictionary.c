#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "array.h"
#include "dictionary.h"
#define FNV_OFFSET_BASIS_32 2166136261
#define FNV_OFFSET_BASIS_64 14695981039346656037
#define FNV_PRIME_32 16777619
#define FNV_PRIME_64 1099511628211
//#define DEBUG

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *self, const char *word) {
	struct word_dict_bucket *new_bucket = calloc(1, sizeof(struct word_dict_bucket));
	new_bucket->word = word;
	if (self == NULL) {
		new_bucket->next = NULL;
	}
	else {
		new_bucket->next = self;
	}
	return new_bucket;
}

struct word_dict_bucket *word_dict_bucket_destroy(struct word_dict_bucket *self) {
	struct word_dict_bucket *prev;
	while (self != NULL) {
		prev = self;
		self = self->next;
#if defined DEBUG
		printf("\nSuppressed %s", prev->word);
#endif
		free(prev);
	}
	self = NULL;
	return self;
}

void word_dict_create(struct word_dict *self) {
	self->count = 0;
	self->size = 10000;
	self->buckets=calloc(self->size, sizeof(struct word_dict_bucket));
#if defined DEBUG
	printf("\nDictionary created:\n size= %zu, count=%zu", self->size, self->count);
#endif
}

void word_dict_destroy(struct word_dict *self) {
	for (size_t i=0; i<self->size; i++){
		self->buckets[i] = word_dict_bucket_destroy(self->buckets[i]);
	}
	free(self->buckets);
#if defined DEBUG
	printf("\n\n [Operation = destroy dictionary]\nDictionary destroyed\n");
#endif
}

size_t fnv_hash(const char *key) {
	size_t hash= FNV_OFFSET_BASIS_32;
	char *cpy = string_duplicate(key);
	string_sort_letters(cpy);
	for (size_t i=0; i<strlen(cpy); i++){
		hash = hash ^ cpy[i];
		hash = hash * FNV_PRIME_32;
	}
	free(cpy);
	return hash;
}

void word_dict_rehash(struct word_dict *self){
#if defined DEBUG
	printf("\n[Operation = rehash]");
#endif
	self->size *=2;
#if defined DEBUG
	printf("New size= %zu", self->size);
#endif
	struct word_dict_bucket **tmp=self->buckets;
	tmp = realloc(self->buckets, self->size * sizeof(struct word_dict_bucket));
	if (tmp == NULL) {
		fprintf(stderr, "Error: realloc failed");
		exit(EXIT_FAILURE);
	}
	else {
		self->buckets = tmp;
	}
	for(size_t i=0; i < self->size;i++){
#if defined DEBUG
		printf("  i= %zu", i);
#endif
		struct word_dict_bucket *wdb = self->buckets[i];
		if (wdb != NULL){
			while (wdb != NULL){
				size_t indice = fnv_hash(wdb->word) % self-> size;
				if (i != indice) {
					self->buckets[indice] = word_dict_bucket_add(self->buckets[indice], wdb->word);
#if defined DEBUG
					printf("\nprevious index: %zu; new index: %zu; word: %s", i, indice, wdb->word);
#endif
					self->buckets[i] = destroy_word(self->buckets[i], wdb->word);
				}
				wdb = wdb->next;
			}
		}
	}
#if defined DEBUG
	printf("\nDictionary rehashed with size=%zu\n", self->size);
#endif
}

void word_dict_add(struct word_dict *self, const char *word){
	if (((double) self->count / (double) self->size) > 0.5){
		word_dict_rehash(self);
	}
	size_t index = fnv_hash(word) % self->size;
	self->buckets[index] = word_dict_bucket_add(self->buckets[index], word);
	self->count++;
#if defined DEBUG
	printf("\nindex: %zu", index);
	printf("  Added %s\n", word);
	print_bucket(self->buckets[index]);
#endif
}

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array) {
	for (size_t i = 0; i < array->size; i++) {
		word_dict_add(self, array->data[i]);
	}
}

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result) {
	struct word_dict_bucket *curr_anagram = self->buckets[fnv_hash(word)%self->size];
	if (curr_anagram == NULL) {
#if defined DEBUG
		printf("\nNo anagram found\n");
#endif
	}
	else {
		while (curr_anagram != NULL) {
			if (string_are_anagrams(curr_anagram->word, word)) {
				word_array_add(result, curr_anagram->word);
			}
			curr_anagram = curr_anagram->next;
		}
	}
}

void print_bucket(struct word_dict_bucket *p){
	struct word_dict_bucket *cure =p;
	while (cure != NULL) {
		printf("%s > ", cure->word);
		cure = cure->next;
	}
	printf("NULL\n");
}


struct word_dict_bucket *destroy_word(struct word_dict_bucket *self,const char *word){
	struct word_dict_bucket *head = NULL;
	struct word_dict_bucket *prev = NULL;
	struct word_dict_bucket *curr = NULL;
	struct word_dict_bucket *next = NULL;
	for (curr = self; curr != NULL; curr = curr->next){
		next = curr->next;
		if (curr->word == word){
			free(curr);
			if (prev != NULL){
				prev->next = next;
			}
		} else{
			prev = curr;
			if (head == NULL){
				head = curr;
			}
		}
	}
	return head;
}

