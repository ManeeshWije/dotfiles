#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */

/*
 *   CIS*3110 Code Snippets
 *
 *   Code Snippet #3: Fork and Exec Example
 *      Author: Deb Stacey (see attribution to original author in References section)
 *      Date of Last Revision: Thursday, January 21, 2021
 *      Summary: C code that forks a child process and shows
 *               the PID's for both parent and child processes and then runs a Unix command
 */

int main ( int argc, char *argv[] ) {

   /*
    *   Variable Declarations
    */
   pid_t childpid;   /* child's process id */
   int status;       /* for parent process: child's exit status */
   char *parameters[10] = {"ls", "-tl"};
   char pathbuf[1000];
   long argMax;

   printf("Process and Fork Example (CIS*3110 Code Snippet #3)\n");

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
         printf("CHILD %d of parent %d running %s %s\n",getpid(),getppid(),parameters[0], parameters[1]);

         confstr(_CS_PATH, pathbuf, 1000);
	 printf ( "PATH = %s\n", pathbuf );

	 argMax = sysconf(_SC_ARG_MAX);
	 printf ( "arg max = %ld\n", argMax );

         status = execvp ( "ls", parameters );
         exit(status);
      } else {   
   /* 
    *   Parent Process
    */
         printf("PARENT %d waiting for  child %d\n",getpid(),childpid);
         waitpid(childpid,&status,0);
         printf("PARENT: Child's exit code is %d\n",WEXITSTATUS(status));
         printf("PARENT: parent process exiting...\n");
         exit(0);
      }
   } else {
      perror("fork");
      exit(-1);
   }

   exit(0);
}
