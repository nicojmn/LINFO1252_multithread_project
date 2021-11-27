#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef BUFFER_IMPLEM_H
#define BUFFER_IMPLEM_H
#define BUFFER_SIZE 8
/**
 * Initialize the buffer in the HEAP
 * @return  EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int init_buffer(void);

/**
 * Free the buffer and sets it to NULL
 */
void free_buffer(void);

/**
 * Produce a pseudo-random element in the [INT_MIN, INT_MAX] interval
 * @param elem : The last element produced, used as seed
 * @return
 */
int produce_elem_buffer(int elem);

/**
 * Insert "elem" in the buffer at the "prod_index"
 * @param elem : The element to be inserted in the buffer
 */
void insert_elem_buffer(int elem);

/**
 * Remove "elem" from the buffer at the "cons_index"
 * @return The element removed from the buffer
 */
int remove_elem_buffer();

/**
 * Simulate a hard work to make the program more realistic
 * Compare value changed from RAND_MAX/10000 to RAND_MAX/50000 to better observe the changes in the performance evaluation
 */
void false_hardworking(void);
#endif //BUFFER_IMPLEM_H
