#include "../headers/philosophers.h"

void philosopher(void *arg) {

    int *id = (int *) arg;
    int left_stick = *id;
    int right_stick = (left_stick + 1) % NUMBER_PHILOSOPHERS;

    for (int i = 0; i < 100000; ++i) {
        think(*id);

        if (left_stick < right_stick) {
            sem_wait(&sticks[left_stick]);
            sem_wait(&sticks[right_stick]);
        } else {
            sem_wait(&sticks[right_stick]);
            sem_wait(&sticks[left_stick]);
        }
        eat(*id);
    }
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

    if (NUMBER_PHILOSOPHERS < 3) {
        fprintf(stderr, "There must be at least 2 philosophers");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
