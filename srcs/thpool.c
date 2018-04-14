#include "pp/thpool.h"

thpool_t* thpool_init(thpool_t* pool, size_t nthreads)
{
  pool->running = 1;
  pool->size = nthreads;
  list_init(&pool->tasks);
  if (mtx_init(&pool->task_mutex, mtx_plain) != thrd_success)
  {
    return (NULL);
  }
  pool->wait = (struct timespec) {
    .tv_sec   = THPOOL_WAIT_SEC,
    .tv_nsec  = THPOOL_WAIT_NSEC
  };
  if ((pool->threads = malloc(sizeof(*pool->threads) * nthreads)) == NULL)
  {
    return (NULL);
  }
  mtx_lock(&pool->task_mutex);
  for (size_t i = 0; i < nthreads; ++i)
  {
    if (thrd_create(&pool->threads[i], &thpool_thread, pool) != thrd_success)
    {
      return (NULL);
    }
  }
  mtx_unlock(&pool->task_mutex);
  return (pool);
}

int thpool_push(thpool_t* pool, thrd_start_t func, void* arg)
{
  struct thtask* task;
  
  if (!pool->running)
  {
    return (-1);
  }
  if ((task = thpool_make_task(func, arg)) == NULL)
  {
    return (-1);
  }
  return (thpool_push_task(pool, task, 1));
}

int thpool_map(thpool_t* pool, void* array, size_t nmemb, size_t size, thrd_start_t func)
{
  struct thtask* task;
  char* list = (char*)array;

  if (!pool->running)
  {
    return (-1);
  }
  mtx_lock(&pool->task_mutex);
  for (size_t i = 0; i < nmemb; ++i)
  {
    if ((task = thpool_make_task(func, list + (i * size))) == NULL)
    {
      mtx_unlock(&pool->task_mutex);
      return (-1);
    }
    if (thpool_push_task(pool, task, 0) < 0)
    {
      mtx_unlock(&pool->task_mutex);
      return (-1);
    }
  }
  mtx_unlock(&pool->task_mutex);
  return (0);
}

int thpool_join(thpool_t* pool)
{
  int last_res;
  mtx_lock(&pool->task_mutex);
  pool->running = 0;
  mtx_unlock(&pool->task_mutex);
  for (size_t i = 0; i < pool->size; ++i)
  {
    if (thrd_join(pool->threads[i], &last_res) != thrd_success)
    {
      return (-1);
    }
  }
  mtx_destroy(&pool->task_mutex);
  list_clear(&pool->tasks);
  free(pool->threads);
  return (0);
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
  return (0);
}

int thpool_push_task(thpool_t* pool, struct thtask* task, int lock)
{
  int status = 0;

  if (lock)
  {
    mtx_lock(&pool->task_mutex);
  }
  if (list_push_front(&pool->tasks, task) == NULL)
  {
    status = -1;
  }
  if (lock)
  {
    mtx_unlock(&pool->task_mutex);
  }
  return (status);
}

struct thtask* thpool_make_task(thrd_start_t func, void* arg)
{
  struct thtask* task = malloc(sizeof(*task));

  if (task == NULL)
  {
    return (NULL);
  }
  task->func = func;
  task->arg = arg;
  return (task);
}
