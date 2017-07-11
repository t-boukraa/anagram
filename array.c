#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "array.h"
#include <assert.h>
const size_t A = 2;
#define WORD_LETTERS_MAX 32
//#define DEBUG

void word_array_create(struct word_array *self) {
	self->capacity = 10;
	self->size = 0;
	self->data = calloc(self->capacity,sizeof(char *));
	if (self->data == NULL) {
		fprintf(stderr, "Error: calloc function failed\n");
		exit(EXIT_FAILURE);
	}
}

void word_array_destroy(struct word_array *self) {
	for (size_t i=0; i<self->size; i++){
		free(self->data[i]);
		self->data[i]=NULL;
	}
	self->data = NULL;
	self->size = 0;
	free(self->data);
#if defined DEBUG
	printf("\nArray destroyed\n");
#endif
}

void word_array_add(struct word_array *self, const char *word) {
	if(self->size == self->capacity){
		self->capacity *= A;
#if defined DEBUG
		printf("\nCapacity has been increased to %zu\n", self->capacity);
#endif
		char **data = calloc(self->capacity, sizeof(char *));
		if (data == NULL) {
			fprintf(stderr, "Error: calloc function failed\n");
			exit(EXIT_FAILURE);
	}
		memcpy(data, self->data, self->size * sizeof(char *));
		free(self->data);
		self->data = data;
	}
	char *cpy = string_duplicate(word);
	self->data[self->size] = cpy;
#if defined DEBUG
	printf("Operation = add\n%s has been successfully added in [%zu]\n", self->data[self->size], self->size);
#endif
	self->size++;
//	free(cpy);
}

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result) {
	const struct word_array *p = self;
	size_t i = 0;
#if defined DEBUG
	printf("\nOperation = search\n");
#endif
	while (p->data[i] != NULL) {
		if (string_are_anagrams(p->data[i], word)) {
			word_array_add(result, p->data[i]);
#if defined DEBUG
			printf("Anagram of %s found: %s\n",word, p->data[i]);
#endif
		}
		i++;
	}
	if (result->size == 0){
		printf("No anagram of %s found\n", word);
	}
}

void word_array_quicksort_partial(char **data, int i, int j) {
	if (i < j) {
		int p = word_array_partition(data, i, j);
		word_array_quicksort_partial(data, i, p - 1);
		word_array_quicksort_partial(data, p + 1, j);
	}
}

void word_array_swap(char **data, int a, int b) {
	char *tmp = data[a];
	data[a] = data[b];
	data[b] = tmp;
#if defined DEBUG
	printf("Operation = swap\nSwapped %s with %s\n", data[a], data[b]);
#endif
}

void word_array_sort(struct word_array *self) {
	word_array_quicksort_partial(self->data, 0, self->size-1);
}

int word_array_partition(char **data, int i, int j) {
	int pivot_index = i;
	const char *pivot = data[pivot_index];
	word_array_swap(data, pivot_index, j);
	int l = i;
	for (int k = i; k < j; k++) {
		if (strcmp(data[k], pivot) < 0) {
			word_array_swap(data, k, l);
			l++;
		}
	}
	word_array_swap(data, l, j);
	return l;
}

void word_array_print(const struct word_array *self){
	if (self->data == NULL || self->size == 0) {
		fprintf(stderr, "This word array is empty\n");
	}
	else{
		printf("\nThis word array of size %zu (Capacity: %zu) contains:\n", self->size, self->capacity);
		for (size_t i=0; i<self->size; i++){
			printf("%s\n",self->data[i]);
		}
	}
}

void word_array_read_file(struct word_array *self, const char *filename) {
	FILE *file = fopen(filename, "r");
	char buf[WORD_LETTERS_MAX];
	if (file == NULL) {
		fprintf(stderr, "Error: %s is not a file\n", filename);
		exit(EXIT_FAILURE);
	}
	while (fgets(buf, WORD_LETTERS_MAX, file)){
		clean_newline(buf, strlen(buf));
		word_array_add(self, buf);
	}
	fclose(file);
}

void clean_newline(char *buf, size_t size) {
	buf[size - 1] = '\0';
}
