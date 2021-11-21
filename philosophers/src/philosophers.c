#include "../headers/philosophers.h"

void eat(int id) {
    printf("Philosopher %d is eating\n", id);
}

void think(int id) {
    printf("Philosopher %d is thinking\n", id);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments, the program need a number of philosophers in arguments\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
