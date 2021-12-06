#include "../headers/semaphore.h"

int lock(active_sem_t *sem) {
    int set = 1;
    while (set == 1) {
        if (*(sem->lock) == 0) {
            asm("xchgl  %0, %1" : "+q" (set), "+m" (*(sem->lock)));
        }
    }
    return EXIT_SUCCESS;
}

int unlock(active_sem_t *sem) {
    *(sem->lock) = 0;
    return EXIT_SUCCESS;
}

active_sem_t *active_sem_init(unsigned int value) {
    active_sem_t *sem = malloc(sizeof(active_sem_t));
    if (sem == NULL) return NULL;
    sem->lock = malloc(sizeof(int));
    if (sem->lock == NULL) { free(sem); return NULL; }
    sem->val = value;
    return sem;
}

int active_sem_destroy(active_sem_t *sem) {
    free(sem->lock);
    free(sem);
    return EXIT_SUCCESS;
}

int active_sem_wait(active_sem_t *sem) {
    lock(sem);
    sem->val--;
    unlock(sem);
    return EXIT_SUCCESS;
}

int active_sem_post(active_sem_t *sem) {
    lock(sem);
    sem->val++;
    unlock(sem);
    return EXIT_SUCCESS;
}
