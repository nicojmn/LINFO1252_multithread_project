#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "../../../active_locks/semaphore/headers/semaphore.h"
#include "../../../posix/producers_consumers/headers/buffer_implem.h"

#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H
typedef struct _arg arg_t;

/**
 * Produce "nbr_iter" elements
 * @param args : The arguments structure arg_t
 */
void producer(arg_t *args);

/**
 * Consume "nbr_iter" elements produced by producers
 * @param args : The arguments structure arg_t
 */
void consumer(arg_t *args);

/**
 * The main function execute the program to solve the producer-consumer problem with 1024 elements produced and consumed
 * @param argc : number of arguments (needed 3)
 * @param argv : array of arguments (program name, #producer_threads, #consumer_threads)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);
#endif //PRODUCER_CONSUMER_H
