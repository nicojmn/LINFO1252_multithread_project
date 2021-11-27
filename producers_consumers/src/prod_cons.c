#include "../headers/prod_cons.h"
#include "../../logs_implem/headers/log.h"

int init_sem_buffer_states() {
    int err = sem_init(&empty, 0, BUFFER_SIZE); if (err != 0) return EXIT_FAILURE;
    err = sem_init(&full, 0, 0); if (err != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void free_sem_buffer_states() {
    sem_destroy(&empty);
    sem_destroy(&full);
}

void producer(const int *nbr_iter) {
    int elem = 0;
    int curr_iter = 0;
    while (curr_iter < *nbr_iter) {
        elem = produce_elem_buffer(elem);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
            insert_elem_buffer(elem);
            curr_iter+=1;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void consumer(const int *nbr_iter) {
//    int elem = 0;
    int curr_iter = 0;
    while (curr_iter < *nbr_iter) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
            remove_elem_buffer();
            curr_iter+=1;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        ERROR("The program needs a number of producers and consumers in arguments.");
        return EXIT_FAILURE;
    }
    int err;
    const int n_threads_prod = atoi(argv[1]);
    const int n_threads_cons = atoi(argv[2]);

    pthread_t prod_thread[n_threads_prod];
    pthread_t cons_thread[n_threads_cons];

    int nbr_iter_prod[2] = {1024/n_threads_prod, (1024/n_threads_prod)+(1024%n_threads_prod)};
    int nbr_iter_cons[2] = {1024/n_threads_cons, (1024/n_threads_cons)+(1024%n_threads_cons)};

    err = init_buffer();
    if (err != 0) {
        ERROR("Cannot initialize the BUFFER");
        exit(EXIT_FAILURE);
    } SUCCESS("Buffer Initialized");

    err = pthread_mutex_init(&mutex, NULL);
    if (err != 0) {
        ERROR("Cannot initialize the MUTEX");
        exit(EXIT_FAILURE);
    } SUCCESS("Mutex Initialized");

    err = init_sem_buffer_states();
    if (err != 0) {
        ERROR("Cannot initialize the SEMAPHORES");
        exit(EXIT_FAILURE);
    } SUCCESS("Semaphores Initialized");

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_create(&(prod_thread[i]), NULL, (void *(*)(void *)) producer, i==0 ? &nbr_iter_prod[1] : &nbr_iter_prod[0]);
        if (err != 0) {
            ERROR("Cannot initialize the PRODUCER THREAD %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Producer Thread %d Initialized", i+1);
    }

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_create(&(cons_thread[i]), NULL, (void *(*)(void *)) consumer, i==0 ? &nbr_iter_cons[1] : &nbr_iter_cons[0]);
        if (err != 0) {
            ERROR("Cannot initialize the CONSUMER THREADS");
            exit(EXIT_FAILURE);
        } SUCCESS("Consumer Thread %d Initialized", i+1);
    }

    INFO("In Processing...");

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_join(prod_thread[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN the PRODUCER THREADS");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Producer Thread(s) Finished");

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_join(cons_thread[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN the CONSUMER THREADS");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Consumer Thread(s) Finished");

    free_sem_buffer_states();
    free_buffer();
    return EXIT_SUCCESS;
}
