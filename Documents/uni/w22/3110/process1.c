#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */

/*
 *   CIS*3110 Code Snippets
 *
 *   Code Snippet #1: Process and Fork Example
 *      Author: Deb Stacey (see attribution to original author in References section)
 *      Date of Last Revision: Wednesday, November 25, 2015
 *      Summary: C code that forks a child process and shows
 *               the PID's for both parent and child processes.
 *      References: Based on code found at http://www.amparo.net/ce155/fork-ex.html
 */

int main ( int argc, char *argv[] ) {

   /*
    *   Variable Declarations
    */
   pid_t childpid;   /* child's process id */
   int status;       /* for parent process: child's exit status */
   int value = 100;  /* demonstration of what memory is shared */

   printf("Process and Fork Example (CIS*3110 Code Snippet #1)\n");

   /* 
    *   Create a new process
    */
   childpid = fork();

   /*
    *   Code for both parent and child processes.  Each process will only
    *   execute the code that is designated for them by their PPIDs
    */
   if ( childpid >= 0 ) {   /* fork succeeded */
   /*
    *   Child Process
    */
      if ( childpid == 0 ) {   
         printf("CHILD: I am the child process since my copy of childpid is %d and my PID is %d\n",childpid,getpid());
         printf("CHILD: My parent's PID is %d\n",getppid());
         printf("CHILD: Sleeping for 1 second...\n");
         sleep(1);
         printf("CHILD: Value = %d\n",value);
         value = value * 2 / 5;
         printf("CHILD: Value = %d\n",value);
         printf("CHILD: Enter an exit value (0 to 255): ");
         scanf("%d",&status);
         printf("CHILD: child process exiting...\n");
         exit(status);
      } else {   
   /* 
    *   Parent Process
    */
         printf("PARENT: I am the parent process since my copy of childpid is %d and my PID is %d\n",childpid,getpid());
         printf("PARENT: Value = %d\n",value);
         printf("PARENT: Waiting for my child to exit...\n");
         waitpid(childpid,&status,0);
         printf("PARENT: Child's exit code is %d\n",WEXITSTATUS(status));
         printf("PARENT: Value = %d\n",value);
         printf("PARENT: parent process exiting...\n");
         exit(0);
      }
   } else {
      perror("fork");
      exit(-1);
   }

}
