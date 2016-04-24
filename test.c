#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "param.h"

#define NUM_THREADS 5

lock_t *lock;
int counter;

// Increments a counter by one in a for-loop argument a number of times
void *
function(void* arg)
{
  int i;
  int* x = (int*)arg;
  for(i=0; i<100; i++)
  {
    (*x)++;
  }
  printf(1, "%d\n", *x);
  return 0;
}

int
main(int argc, char *argv[])
{
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



