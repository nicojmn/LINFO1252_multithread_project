#include "../headers/buffer_implem.h"
#include "../../logs_implem/headers/log.h"
// Private Global Variables
int *buffer;
int prod_index;
int cons_index;

int init_buffer() {
    buffer = malloc(sizeof(int)*BUFFER_SIZE);
    if (buffer == NULL) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void free_buffer() {
    free(buffer);
    buffer = NULL;
}

/**
 * --Private Function--
 * Increase the current value of "prod_index" in [0, BUFFER_SIZE] interval
 * @return the current value of "prod_index" (not increased !!)
 */
int prod_index_buffer() {
    int temp = prod_index;
    prod_index = (prod_index + 1) % BUFFER_SIZE;
    return temp;
}

/**
 * --Private Function--
 * Increase the current value of "cons_index" in [0, BUFFER_SIZE] interval
 * @return the current value of "cons_index" (not increased !!)
 */
int cons_index_buffer() {
    int temp = cons_index;
    cons_index = (cons_index + 1) % BUFFER_SIZE;
    return temp;
}

int produce_elem_buffer(int elem) {
    return (INT_MIN + 2*rand_r((unsigned int *) &elem)) % INT_MAX;
}

void insert_elem_buffer(int elem) {
    false_hardworking();
    buffer[prod_index_buffer()] = elem;
}

int remove_elem_buffer() {
    false_hardworking();
    return buffer[cons_index_buffer()];
}

void false_hardworking(void) {
    while(rand() > RAND_MAX/10000);
}
