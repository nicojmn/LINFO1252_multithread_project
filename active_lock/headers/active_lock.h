#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef ACTIVE_LOCK_H
/**
 * Initialize the lock in the HEAP
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int init_lock(void);

/**
 * Deny access to critical path for threads which don't have a grant access
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int lock(void);

/**
 * Free the access to the critical path for others threads
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int unlock(void);

/**
 * Destroy the lock variable from the HEAP
 */
void destroy_lock(void);

/**
 * Simulate work in a concurrency way
 * @param nbr_count : The number of iteration for one thread
 */
void work(const int *nbr_count);

/**
 * Simulate a hard work to make the program more realistic
 */
void false_hardworking(void);

/**
 * The main function execute the program to test the test_and_set algorithm with 6400 locks/unlocks
 * @param argc : number of arguments (needed 2)
 * @param argv : array of arguments (program name, #threads)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);
#define ACTIVE_LOCK_H

#endif // ACTIVE_LOCK_H
