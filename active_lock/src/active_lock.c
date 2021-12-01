#include "../headers/active_lock.h"
#include "../../logs_implem/headers/log.h"

int *lock_var;

int init_lock() {
    lock_var = malloc(sizeof(int));
    if (lock_var == NULL) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int lock() {
    int set = 1;
    while (set == 1) {
        if (*lock_var == 0) {
            asm("xchgl  %0, %1" : "+q" (set), "+m" (*lock_var));
        }
    }
    return EXIT_SUCCESS;
}

int unlock() {
    *lock_var = 0;
    return EXIT_SUCCESS;
}

void destroy_lock() {
    free(lock_var);
}

void work(const int *nbr_count) {
    for (int i = 0; i < *nbr_count; i++) {
        lock();
        false_hardworking();
        unlock();
    }
}

void false_hardworking(void) {
    while(rand() > RAND_MAX/10000); //50000
}

int main(int argc, char **argv) {
    if (argc < 2) {
        ERROR("The program needs a number of threads in arguments.");
        return EXIT_FAILURE;
    }

    int err;
    const int n_threads = atoi(argv[1]);
    pthread_t threads[n_threads];
    int nbr_iter[2] = {6400/n_threads, (6400/n_threads)+(6400%n_threads)};

    err = init_lock();
    if (err != 0) {
        ERROR("Cannot initialize the LOCK");
        exit(EXIT_FAILURE);
    } SUCCESS("Lock Initialized");

    for (int i = 0; i < n_threads; i++) {
        err = pthread_create(&(threads[i]), NULL, (void *(*)(void *)) work, i == 0 ? &nbr_iter[1] : &nbr_iter[0]);
        if (err != 0) {
            ERROR("Cannot initialize the Thread %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Thread %d Initialized", i+1);
    }

    INFO("In Processing...");

    for (int i = 0; i < n_threads; i++) {
        err = pthread_join(threads[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN a thread");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Thread(s) Finished");

    destroy_lock();
    return EXIT_SUCCESS;
}