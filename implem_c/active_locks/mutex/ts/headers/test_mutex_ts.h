#include "../headers/test_and_set.h"

#ifndef TEST_MUTEX_TS_H
#define TEST_MUTEX_TS_H
/**
 * The arguments structure with the number of iteration for one thread
 * and the locker_t structure
 */
typedef struct _arg arg_t;

/**
 * Initialize the args in the STACK
 * @param nbr_count: The number of iteration for one thread
 * @param locker: A locker_t structure with the lock variable
 * @return the args created
 */
arg_t init_arg(int nbr_count, locker_t* locker);

/**
 * Simulate a hard work to make the program more realistic
 */
void false_hardworking(void);

/**
 * Simulate work in a concurrency way
 * @param args: A arg_t structure with all the arguments needed
 */
void work(arg_t *args);

/**
 * The main function execute the program to test the test_and_set algorithm with 6400 locks/unlocks
 * @param argc : number of arguments (needed 2)
 * @param argv : array of arguments (program name, #threads)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv);

#endif //TEST_MUTEX_TS_H
