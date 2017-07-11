#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "string.h"
#include <assert.h>
//#define DEBUG

// Question 1.1:
void number_of_each_letters(const char *str, int *res) {
	const char *p = str;
	while (*p != '\0') {
		if (*p >= 'a' && *p <= 'z') {
			res[*p - 'a']++;
		}
		p++;
	}
#if defined DEBUG
	printf("\n%s contains:\n", str);
	for (size_t i = 0; i<26; i++){
		printf("Number of %c: %i\n",'a' + i, res[i]);
	}
#endif
}

bool string_are_anagrams(const char *str1, const char *str2){
	if (strlen(str1) != strlen(str2)) {
		return false;
	}
	int *tabstr1 = calloc(26, sizeof(int));
	if (tabstr1 == NULL) {
		fprintf(stderr, "Error: calloc function failed\n");
		exit(EXIT_FAILURE);
	}
	int *tabstr2 = calloc(26, sizeof(int));
	if (tabstr2 == NULL) {
		fprintf(stderr, "Error: calloc function failed\n");
		exit(EXIT_FAILURE);
	}
	number_of_each_letters(str1, tabstr1);
	number_of_each_letters(str2, tabstr2);

	for (size_t i = 0; i < 26; i++) {
		if (tabstr1[i] != tabstr2[i]) {
			free(tabstr1);
			free(tabstr2);
			return false;
		}
	}
	free(tabstr1);
	free(tabstr2);
	return true;
}


//Question 1.2:
char *string_duplicate(const char *str){
	char *copy = calloc(strlen(str), sizeof(char));
	if (copy == NULL){
		fprintf(stderr, "Error: calloc function failed");
		exit(EXIT_FAILURE);
	}
	size_t i=0;
	while (str[i] != '\0'){
		copy[i] = str[i];
		i++;
	}
#if defined DEBUG
	printf("\nOperation = copy\n%s has been successfully copied\n",copy);
#endif
	return copy;
}


//Question 1.3:
void string_sort_letters(char *str){
	for (size_t i=1; i<strlen(str); i++){
		char l=str[i];
		size_t j=i;
		while (j > 0 && str[j-1] > l){
			str[j]=str[j-1];
			j--;
		}
		str[j]=l;
	}
#if defined DEBUG
	char *init = string_duplicate(str);
	printf("\nOperation = sort\nInitial word: %s\nSorted word:%s\n", init, str);
	free(init);
#endif
}
