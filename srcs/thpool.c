#include "pp/thpool.h"

thpool_t* thpool_init(thpool_t* pool, size_t nthreads)
{
  pool->running = 1;
  pool->size = nthreads;
  list_init(&pool->tasks);
  if (mtx_init(&pool->task_mutex, mtx_plain) != thrd_success)
  {
    return NULL;
  }
  pool->wait = (struct timespec) {
    .tv_sec   = THPOOL_WAIT_SEC,
    .tv_nsec  = THPOOL_WAIT_NSEC
  };
  if ((pool->threads = malloc(sizeof(*pool->threads) * nthreads)) == NULL)
  {
    return NULL;
  }
  mtx_lock(&pool->task_mutex);
  for (size_t i = 0; i < nthreads; ++i)
  {
    if (thrd_create(&pool->threads[i], &thpool_thread, pool) != thrd_success)
    {
      return NULL;
    }
  }
  mtx_unlock(&pool->task_mutex);
  return pool;
}

thpool_t* thpool_push(thpool_t* pool, thrd_start_t func, void* arg)
{
  struct thtask* task;
  
  if (!pool->running)
  {
    return NULL;
  }
  if ((task = thpool_make_task(func, arg)) == NULL)
  {
    return NULL;
  }
  return thpool_push_task(pool, task, 1);
}

thpool_t* thpool_map(thpool_t* pool, void* array, size_t nmemb, size_t size, thrd_start_t func)
{
  struct thtask* task;
  char* list = (char*)array;

  if (!pool->running)
  {
    return NULL;
  }
  mtx_lock(&pool->task_mutex);
  for (size_t i = 0; i < nmemb; ++i)
  {
    if ((task = thpool_make_task(func, list + (i * size))) == NULL)
    {
      mtx_unlock(&pool->task_mutex);
      return NULL;
    }
    if (thpool_push_task(pool, task, 0) == NULL)
    {
      mtx_unlock(&pool->task_mutex);
      return NULL;
    }
  }
  mtx_unlock(&pool->task_mutex);
  return pool;
}

thpool_t* thpool_join(thpool_t* pool)
{
  int last_res;
  mtx_lock(&pool->task_mutex);
  pool->running = 0;
  mtx_unlock(&pool->task_mutex);
  for (size_t i = 0; i < pool->size; ++i)
  {
    if (thrd_join(pool->threads[i], &last_res) != thrd_success)
    {
      return NULL;
    }
  }
  mtx_destroy(&pool->task_mutex);
  list_clear(&pool->tasks);
  free(pool->threads);
  return pool;
}

int thpool_thread(void* arg)
{
  thpool_t* pool = (thpool_t*)arg;
  struct thtask* task = (struct thtask*)0x1;

  while (pool->running || task)
  {
    task = NULL;
    mtx_lock(&pool->task_mutex);
    if (pool->tasks.size > 0)
    {
      task = list_pop(&pool->tasks);
    }
    mtx_unlock(&pool->task_mutex);
    if (task)
    {
      task->func(task->arg);
      free(task);
    }
    else
    {
      thrd_sleep(&pool->wait, NULL);
    }
  }
  return 0;
}

thpool_t* thpool_push_task(thpool_t* pool, struct thtask* task, int lock)
{
  thpool_t* ret = pool;

  if (lock)
  {
    mtx_lock(&pool->task_mutex);
  }
  if (list_push_front(&pool->tasks, task) == NULL)
  {
    ret = NULL;
  }
  if (lock)
  {
    mtx_unlock(&pool->task_mutex);
  }
  return ret;
}

struct thtask* thpool_make_task(thrd_start_t func, void* arg)
{
  struct thtask* task = malloc(sizeof(*task));

  if (task == NULL)
  {
    return NULL;
  }
  task->func = func;
  task->arg = arg;
  return task;
}
