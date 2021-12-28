#include "ThreadPool.h"

#include <stdlib.h>

void * thread_job(void *arg);
void add_work(struct ThreadPool *thred_pool, struct ThreadJob job);


struct ThreadPool thread_pool_constructor(int num_threads){
    struct ThreadPool thread_pool;

    thread_pool.num_threads = num_threads;
    thread_pool.active = 1; // Assume that its always active when created

    thread_pool.pool = (pthread_t *)malloc(sizeof(pthread_t[num_threads]));

    // Initialising threads
    for(int i = 0; i < num_threads; ++i){
        pthread_create(&thread_pool.pool[i], NULL, thread_job, NULL);
    }

    thread_pool.work = queue_constructor();
    thread_pool.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    thread_pool.signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    thread_pool.add_work = add_work;

    return thread_pool;
}

//Thread pool destructor
void thread_pool_destructor(struct ThreadPool *thread_pool){
    thread_pool->active = 0;
    for(int i = 0; i < thread_pool->num_threads; ++i){
        pthread_cond_signal(&thread_pool->signal);
    }
    for(int i = 0; i < thread_pool->num_threads; ++i){
        pthread_join(thread_pool->pool[i], NULL);
    }
    free(thread_pool->pool);
    queue_destructor(&thread_pool->work);
}

struct ThreadJob thread_job_constructor(void * (*job_function)(void *arg), void *arg){
    struct ThreadJob job;
    job.job = job_function;
    job.arg = arg;
    return job;
}


void * thread_job(void *arg){

    struct ThreadPool *thread_pool = (struct ThreadPool *)arg;
    while(thread_pool->active == 1){
        // Lock the door
        pthread_mutex_lock(&thread_pool->lock);
        // Signal
        pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
        // We cpy the thing in queue to the local variable to allow the queue to work and not to have mem...
        struct ThreadJob job = *(struct ThreadJob *)thread_pool->work.peek(&thread_pool->work);
        thread_pool->work.pop(&thread_pool->work);
        // Unlock the door
        pthread_mutex_unlock(&thread_pool->lock);

        if(job.job){
            job.job(job.arg);
        }
    }
    return NULL;
}

void add_work(struct ThreadPool *thred_pool, struct ThreadJob job){
    thred_pool->work.push(&thred_pool->work, &job, sizeof(job));

}
