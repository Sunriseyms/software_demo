#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t cpid, w;
  int wstatus;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) { /* Code executed by child */
    printf("Child PID is %ld\n", (long)getpid());
    if (argc == 1)
      pause(); /* Wait for signals */
    if (argc == 2){
        printf("abort\n");
        abort();
    }
    if (argc == 3) {
        printf("raise\n");
        //int i = 2/0;
        raise(15);
    }
    _exit(atoi(argv[1]));

  } else { /* Code executed by parent */
    while (true) {
      w = waitpid(cpid, &wstatus, WNOHANG);
      //printf("w=%d\n", w);
      if (w == 0) {
        continue;
      }

      if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }

      if (WIFEXITED(wstatus)) {
        printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        break;
      } else if (WIFSIGNALED(wstatus)) {
        printf("killed by signal %d\n", WTERMSIG(wstatus));
        break;
      } else if (WIFSTOPPED(wstatus)) {
        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
      } else if (WIFCONTINUED(wstatus)) {
        printf("continued\n");
      }

      printf("xxxx\n");
    }
    exit(EXIT_SUCCESS);
  }
}
