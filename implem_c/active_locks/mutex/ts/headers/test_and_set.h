#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef TS_H
/**
 * The lock structure with the lock variable
 */
typedef struct _locker locker_t;

/**
 * Initialize the lock in the HEAP
 * @return a locker_t structure with the lock variable
 */
locker_t *init_lock(void);

/**
 * Destroy the lock variable from the HEAP
 * @param locker:  A locker_t structure with the lock variable
 */
void destroy_lock(locker_t *locker);

/**
 * Deny access to critical path for threads which don't have a grant access (test_and_set algorithm)
 * @param locker:  A locker_t structure with the lock variable
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int lock(locker_t *locker);

/**
 * Free the access to the critical path for others threads
 * @param locker:  A locker_t structure with the lock variable
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int unlock(locker_t *locker);
#define TS_H

#endif // TS_H
