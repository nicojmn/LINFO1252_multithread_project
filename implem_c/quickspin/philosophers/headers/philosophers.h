#ifndef PHILO_QS_H
#define PHILO_QS_H

#include <stdio.h>
#include <stdlib.h>
#include "../../../active_locks/mutex/tts/headers/test_and_test_and_set.h"
#include "../../../logs/headers/log.h"


// Global variables
locker_t **sticks;
int NUMBER_PHILOSOPHERS;


/**
 *
 * @param id : the id of a philosopher
 */
void eat(int id);

/**
 *
 * @param id the id of a philosopher
 */
void think(int id);

/**
 *
 * @param argc : number of arguments
 * @param argv : array of arguments
 * @return EXIT_SUCCESS if the program works or EXIT_FAILURE if an error occurs
 *
 * The main function execute the program to solve the philosophers problem with 100 000 eat/think cycle
 */
int main(int argc, char *argv[]);

#endif //PHILO_QS_H
