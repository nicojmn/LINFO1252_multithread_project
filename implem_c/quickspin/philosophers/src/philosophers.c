#include "../headers/philosophers.h"

void *philosopher(void *arg) {

    int *id = (int *) arg;
    int left_stick = *id;
    int right_stick = (*id + 1) % NUMBER_PHILOSOPHERS;


    for (int i = 0; i < 100000; ++i) {
        think(*id);

        if (left_stick < right_stick) {
            lock(sticks[left_stick]);
            lock(sticks[right_stick]);
        } else {
            lock(sticks[right_stick]);
            lock(sticks[left_stick]);
        }
        eat(*id);
        unlock(sticks[left_stick]);
        unlock(sticks[right_stick]);
    }
    return NULL;
}

void eat(int id) {
    // Philosopher is eating
}

void think(int id) {
    // Philosopher is thinking
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        ERROR("Wrong number of arguments, the program need a number of philosophers in arguments");
        return EXIT_FAILURE;
    }

    NUMBER_PHILOSOPHERS = atoi(argv[1]);

    pthread_t *philosophers_threads = malloc(sizeof(pthread_t) * NUMBER_PHILOSOPHERS);

    sticks = malloc(sizeof(locker_t * ) * NUMBER_PHILOSOPHERS);
    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        sticks[i] = init_lock();
    }
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
        } else {
            ERROR("Thread cannot be init");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        if (pthread_join(philosophers_threads[i], NULL) != 0) {
            ERROR("Can't join thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUMBER_PHILOSOPHERS; ++i) {
        destroy_lock(sticks[i]);
    }

    free(philosophers_threads);
    philosophers_threads = NULL;
    free(sticks);
    sticks = NULL;

    return EXIT_SUCCESS;
}