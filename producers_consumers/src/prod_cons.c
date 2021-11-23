#include "../headers/prod_cons.h"

int init_sem_buffer_states() {
    int err = sem_init(&empty, 0, BUFFER_SIZE); if (err != 0) return EXIT_FAILURE;
    err = sem_init(&full, 0, 0); if (err != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void free_sem_buffer_states() {
    sem_destroy(&empty);
    sem_destroy(&full);
}

_Noreturn void *producer(void) {
    int elem = 0;
    while (true) {
        elem = produce_elem_buffer(elem);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
            insert_elem_buffer(elem);
            printf("PRODUCER:\n");
            print_buffer();
            false_hardworking();
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

_Noreturn void *consumer(void) {
//    int elem = 0;
    while (true) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
            remove_elem_buffer();
            printf("CONSUMER:\n");
            print_buffer();
            false_hardworking();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void false_hardworking(void) {
    while(rand() > RAND_MAX/10000);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "The program needs a number of producers and consumers in arguments.\n");
        return EXIT_FAILURE;
    }
    int err;
    const int n_threads_prod = atoi(argv[1]);
    const int n_threads_cons = atoi(argv[2]);

    pthread_t prod_thread[n_threads_prod];
    pthread_t cons_thread[n_threads_cons];

    err = init_buffer();
    if (err != 0) {
        fprintf(stderr, "Cannot initialize the BUFFER\n");
        return EXIT_FAILURE;
    }
    err = pthread_mutex_init(&mutex, NULL);
    if (err != 0) {
        fprintf(stderr, "Cannot initialize the MUTEX.\n");
        return EXIT_FAILURE;
    }
    err = init_sem_buffer_states();
    if (err != 0) {
        fprintf(stderr, "Cannot initialize the SEMAPHORES.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_create(&(cons_thread[i]), NULL, (void *(*)(void *)) consumer, NULL);
        if (err != 0) {
            fprintf(stderr, "Cannot initialize the CONSUMER THREADS.\n");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_create(&(prod_thread[i]), NULL, (void *(*)(void *)) producer, NULL);
        if (err != 0) {
            fprintf(stderr, "Cannot initialize the PRODUCER THREADS.\n");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n_threads_prod; i++) {
        err = pthread_join(prod_thread[i], NULL);
        if (err != 0) {
            fprintf(stderr, "Cannot JOIN the PRODUCER THREADS.\n");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n_threads_cons; i++) {
        err = pthread_join(cons_thread[i], NULL);
        if (err != 0) {
            fprintf(stderr, "Cannot JOIN the CONSUMER THREADS.\n");
            return EXIT_FAILURE;
        }
    }

    free_sem_buffer_states();
    free_buffer();
    return EXIT_SUCCESS;
}
