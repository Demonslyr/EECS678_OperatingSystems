#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include <sys/wait.h>

#define BSIZE 256

#define BASH_EXEC  "/bin/bash"
#define FIND_EXEC  "/usr/bin/find"
#define XARGS_EXEC "/usr/bin/xargs"
#define GREP_EXEC  "/bin/grep"
#define SORT_EXEC  "/usr/bin/sort"
#define HEAD_EXEC  "/usr/bin/head"

int main(int argc, char *argv[])
{
  int status;
  pid_t p_find, p_grep, p_sort, p_head;//serve as the int pids
  int fd_1[2],fd_2[2],fd_3[2];
  pipe(fd_1);//find->grep
  pipe(fd_2);//grep->sort
  pipe(fd_3);//sort->head

  if (argc != 4) {
    printf("usage: finder DIR STR NUM_FILES\n");
    exit(0);
  }

  p_find = fork();
  //char   buf[100];
  //sprintf(buf, "This line is from pid %d\n", p_find);
  if (p_find == 0) 
  {
    /* First Child */
    char cmdbuf[BSIZE];
    bzero(cmdbuf, BSIZE);
    dup2(fd_1[1],1);
    sprintf(cmdbuf, "%s %s -name \'*\'.[ch]", FIND_EXEC, argv[1]);
    /* set up pipes */

    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);
    close(fd_3[0]);
    close(fd_3[1]);
    /**/
 
    if ( (execl(BASH_EXEC, BASH_EXEC, "-c", cmdbuf, (char *) 0)) < 0) 
    {
      fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }





  p_grep = fork();
  if (p_grep == 0) 
  {
    /* Second Child */
    char cmdbuf[BSIZE];
    bzero(cmdbuf, BSIZE);
    dup2(fd_1[0],0);
    dup2(fd_2[1],1);
    sprintf(cmdbuf, "%s %s -c %s", XARGS_EXEC, GREP_EXEC, argv[2]);//argv2?//
    /* set up pipes */
 
    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);
    close(fd_3[0]);
    close(fd_3[1]);

    if ( (execl(BASH_EXEC, BASH_EXEC, "-c", cmdbuf, (char *) 0)) < 0) 
    {
      fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }

  p_sort = fork();
  if (p_sort == 0) 
  {
    /* Third Child */
    char cmdbuf[BSIZE];
    bzero(cmdbuf, BSIZE);
    dup2(fd_2[0],0);
    dup2(fd_3[1],1);

    sprintf(cmdbuf, "%s -t : +1.0 -2.0 --numeric --reverse", SORT_EXEC);
    /* set up pipes */

    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);
    close(fd_3[0]);
    close(fd_3[1]);
 
    if ( (execl(BASH_EXEC, BASH_EXEC, "-c", cmdbuf, (char *) 0)) < 0) 
    {
    fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
    return EXIT_FAILURE;
    }
    exit(0);
  }

  p_head = fork();
  if (p_head == 0) 
  {
    /* Fourth Child */
    char cmdbuf[BSIZE];
    bzero(cmdbuf, BSIZE);
    dup2(fd_3[0],0);
    //dup2(STDOUT_FILENO,1);  
    sprintf(cmdbuf, "%s --lines=%s", HEAD_EXEC, (argv[3]);
    //write(STDOUT_FILENO, cmdbuf, BSIZE); 
    /* set up pipes */
   
    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);
    close(fd_3[0]);
    close(fd_3[1]);

    if ( (execl(BASH_EXEC, BASH_EXEC, "-c", cmdbuf, (char *) 0)) < 0) 
    {
      fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }


/*





*/

    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);
    close(fd_3[0]);
    close(fd_3[1]);
  if ((waitpid(p_find, &status, 0)) == -1) {
    fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(p_grep, &status, 0)) == -1) {
    fprintf(stderr, "Process 2 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(p_sort, &status, 0)) == -1) {
    fprintf(stderr, "Process 3 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(p_head, &status, 0)) == -1) {
    fprintf(stderr, "Process 4 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }

  return 0;
}
