#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (void)
{
  pid_t f;
  printf("1\n");
  f=fork();

  printf("2\n");
  if (f==-1)
  {
    printf("Error \n");
    exit(1);
  } 
  else if (f==0)
  {
    printf("   Child: My process ID: %d \n", getpid());
    sleep(1);
    printf("   Child: My parent's process ID: %d \n", getppid());
    exit(0);
  }
  else
  {
    printf("Parent: My parent's process ID: %d \n", getppid());
    printf("Parent: My process ID: %d \n", getpid());
    printf("Parent: My child's process ID: %d \n", f);
    wait(NULL);
  printf("5\n");
    printf("Parent: Terminating...\n");
    exit(0);
  }
  printf("3\n");
  return (0);
}

