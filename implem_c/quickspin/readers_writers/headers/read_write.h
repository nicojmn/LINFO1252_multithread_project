#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef READ_WRITE_QS_H
#define READ_WRITE_QS_H
/**
 * Initialize all the semaphores used in the program
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int init_sem_rw(void);

/**
 * Initialize all the mutexes used in the program
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int init_mutex_rw(void);

/**
 *  Destroy all the semaphores used in the program
 */
void free_sem_rw(void);

/**
 *  Destroy all the mutexes used in the program
 */
void free_mutex_rw(void);

/**
 * Written #nbr_iter times in the database
 * @param nbr_iter : The number of iteration the current writer thread must do
 */
void writer(const int *nbr_iter);

/**
 * Read #nbr_iter times the database
 * @param nbr_iter : The number of iteration the current reader thread must do
 */
void reader(const int *nbr_iter);

/**
 * The main function execute the program to solve the reader-writer problem with 640 elements written and 2560 elements read
 * @param argc : number of arguments (needed 3)
 * @param argv : array of arguments (program name, #writers, #readers)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);
#endif //READ_WRITE_QS_H
