#include "../headers/philosophers.h"

void *philosopher(void *arg) {

    int *id = (int *) arg;
    int left_stick = *id;
    int right_stick = (*id + 1) % NUMBER_PHILOSOPHERS;


    for (int i = 0; i < 5; ++i) {
        think(*id);

        if (left_stick < right_stick) {
            pthread_mutex_lock(&sticks[left_stick]);
            pthread_mutex_lock(&sticks[right_stick]);
        } else {
            pthread_mutex_lock(&sticks[right_stick]);
            pthread_mutex_lock(&sticks[left_stick]);
        }
        eat(*id);
        pthread_mutex_unlock(&sticks[left_stick]);
        pthread_mutex_unlock(&sticks[right_stick]);
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
    sticks = malloc(sizeof(pthread_mutex_t) * NUMBER_PHILOSOPHERS);
    int ids[NUMBER_PHILOSOPHERS];

    if (philosophers_threads == NULL) {
        fprintf(stderr, "Memory allocation (malloc) of threads failed\n");
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
        if (pthread_create(&philosophers_threads[i], NULL, philosopher, (void *) &ids[i]) == 0) {
            printf("Create thread %d\n", i);
        } else fprintf(stderr, "Thread cannot be init\n");
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_join(philosophers_threads[i], NULL) != 0) {
            fprintf(stderr, "Can't join thread\n");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_mutex_destroy(&sticks[i]) != 0) {
            fprintf(stderr, "Can't destroy mutex\n");
            return EXIT_FAILURE;
        }
    }

    free(philosophers_threads);
    free(sticks);

    return EXIT_SUCCESS;
}