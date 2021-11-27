#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "../headers/buffer_implem.h"

#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int init_sem_buffer_states(void);
void free_sem_buffer_states(void);

void producer(const int *nbr_iter);

void consumer(const int *nbr_iter);

int main(int argc, char **argv);
#endif //PRODUCER_CONSUMER_H
