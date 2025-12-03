#ifndef __HASH_HEADER_H__
#define __HASH_HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CHAR            50
#define MAX_ARRAY_SIZE      10

typedef struct person{
    int             Id;                     // Student or employee ID
    char            Name[MAX_CHAR];         // Name of candidate
    int             Grade;                  // Grade of candidate
    struct person   *prev;                  // Prev link pointer
    struct person   *next;                  // next link pointer
} Person;


// Declerations
void print_hash_table();
bool hash_insert_data(Person *);
int  generate_hash_index(Person *);



#endif
