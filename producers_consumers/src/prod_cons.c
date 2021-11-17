#include "../headers/prod_cons.h"

void producer(void) {

}

void consumer(void) {

}

void false_hardworking(void) {
    while(rand() > RAND_MAX/10000);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "The program needs a number of producers and consumers in arguments.\n");
        return EXIT_FAILURE;
    }
    const int n_threads_prod = atoi(argv[1]);
    const int n_threads_cons = atoi(argv[2]);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);



    return EXIT_SUCCESS;
}
