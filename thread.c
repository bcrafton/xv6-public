#include "types.h"
#include "mmu.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "fs.h"
#include "proc.h"
#include "x86.h"

int
pthread_create(void * (*start_routine)(void *), void * arg){
  void *user_stack = malloc(PGSIZE);  
  int ret = clone(user_stack, PGSIZE);
  if (ret == 0)
  {
    (*start_routine)(arg);
    free(user_stack);
    exit();
  }
  else
  {
    return ret;
  }
}

int
pthread_join(void)
{
  return join();
}

void
pthread_mutex_init(struct pthread_mutex_t *lk)
{
  lk->locked = 0;
}

// Acquire the lock.
// Loops (spins) until the lock is acquired.
// Holding a lock for a long time may cause
// other CPUs to waste time spinning to acquire it.
void
pthread_mutex_lock(struct pthread_mutex_t *lk)
{
  while(xchg(&lk->locked, 1) != 0)
    ;
}

// Release the lock.
void
pthread_mutex_unlock(struct pthread_mutex_t *lk)
{
  xchg(&lk->locked, 0);
}
