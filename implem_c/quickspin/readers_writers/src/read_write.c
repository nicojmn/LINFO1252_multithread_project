#include "../headers/read_write.h"
#include "../../../logs/headers/log.h"
// Private Global Variables
typedef struct _arg {
    locker_t *mutex_alone_access;
    locker_t *mutex_c;
    active_sem_t *sem_r;
    active_sem_t *sem_w;
    const int nbr_iter;
} arg_t;

int readcount = 0;
int writecount = 0;

void writer(arg_t *args) {
    int curr_iter = 0;
    while (curr_iter < args->nbr_iter) {
        lock(args->mutex_c);
            writecount+=1;
            if (writecount == 1) active_sem_wait(args->sem_r);
        unlock(args->mutex_c);

        active_sem_wait(args->sem_w);
            INFO("WRITER has access to the DB");
            curr_iter+=1;
            while(rand() > RAND_MAX/10000);
        active_sem_post(args->sem_w);

        lock(args->mutex_c);
            writecount-=1;
            if (writecount == 0) active_sem_post(args->sem_r);
        unlock(args->mutex_c);
    }
}

void reader(arg_t *args) {
    int curr_iter = 0;
    while (curr_iter < args->nbr_iter) {
        lock(args->mutex_alone_access);
            active_sem_wait(args->sem_r);

                lock(args->mutex_c);
                    //critical section
                    readcount+=1;
                    if (readcount == 1) active_sem_wait(args->sem_w);
                unlock(args->mutex_c);

        active_sem_post(args->sem_r);
        unlock(args->mutex_alone_access);

        INFO("READER has access to the DB");
        curr_iter+=1;
        while(rand() > RAND_MAX/10000);

        lock(args->mutex_c);
            readcount-=1;
            if (readcount == 0) active_sem_post(args->sem_w);
        unlock(args->mutex_c);
    }
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

    locker_t *mutex_alone_access = init_lock(); if (mutex_alone_access == NULL) {
        ERROR("Cannot initialize the mutex_alone_access");
        exit(EXIT_FAILURE);
    }
    locker_t *mutex_rc = init_lock(); if (mutex_rc == NULL) {
        destroy_lock(mutex_alone_access);
        ERROR("Cannot initialize the mutex_rc");
        exit(EXIT_FAILURE);
    }
    locker_t *mutex_wc = init_lock(); if (mutex_wc == NULL) {
        destroy_lock(mutex_alone_access);
        destroy_lock(mutex_rc);
        ERROR("Cannot initialize the mutex_wc");
        exit(EXIT_FAILURE);
    } SUCCESS("Mutex Initialized");


    active_sem_t *sem_r = active_sem_init(1); if (sem_r == NULL) {
        destroy_lock(mutex_alone_access);
        destroy_lock(mutex_rc);
        destroy_lock(mutex_wc);
        ERROR("Cannot initialize the sem_r SEMAPHORE");
        exit(EXIT_FAILURE);
    }
    active_sem_t *sem_w = active_sem_init(1); if (sem_w == NULL) {
        destroy_lock(mutex_alone_access);
        destroy_lock(mutex_rc);
        destroy_lock(mutex_wc);
        active_sem_destroy(sem_r);
        ERROR("Cannot initialize the sem_w SEMAPHORE");
        exit(EXIT_FAILURE);
    } SUCCESS("Semaphores Initialized");

    arg_t arg_w_odd = {.nbr_iter = (640/n_threads_w)+(640%n_threads_w), .mutex_alone_access = mutex_alone_access, .mutex_c = mutex_wc, .sem_r = sem_r, .sem_w = sem_w};
    arg_t arg_w = {.nbr_iter = 640/n_threads_w, .mutex_alone_access = mutex_alone_access, .mutex_c = mutex_wc, .sem_r = sem_r, .sem_w = sem_w};

    arg_t arg_r_odd = {.nbr_iter = (2560/n_threads_r)+(2560%n_threads_r), .mutex_alone_access = mutex_alone_access, .mutex_c = mutex_rc, .sem_r = sem_r, .sem_w = sem_w};
    arg_t arg_r = {.nbr_iter = 2560/n_threads_r, .mutex_alone_access = mutex_alone_access, .mutex_c = mutex_rc, .sem_r = sem_r, .sem_w = sem_w};

    for (int i = 0; i < n_threads_w; i++) {
        err = pthread_create(&(thread_w[i]), NULL, (void *(*)(void *)) writer, i==0 ? &arg_w_odd : &arg_w);
        if (err != 0) {
            ERROR("Cannot initialize the WRITER %d", i+1);
            exit(EXIT_FAILURE);
        } SUCCESS("Writer %d Initialized", i+1);
    }

    for (int i = 0; i < n_threads_r; i++) {
        err = pthread_create(&(thread_r[i]), NULL, (void *(*)(void *)) reader, i==0 ? &arg_r_odd : &arg_r);
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

    destroy_lock(mutex_alone_access);
    destroy_lock(mutex_rc);
    destroy_lock(mutex_wc);
    active_sem_destroy(sem_r);
    active_sem_destroy(sem_w);
    return EXIT_SUCCESS;
}
