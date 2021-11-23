#include "../headers/buffer_implem.h"
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

int prod_index_buffer() {
    int temp = prod_index;
    prod_index = (prod_index + 1) % BUFFER_SIZE;
    return temp;
}

int cons_index_buffer() {
    int temp = cons_index;
    cons_index = (cons_index + 1) % BUFFER_SIZE;
    return temp;
}

int produce_elem_buffer(int elem) {
    return (INT_MIN + 2*rand_r((unsigned int *) &elem)) % INT_MAX;
}

void insert_elem_buffer(int elem) {
    buffer[prod_index_buffer()] = elem;
}

int remove_elem_buffer() {
    return buffer[cons_index_buffer()];
}

void print_buffer() {
    printf("-----------\n");
    printf("Prod Index   =>  %d\n", prod_index);
    printf("Cons Index   =>  %d\n", cons_index);
    printf("BUFFER       =>  [");
    for (int i = 0; i< BUFFER_SIZE; i++) {
        if (i > 0) printf(", ");
        printf("%d", buffer[i]);
    }
    printf("]\n");
    printf("-----------\n");
}