#include "string.h"
#include "array.h"
#include "dictionary.h"
#include "joker.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#define BUFSIZE 32
/* 	BOUKRAA Toufik		*/
/* 	PEYROT 	Stephane	*/

int main(int argc, char *argv[]){	
	struct word_array array;
	struct word_array res1;
	struct word_array res2;
	struct word_dict dic;
	word_array_create(&array);
	word_dict_create(&dic);
	
	word_array_read_file(&array, "dictionnaire.txt");
	word_dict_fill_with_array(&dic, &array);

	struct timeval b, e;

	char buf[BUFSIZE];
	for (;;) {
		word_array_create(&res1);
		word_array_create(&res2);
		printf("> ");
		if (fgets(buf, BUFSIZE, stdin) != NULL){
			clean_newline(buf, strlen(buf));
			if (buf[0] == '\0') {
				break;
			}
		}

		gettimeofday(&b, NULL);
		word_array_search_anagram_wildcard(&array, buf, &res1);
		gettimeofday(&e, NULL);
		long t1 = (e.tv_sec - b.tv_sec) * 1000000 + (e.tv_usec - b.tv_usec);
		word_array_print(&res1);
		gettimeofday(&b, NULL);
		word_dict_search_anagram_wildcard(&dic, buf, &res2);
		gettimeofday(&e, NULL);
		word_array_sort(&res2);
		long t2 = (e.tv_sec - b.tv_sec) * 1000000 + (e.tv_usec - b.tv_usec);
		word_array_print(&res2);
		printf("\nArray:\n%zu word(s) in %ld micro s", res1.size, t1);
		printf("\nDictionary:\n%zu word(s) in %ld micro s\n", res2.size, t2);
		word_array_destroy(&res1);
		word_array_destroy(&res2);
	}
	word_array_destroy(&array);
	word_dict_destroy(&dic);


	return EXIT_SUCCESS;
}
