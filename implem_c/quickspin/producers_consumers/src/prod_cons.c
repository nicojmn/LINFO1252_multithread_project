#include "../headers/prod_cons.h"
#include "../../../logs/headers/log.h"
// Private Global Variables
typedef struct _arg {
    locker_t *mutex;
    active_sem_t *empty;
    active_sem_t *full;
    const int nbr_iter;
} arg_t;

void producer(arg_t *args) {
    int elem = 0;
    int curr_iter = 0;
    while (curr_iter < args->nbr_iter) {
        elem = produce_elem_buffer(elem);
        active_sem_wait(args->empty);
        lock(args->mutex);
            insert_elem_buffer(elem);
            curr_iter+=1;
        unlock(args->mutex);
        active_sem_post(args->full);
    }
}

void consumer(arg_t *args) {
//    int elem = 0;
    int curr_iter = 0;
    while (curr_iter < args->nbr_iter) {
        active_sem_wait(args->full);
        lock(args->mutex);
            remove_elem_buffer();
            curr_iter+=1;
        unlock(args->mutex);
        active_sem_post(args->empty);
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        ERROR("The program needs a number of producers and consumers in arguments.");
        exit(EXIT_FAILURE);
    }
    int err;
    const int n_threads_prod = atoi(argv[1]);
    const int n_threads_cons = atoi(argv[2]);

    pthread_t prod_thread[n_threads_prod];
    pthread_t cons_thread[n_threads_cons];

    err = init_buffer();
    if (err != 0) {
        ERROR("Cannot initialize the BUFFER");
        exit(EXIT_FAILURE);
    } SUCCESS("Buffer Initialized");

    locker_t *mutex = init_lock(); if (mutex == NULL) {
        ERROR("Cannot initialize the MUTEX");
        exit(EXIT_FAILURE);
    } SUCCESS("Mutex Initialized");

    active_sem_t *empty = active_sem_init(BUFFER_SIZE); if (empty == NULL) {
        ERROR("Cannot initialize the empty SEMAPHORE");
        destroy_lock(mutex);
        exit(EXIT_FAILURE);
    }
    active_sem_t *full = active_sem_init(0); if (full == NULL) {
        ERROR("Cannot initialize the full SEMAPHORE");
        destroy_lock(mutex);
        active_sem_destroy(empty);
        exit(EXIT_FAILURE);
    } SUCCESS("Semaphores Initialized");

    arg_t arg_prod_odd = {.nbr_iter = (1024/n_threads_prod)+(1024%n_threads_prod), .mutex = mutex, .empty = empty, .full = full};
    arg_t arg_prod = {.nbr_iter = 1024/n_threads_prod, .mutex = mutex, .empty = empty, .full = full};

    arg_t arg_cons_odd = {.nbr_iter = (1024/n_threads_cons)+(1024%n_threads_cons), .mutex = mutex, .empty = empty, .full = full};
    arg_t arg_cons = {.nbr_iter = 1024/n_threads_cons, .mutex = mutex, .empty = empty, .full = full};

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_create(&(prod_thread[i]), NULL, (void *(*)(void *)) producer, i==0 ? &arg_prod_odd : &arg_prod);
        if (err != 0) {
            ERROR("Cannot initialize the PRODUCER %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Producer %d Initialized", i+1);
    }

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_create(&(cons_thread[i]), NULL, (void *(*)(void *)) consumer, i==0 ? &arg_cons_odd : &arg_cons);
        if (err != 0) {
            ERROR("Cannot initialize the CONSUMER %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Consumer %d Initialized", i+1);
    }

    INFO("In Processing...");

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_join(prod_thread[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN a PRODUCER");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Producer(s) Finished");

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_join(cons_thread[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN a CONSUMER");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Consumer(s) Finished");

    destroy_lock(mutex);
    active_sem_destroy(empty);
    active_sem_destroy(full);
    free_buffer();
    return EXIT_SUCCESS;
}
