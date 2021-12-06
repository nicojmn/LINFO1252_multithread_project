#include "../headers/read_write.h"
#include "../../../logs/headers/log.h"
// Private Global Variables
pthread_mutex_t mutex_alone_access;
pthread_mutex_t mutex_rc;
pthread_mutex_t mutex_wc;

sem_t sem_r;
sem_t sem_w;

int readcount = 0;
int writecount = 0;

int init_sem_rw(void) {
    int err = sem_init(&sem_r, 0, 1); if (err != 0) return EXIT_FAILURE;
    err = sem_init(&sem_w, 0, 1); if (err != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int init_mutex_rw(void) {
    int err = pthread_mutex_init(&mutex_alone_access, NULL); if (err != 0) return EXIT_FAILURE;
    err = pthread_mutex_init(&mutex_rc, NULL); if (err != 0) return EXIT_FAILURE;
    err = pthread_mutex_init(&mutex_wc, NULL); if (err != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void free_sem_rw(void) {
    sem_destroy(&sem_r);
    sem_destroy(&sem_w);
}

void free_mutex_rw(void) {
    pthread_mutex_destroy(&mutex_alone_access);
    pthread_mutex_destroy(&mutex_rc);
    pthread_mutex_destroy(&mutex_wc);
}

void writer(const int *nbr_iter) {
    int curr_iter = 0;
    while (curr_iter < *nbr_iter) {
        pthread_mutex_lock(&mutex_wc);
            writecount+=1;
            if (writecount == 1) sem_wait(&sem_r);
        pthread_mutex_unlock(&mutex_wc);

        sem_wait(&sem_w);
            INFO("WRITER has access to the DB");
            curr_iter+=1;
            false_hardworking();
        sem_post(&sem_w);

        pthread_mutex_lock(&mutex_wc);
            writecount-=1;
            if (writecount == 0) sem_post(&sem_r);
        pthread_mutex_unlock(&mutex_wc);
    }
}

void reader(const int *nbr_iter) {
    int curr_iter = 0;
    while (curr_iter < *nbr_iter) {
        pthread_mutex_lock(&mutex_alone_access);
            sem_wait(&sem_r);

                pthread_mutex_lock(&mutex_rc);
                    //critical section
                    readcount+=1;
                    if (readcount == 1) sem_wait(&sem_w);
                pthread_mutex_unlock(&mutex_rc);

            sem_post(&sem_r);
        pthread_mutex_unlock(&mutex_alone_access);

        INFO("READER has access to the DB");
        curr_iter+=1;
        false_hardworking();

        pthread_mutex_lock(&mutex_rc);
            readcount-=1;
            if (readcount == 0) sem_post(&sem_w);
        pthread_mutex_unlock(&mutex_rc);
    }
}

void false_hardworking(void) {
    while(rand() > RAND_MAX/10000);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        ERROR("The program needs a number of writers and readers in arguments.");
        return EXIT_FAILURE;
    }
    int err;
    const int n_threads_w = atoi(argv[1]);
    const int n_threads_r = atoi(argv[2]);

    pthread_t thread_w[n_threads_w];
    pthread_t thread_r[n_threads_r];

    int nbr_iter_w[2] = {640/n_threads_w, (640/n_threads_w)+(640%n_threads_w)};
    int nbr_iter_r[2] = {2560/n_threads_r, (2560/n_threads_r)+(2560%n_threads_r)};

    err = init_mutex_rw();
    if (err != 0) {
        ERROR("Cannot initialize a MUTEX");
        exit(EXIT_FAILURE);
    } SUCCESS("Mutexes Initialized");

    err = init_sem_rw();
    if (err != 0) {
        ERROR("Cannot initialize the SEMAPHORES");
        exit(EXIT_FAILURE);
    } SUCCESS("Semaphores Initialized");

    for (int i = 0; i < n_threads_w; i++) {
        err = pthread_create(&(thread_w[i]), NULL, (void *(*)(void *)) writer, i==0 ? &nbr_iter_w[1] : &nbr_iter_w[0]);
        if (err != 0) {
            ERROR("Cannot initialize the WRITER %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Writer %d Initialized", i+1);
    }

    for (int i = 0; i < n_threads_r; i++) {
        err = pthread_create(&(thread_r[i]), NULL, (void *(*)(void *)) reader, i==0 ? &nbr_iter_r[1] : &nbr_iter_r[0]);
        if (err != 0) {
            ERROR("Cannot initialize the READER %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Reader %d Initialized", i+1);
    }

    INFO("In Processing...");

    for (int i = 0; i < n_threads_w; i++) {
        err = pthread_join(thread_w[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN a WRITER");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Writer(s) Finished");

    for (int i = 0; i < n_threads_r; i++) {
        err = pthread_join(thread_r[i], NULL);
        if (err != 0) {
            ERROR("Cannot JOIN a READER");
            exit(EXIT_FAILURE);
        }
    } SUCCESS("Reader(s) Finished");

    free_sem_rw();
    free_mutex_rw();
    return EXIT_SUCCESS;
}
