#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "param.h"

#define NUM_THREADS 5

struct threadlock lock;

// Increments a counter by one in a for-loop argument a number of times
void *
function(void* arg)
{
  threadlock_acquire((struct threadlock *)&lock);
  int i;
  int* x = (int*)arg;
  for(i=0; i<100000000; i++)
  {
    (*x)++;
  }
  printf(1, "%d\n", *x);
  threadlock_release((struct threadlock *)&lock);
  return 0;
}

int
main(int argc, char *argv[])
{
  threadlock_init((struct threadlock *)&lock);
  int x = 0;
  int i;
  int pid;
  for(i=0; i<NUM_THREADS; i++)
  {
    pid = thread_create(function, (void *)&x);
    if(pid == -1)
    {
      printf(2, "Error: thread_create failure");
      exit();
    }
    else if(pid == 0)
    {
      printf(1, "I am the child\n");
      exit();
    }
  }
  
  for(i=0; i<NUM_THREADS; i++)
  {
    thread_join();
  }
  printf(1, "%d\n", x);

  exit();
}



