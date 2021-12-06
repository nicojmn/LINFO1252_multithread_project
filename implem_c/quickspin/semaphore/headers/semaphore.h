#include <stdbool.h>
#include <stdlib.h>

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
typedef struct active_sem_t {
    long int val;
    int *lock;
} active_sem_t;

active_sem_t *active_sem_init(unsigned int value);

int active_sem_destroy(active_sem_t *sem);

int active_sem_wait(active_sem_t *sem);

int active_sem_post(active_sem_t *sem);
#endif //SEMAPHORE_H
