// Main Thread Pool implementation

#ifndef LINUXPROJ_THREADPOOL_H
#define LINUXPROJ_THREADPOOL_H


#include <pthread.h>
#include "Queue/Queue.h"

struct ThreadJob{
    void * (*job)(void *arg);
    void *arg;
};

struct ThreadPool{
    // Number of threads
    int num_threads;
    // The status of threads
    short int active;

    // We use queue to queue the work
    struct Queue work;

    // Main part
    pthread_t *pool;
    pthread_mutex_t lock;
    // To remain inactive
    pthread_cond_t signal;

    void (*add_work)(struct ThreadPool *thred_pool, struct ThreadJob job);
};


struct ThreadPool thread_pool_constructor(int num_threads);
struct ThreadJob thread_job_constructor(void * (*job_function)(void *arg), void *arg);

#endif //LINUXPROJ_THREADPOOL_H


