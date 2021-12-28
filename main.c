#define _CRT_SECURE_NO_WARNINGS
#include "ThreadPool.h"
#include <stdio.h>

void func(){

    //do some job

    return;
}

int main() {
//    printf("Hello, World!\n");

    struct ThreadJob job1;
    job1 = thread_job_constructor(func, NULL);
//    job1.job = func;
//    job1.arg = NULL;


    struct ThreadPool pool;
    pool = thread_pool_constructor(10);

    pool.add_work(&pool, job1);

    return 0;
}
