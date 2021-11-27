#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "../headers/buffer_implem.h"

#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H
// Global Variables
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

/**
 * Initialize the semaphores "empty" and "full"
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int init_sem_buffer_states(void);

/**
 *  Free the semaphores "empty" and "full" and set them to NULL
 */
void free_sem_buffer_states(void);

/**
 * Produce "nbr_iter" elements
 * @param nbr_iter : The number of iteration the current producer thread must do
 */
void producer(const int *nbr_iter);

/**
 * Consume "nbr_iter" elements produced by producers
 * @param nbr_iter : The number of iteration the current consumer thread must do
 */
void consumer(const int *nbr_iter);

/**
 * The main function execute the program to solve the producer-consumer problem with 1024 elements produced and consumed
 * @param argc : number of arguments (needed 3)
 * @param argv : array of arguments (program name, #producer_threads, #consumer_threads)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);
#endif //PRODUCER_CONSUMER_H
