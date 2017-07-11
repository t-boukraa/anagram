#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>

struct word_array {
	char **data;
	size_t size;
	size_t capacity;
};

void word_array_create(struct word_array *self);

void word_array_destroy(struct word_array *self);

void word_array_add(struct word_array *self, const char *word);

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result);

void word_array_sort(struct word_array *self);

int word_array_partition(char **data, int i, int j);

void word_array_sort(struct word_array *self);

void word_array_swap(char **data, int a, int b);

void word_array_print(const struct word_array *self);

void word_array_read_file(struct word_array *self, const char *filename);

void clean_newline(char *buf, size_t size);
#endif