#include "types.h"
#include "mmu.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "fs.h"
#include "proc.h"
#include "x86.h"

int
thread_join(void)
{
  return join();
}

int
thread_create(void * (*start_routine)(void *), void * arg){
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

void
threadlock_init(struct threadlock *lk)
{
  lk->locked = 0;
}

// Acquire the lock.
// Loops (spins) until the lock is acquired.
// Holding a lock for a long time may cause
// other CPUs to waste time spinning to acquire it.
void
threadlock_acquire(struct threadlock *lk)
{
  while(xchg(&lk->locked, 1) != 0)
    ;
}

// Release the lock.
void
threadlock_release(struct threadlock *lk)
{
  xchg(&lk->locked, 0);
}
