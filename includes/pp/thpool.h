#ifndef PP_THPOOL_H_
#define PP_THPOOL_H_

#include <threads.h>

#include "pp/list.h"

#define THPOOL_WAIT_SEC   0
#define THPOOL_WAIT_NSEC  50000000

typedef struct thread_pool
{
  list_t tasks;
  thrd_t* threads;
  size_t size;
  mtx_t task_mutex;
  struct timespec wait;
  int running:1;
} thpool_t;

struct thtask
{
  thrd_start_t func;
  void* arg;
};

/*
  @return       pool or NULL on error
  @description  Initialize the thread pool with a number of threads nthreads
*/
thpool_t* thpool_init(thpool_t* pool, size_t nthreads);

/*
  @return       pool or NULL on error
  @description  Run async function func(arg) using pool
                If pool is not running, will return an error
*/
thpool_t* thpool_push(thpool_t* pool, thrd_start_t func, void* arg);

/*
  @return       pool or NULL on error
  @description  Run async functions from array of nmemb elements of size size using pool
                If pool is not running, will return an error
*/
thpool_t* thpool_map(thpool_t* pool, void* array, size_t nmemb, size_t size, thrd_start_t func);

/*
  @return       pool or NULL on error
  @description  Join all threads from pool
                thpool_init() must be called afterwards if one wants to re-create threads
*/
thpool_t* thpool_join(thpool_t* pool);

/*
  @return       Always 0
  @description  Routine of every thread from the pool
                If a task is available, it will pop it from the list of tasks and run it
                Otherwise, the thread will sleep for pool.wait
*/
int thpool_thread(void* pool);

/*
  @return       pool or NULL on error
  @description  Insert task into the pool.tasks
                If lock is positive, it will lock pool.task_mutex before doing so
*/
thpool_t* thpool_push_task(thpool_t* pool, struct thtask* task, int lock);

/*
  @return       Created thread task or NULL on error
  @description  Create and allocate a thread task from func and arg
*/
struct thtask* thpool_make_task(thrd_start_t func, void* arg);

#endif
