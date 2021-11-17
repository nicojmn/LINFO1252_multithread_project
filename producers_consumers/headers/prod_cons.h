#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H
#define BUFFER_SIZE 8
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void producer(void);
void consumer(void);

void false_hardworking(void);

int main(int argc, char **argv);
#endif //PRODUCER_CONSUMER_H
