#include "../headers/semaphore.h"

typedef struct _active_sem_t {
    long int val;
    locker_t *locker;
} active_sem_t;

active_sem_t *active_sem_init(unsigned int value) {
    active_sem_t *sem = malloc(sizeof(active_sem_t));
    if (sem == NULL) return NULL;
    sem->locker = init_lock();
    if (sem->locker == NULL) { free(sem); return NULL; }
    sem->val = value;
    return sem;
}

int active_sem_destroy(active_sem_t *sem) {
    destroy_lock(sem->locker);
    free(sem);
    return EXIT_SUCCESS;
}

int active_sem_wait(active_sem_t *sem) {
    lock(sem->locker);
    sem->val--;
    unlock(sem->locker);
    return EXIT_SUCCESS;
}

int active_sem_post(active_sem_t *sem) {
    lock(sem->locker);
    sem->val++;
    unlock(sem->locker);
    return EXIT_SUCCESS;
}
