#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "../../../active_locks/semaphore/headers/semaphore.h"

#ifndef READ_WRITE_QS_H
#define READ_WRITE_QS_H
typedef struct _arg arg_t;

/**
 * Written #nbr_iter times in the database
 * @param args : The arguments structure arg_t
 */
void writer(arg_t *args);

/**
 * Read #nbr_iter times the database
 * @param args : The arguments structure arg_t
 */
void reader(arg_t *args);

/**
 * The main function execute the program to solve the reader-writer problem with 640 elements written and 2560 elements read
 * @param argc : number of arguments (needed 3)
 * @param argv : array of arguments (program name, #writers, #readers)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);
#endif //READ_WRITE_QS_H
