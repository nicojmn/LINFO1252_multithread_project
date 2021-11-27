#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef BUFFER_IMPLEM_H
#define BUFFER_IMPLEM_H
#define BUFFER_SIZE 8
//int *buffer;
//int prod_index;
//int cons_index;

int init_buffer(void);
void free_buffer(void);

int produce_elem_buffer(int elem);
void insert_elem_buffer(int elem);
int remove_elem_buffer();

void false_hardworking(void);
#endif //BUFFER_IMPLEM_H
