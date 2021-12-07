#include <stdbool.h>
#include <stdlib.h>
#include "../../mutex/tts/headers/test_and_test_and_set.h"

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
/**
 * The semaphore structure with the value of the semaphore and the lock_t structure
 */
typedef struct _active_sem_t active_sem_t;

/**
 * Initialize the semaphore
 * @param value: The initiale value of the semaphore
 * @return A semaphore active_sem_t on the HEAP
 */
active_sem_t *active_sem_init(unsigned int value);

/**
 * Destroy the semaphore
 * @param sem: The semaphore active_sem_t on the HEAP
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int active_sem_destroy(active_sem_t *sem);

/**
 * Decrease the semaphore value and wait if it's <= 0
 * @param sem: The semaphore active_sem_t on the HEAP
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int active_sem_wait(active_sem_t *sem);

/**
 * Increase the semaphore value
 * @param sem: The semaphore active_sem_t on the HEAP
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int active_sem_post(active_sem_t *sem);
#endif //SEMAPHORE_H
