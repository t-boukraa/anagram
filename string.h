#ifndef STRING_H
#define STRING_H
#include <stdbool.h>


void number_of_each_letters(const char *str, int *res);

bool string_are_anagrams(const char *str1, const char *str2);

char *string_duplicate(const char *str);

void string_sort_letters(char *str);
#endif