#include "../headers/philosophers.h"
#include "../../logs_implem/headers/log.h"

void *philosopher(void *arg) {

    int *id = (int *) arg;
    int left_stick = *id;
    int right_stick = (*id + 1) % NUMBER_PHILOSOPHERS;


    for (int i = 0; i < 5; ++i) { // TODO : change 5 to 100000 - 1
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
    INFO("Philosopher %d is eating", id);
}

void think(int id) {
    INFO("Philosopher %d is thinking", id);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        ERROR("Wrong number of arguments, the program need a number of philosophers in arguments");
        return EXIT_FAILURE;
    }

    NUMBER_PHILOSOPHERS = atoi(argv[1]);

    pthread_t *philosophers_threads = malloc(sizeof(pthread_t) * NUMBER_PHILOSOPHERS);
    sticks = malloc(sizeof(pthread_mutex_t) * NUMBER_PHILOSOPHERS);
    int ids[NUMBER_PHILOSOPHERS];

    if (philosophers_threads == NULL) {
        ERROR("Memory allocation (malloc) of threads failed");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        ids[i] = i;
    }

    if (NUMBER_PHILOSOPHERS < 2) {
        ERROR("There must be at least 2 philosophers");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_create(&philosophers_threads[i], NULL, philosopher, (void *) &ids[i]) == 0) {
            SUCCESS("Create thread %d", i);
        } else ERROR("Thread cannot be init");
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_join(philosophers_threads[i], NULL) != 0) {
            ERROR("Can't join thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_mutex_destroy(&sticks[i]) != 0) {
            ERROR("Can't destroy mutex");
            return EXIT_FAILURE;
        }
    }

    free(philosophers_threads);
    philosophers_threads = NULL;
    free(sticks);
    sticks = NULL;

    return EXIT_SUCCESS;
}