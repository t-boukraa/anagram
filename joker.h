#ifndef JOKER_H
#define JOKER_H
#include "array.h"
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WILDCARDS_MAX 4


struct wildcard {
	size_t count;
	size_t index[WILDCARDS_MAX];
};


void wildcard_create(struct wildcard *self);

void wildcard_search(struct wildcard *self, const char *word);

void word_array_search_anagram_wildcard(const struct word_array *self, const char *word, struct word_array *result);

/* return 1 if the string s has, at least, the same number of each letters src*/
size_t string_number_of_different_letters_wildcard(char *s, char *src);

size_t is_anagram_wildcard(char *input, char *word);

void word_dict_search_anagram_wildcard(const struct word_dict *self, const char *word, struct word_array *result);

void word_dict_internal_loop(char *str, char *c, char *cpy, struct word_dict *self, struct word_array *result);
#endif
