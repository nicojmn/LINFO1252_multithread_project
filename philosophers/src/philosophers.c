#include "../headers/philosophers.h"

void *philosopher(void *arg) {

    int *id = (int *) arg;
    ids_t *ids = (ids_t *) malloc(sizeof(ids_t));
    if (ids == NULL) {
        fprintf(stderr, "Malloc of IDs failed\n");
        return (void *) EXIT_FAILURE;
    }

    ids->left_stick = *id;
    ids->right_stick = *id + 1 % NUMBER_PHILOSOPHERS;


    for (int i = 0; i < 100000; ++i) {
        think(*id);
        printf("Here\n");

        if (ids->left_stick < ids->right_stick) {
            printf("Here left\n");
            pthread_mutex_lock(&sticks[ids->left_stick]);
            pthread_mutex_lock(&sticks[ids->right_stick]);
            printf("Left finish");
        } else {
            printf("Here right\n");
            pthread_mutex_lock(&sticks[ids->right_stick]);
            pthread_mutex_lock(&sticks[ids->left_stick]);
        }
        eat(*id);
        pthread_mutex_unlock(&sticks[ids->left_stick]);
        pthread_mutex_unlock(&sticks[ids->right_stick]);
    }
    return NULL;
}

void eat(int id) {
    printf("Philosopher %d is eating\n", id);
}

void think(int id) {
    printf("Philosopher %d is thinking\n", id);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments, the program need a number of philosophers in arguments\n");
        return EXIT_FAILURE;
    }

    NUMBER_PHILOSOPHERS = atoi(argv[1]);

    pthread_t *philosophers_threads = malloc(sizeof(pthread_t) * NUMBER_PHILOSOPHERS);
    if (philosophers_threads == NULL) {
        fprintf(stderr, "Memory allocation (malloc) of threads failed\n");
        return EXIT_FAILURE;
    }

    int *ids = malloc(sizeof(int) * NUMBER_PHILOSOPHERS);
    if (ids == NULL) {
        fprintf(stderr, "Memory allocation (malloc) of ids failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        ids[i] = i;
    }

    if (NUMBER_PHILOSOPHERS < 2) {
        fprintf(stderr, "There must be at least 2 philosophers\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_create(&philosophers_threads[i], NULL, philosopher, (void *) &i) == 0) {
            printf("Create thread %d\n", i);
        } else fprintf(stderr, "Thread cannot be init\n");
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        pthread_join(philosophers_threads[i], NULL);
    }

    free(philosophers_threads);

    return EXIT_SUCCESS;
}