#include "../headers/test_and_test_and_set.h"

typedef struct _locker {
    int lock;
} locker_t;

locker_t *init_lock() {
    locker_t *locker = malloc(sizeof(locker_t));
    if (locker == NULL) return NULL;
    return locker;
}

void destroy_lock(locker_t *locker) {
    free(locker);
}

int lock(locker_t *locker) {
    int set = 1;
    while (set == 1) {
        if (locker->lock == 0) {
            asm("xchgl  %0, %1" : "+q" (set), "+m" (locker->lock));
        }
    }
    return EXIT_SUCCESS;
}

int unlock(locker_t *locker) {
    locker->lock = 0;
    return EXIT_SUCCESS;
}

