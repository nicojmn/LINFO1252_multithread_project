#include "../headers/test_mutex_ts.h"
#include "../headers/test_and_set.h"
#include "../../../../logs/headers/log.h"

/**
 * The arguments structure with the number of iteration for one thread
 * and the locker_t structure
 */
typedef struct _arg {
    const int nbr_count;
    locker_t *locker;
} arg_t;

/**
 * Initialize the args in the STACK
 * @param nbr_count: The number of iteration for one thread
 * @param locker: A locker_t structure with the lock variable
 * @return the args created
 */
arg_t init_arg(int nbr_count, locker_t* locker) {
    arg_t arg = {.nbr_count = nbr_count, .locker = locker};
    return arg;
}

/**
 * Simulate a hard work to make the program more realistic
 */
void false_hardworking(void) {
    while(rand() > RAND_MAX/10000);
}

/**
 * Simulate work in a concurrency way
 * @param args: A arg_t structure with all the arguments needed
 */
void work(arg_t *args) {
    for (int i = 0; i < args->nbr_count; i++) {
        lock(args->locker);
        false_hardworking();
        unlock(args->locker);
    }
}

/**
 * The main function execute the program to test the test_and_set algorithm with 6400 locks/unlocks
 * @param argc : number of arguments (needed 2)
 * @param argv : array of arguments (program name, #threads)
 * @return EXIT_FAILURE if an error occurs or EXIT_SUCCESS otherwise
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        ERROR("The program needs a number of threads in arguments.");
        exit(EXIT_FAILURE);
    }

    int err;
    const int n_threads = atoi(argv[1]);
    pthread_t threads[n_threads];

    locker_t *locker = init_lock();
    if (locker == NULL) {
        ERROR("Cannot initialize the LOCK");
        exit(EXIT_FAILURE);
    } SUCCESS("Lock Initialized");

    arg_t arg_odd = init_arg((6400/n_threads)+(6400%n_threads), locker);
    arg_t arg = init_arg(6400/n_threads, locker);

    for (int i = 0; i < n_threads; i++) {
        err = pthread_create(&(threads[i]), NULL, (void *(*)(void *)) work, i == 0 ? &arg_odd : &arg);
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

    destroy_lock(locker);
    return EXIT_SUCCESS;
}