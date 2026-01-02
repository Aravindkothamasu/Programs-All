#ifndef __HASH_HEADER_H__
#define __HASH_HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define MAX_CHAR                      50
#define MAX_ARRAY_SIZE                26

#define ITERATOR_START_INDX            0
#define ITERATOR_END_INDX       MAX_ARRAY_SIZE

#define console_print( format, ...)	      \
    printf(format, ##__VA_ARGS__);
    //printf(  __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 


typedef struct person{
    int             Id;                     // Student or employee ID
    char            Name[MAX_CHAR];         // Name of candidate
    int             Grade;                  // Grade of candidate
    struct person   *prev;                  // Prev link pointer
    struct person   *next;                  // next link pointer
    // Update hash_copy_contents(), if addition or deletion of elements.
} Person;


// Hash Functions
bool hash_insert_data(Person *);
bool hash_remove_data(char *);
bool hash_search_data(Person *, char *);
int  hash_generate_index(char *);
int  hash_read_data(Person *);
void hash_print_database();
bool hash_copy_contents(Person *, Person *);


#endif
