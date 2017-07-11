#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>

struct word_dict_bucket {
	const char *word;
	struct word_dict_bucket *next;
};

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *self, const char *word);

struct word_dict_bucket *word_dict_bucket_destroy(struct word_dict_bucket *self);

struct word_dict {
	struct word_dict_bucket **buckets;
	size_t count;
	size_t size;
};

void word_dict_create(struct word_dict *self);

void word_dict_destroy(struct word_dict *self);

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array);

size_t fnv_hash(const char *key);

void word_dict_rehash(struct word_dict *self);

void word_dict_add(struct word_dict *self, const char *word);

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result);

void print_bucket(struct word_dict_bucket *p);

void word_array_search_anagram_wildcard(const struct word_array *self, const char *word, struct word_array *result);

struct word_dict_bucket *destroy_word(struct word_dict_bucket *self,const char *word);

#endif
