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

