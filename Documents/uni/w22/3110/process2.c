#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <string.h>     /* Strings */

/*
 *   CIS*3110 Code Snippets
 *
 *   Code Snippet #2: Process and Fork in a Loop Example
 *      Author: Deb Stacey (see attribution to original author in References section)
 *      Date of Last Revision: Wednesday, November 25, 2015
 *      Summary: C code that employs a loop to fork child processes and shows
 *               the PID's for both parent and child processes.
 *      References: Based on code found at http://www.amparo.net/ce155/fork-ex.html
 */

int main ( int argc, char *argv[] ) {

   /*
    *   Variable Declarations
    */
   pid_t childpid;   /* child's process id */
   int status = 0;   /* for parent process: child's exit status */
   char *line;
   const char s[2] = " ";
   char *token;
   size_t length = 0;
   ssize_t nread = 0;

   line = (char *)malloc(256);

   printf("Process and Fork Example (CIS*3110 Code Snippet #2)\n");

   printf("Enter a line of text> ");
   nread = getline(&line, &length, stdin);

   while ( (strncmp(line,"exit",4) != 0) && (strncmp(line,"quit",4) != 0)  ) {
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
            printf("CHILD: I am child process %d\n",getpid());
            printf("CHILD: My parent's PID is %d\n",getppid());

            /* remove the trailing \n */
            strtok(line,"\n");

            /* get the first token */
            token = strtok(line, s);
            status++;
            printf("CHILD: %s\n",token);

            /* walk through other tokens */
            while( token != NULL ) {
               token = strtok(NULL, s);
               if ( token != NULL ) {
                  status++;
                  printf("CHILD: %s\n",token);
               }
            }
            printf("CHILD: child process exiting...\n");
            exit(status);
         } else {
      /*
       *   Parent Process
       */
            printf("PARENT: I am parent process %d\n",getpid());
            printf("PARENT: Waiting for my child to exit...\n");
            waitpid(childpid,&status,0);
            printf("PARENT: Child's exit code is %d\n",WEXITSTATUS(status));
         }
      } else {
         perror("fork");
         exit(-1);
      }

      printf("Enter a line of text> ");
      nread = getline(&line, &length, stdin);

   }
   printf("PARENT: parent process exiting...\n");
   exit(0);
}
