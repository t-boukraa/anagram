#include "joker.h"
#include "string.h"
#include "array.h"
#include "dictionary.h"
#include <string.h>
#define WILDCARDS_MAX 4
//#define DEBUG

//Question 4.1:
void wildcard_create(struct wildcard *self){
	self->count=0;
}


//Question 4.2:
void wildcard_search(struct wildcard *self, const char *word){
    char *cpy=string_duplicate(word);
	size_t i = 0;
	for (i = 0 ; i < strlen(cpy) ; i++){
		if (cpy[i]=='*'){
			self->index[self->count]=i;
			self->count++;
    	}
	}
	free(cpy);
}

void word_array_search_anagram_wildcard(const struct word_array *self, const char *word, struct word_array *result){
	char *str = string_duplicate(word);
	struct wildcard *w = malloc(sizeof(struct wildcard));
	wildcard_create(w);
	wildcard_search(w, str);
	if (w->count == 0) {
		word_array_search_anagrams(self, word, result);
	}
	else {
		char *cpy = calloc(strlen(str), sizeof(char));
		size_t i = 0;
		size_t j = 0;
		while (str[i] != '\0') {
			if (str[i] != '*') {
				cpy[j] = str[i];
				j++;
			}
			i++;
		}
#if defined DEBUG
		printf("\nWord: %s", cpy);
#endif
		i = 0;
		while (self->data[i] != NULL) {
			if (string_number_of_different_letters_wildcard(self->data[i], cpy)) {
				if (strlen(self->data[i]) == strlen(cpy) + w->count) {
#if defined DEBUG
					printf("\nAnagram found: %s\n", self->data[i]);
#endif
					word_array_add(result, self->data[i]);
				}
			}
			i++;
		}
		free(cpy);
	}
	free(str);
	free(w);
}

size_t string_number_of_different_letters_wildcard(char *s, char *src) {
	char *str = malloc(sizeof(char));
	size_t i = 0;
	size_t j = 0;
	while (src[i] != '\0') {
		if (src[i] != '*') {
			str[j] = src[i];
			j++;
		}
		i++;
	}
	int *res1 = calloc(26, sizeof(int));
	int *res2 = calloc(26, sizeof(int));
	number_of_each_letters(s, res1);
	number_of_each_letters(str, res2);
	free(str);
	for (size_t j = 0; j < 26; j++) {
		if (res2[j] != 0) {
			if (res2[j] > res1[j]){
				free(res1);
				free(res2);
				return 0;
			}
		}
	}
	free(res1);
	free(res2);
	return 1;
}


void word_dict_search_anagram_wildcard(const struct word_dict *self, const char *word, struct word_array *result){
	char *str = string_duplicate(word);
	struct wildcard *w = malloc(sizeof(struct wildcard));
	wildcard_create(w);
	wildcard_search(w, str);
	if (w->count == 0) {
		word_dict_search_anagrams(self, word, result);
	}
	else{
		char *cpy = calloc(strlen(str), sizeof(char));
		size_t i = 0;
		size_t j = 0;
		while (str[i] != '\0') {
			if (str[i] != '*') {
				cpy[j] = str[i];
				j++;
			}
			i++;
		}
		char *c = calloc(w->count, sizeof(char));	//c: each word of 'word' with wildcard replaced by all the possibilities
		if (w->count == 1) {			//1 Wildcard
			for (c[0] = 'a'; c[0] <= 'z'; c[0]++) {
				word_dict_internal_loop(str, c, cpy, self, result);
			}
		}
		if (w->count == 2) {			//2 Wildcards
			for (c[0] = 'a'; c[0] <= 'z'; c[0]++) {
				for (c[1] = c[0]; c[1] <= 'z'; c[1]++) {
					word_dict_internal_loop(str, c, cpy, self, result);
				}
				c[1]++;
			}
		}
		if (w->count == 3) {			//3 Wildcards
			for (c[0] = 'a'; c[0] <= 'z'; c[0]++) {
				for (c[1] = c[0]; c[1] <= 'z'; c[1]++) {
					for (c[2] = c[1]; c[2] <= 'z'; c[2]++) {
						word_dict_internal_loop(str, c, cpy, self, result);
					}
				}
			}
		}
		if (w->count == 4) {			//4 Wildcards
			for (c[0] = 'a'; c[0] <= 'z'; c[0]++) {
				for (c[1] = c[0]; c[1] <= 'z'; c[1]++) {
					for (c[2] = c[1]; c[2] <= 'z'; c[2]++) {
						for (c[3] = c[2]; c[3] <= 'z'; c[3]++) {
							word_dict_internal_loop(str, c, cpy, self, result);
						}
					}
				}
			}
		}
		free(c);
		free(cpy);
	}
	free(str);
	free(w);

}

void word_dict_internal_loop(char *str, char *c, char *cpy, struct word_dict *self, struct word_array *result) {
	char *tmp = calloc(strlen(str), sizeof(char));
	strcpy(tmp, c);
	strcat(tmp, cpy);
	struct word_dict_bucket *curr = self->buckets[fnv_hash(tmp) % self->size];
	while (curr != NULL) {
		if (string_are_anagrams(curr->word, tmp)) {
			word_array_add(result, curr->word);
		}
		curr = curr->next;
	}
	free(tmp);
}
