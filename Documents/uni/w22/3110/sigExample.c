#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <signal.h>      /* Signals */
/*
 *   CIS*3110 Code Snippets
 *
 *   Code Snippet #4: Signals Example
 *      Author: Deb Stacey 
 *      Date of Last Revision: Sunday, January 16, 2022
 *      Summary: C code that forks a child process that has its
 *               parent kill it after the number of seconds on the command line.
 *      Compile and Run: 
 *         gcc -o signalExample signalExample.c
 *         ./signalExample 5
 *      - if there is no command line argument for this program the 
 *        default is 1 second.
 */

void sigquit(int signo) {
    printf("CHILD (%d): termination request from PARENT (%d)...ta ta for now...\n", getpid(), getppid());
    exit(0);
}

int main( int argc, char *argv[] ) {

    int seconds = 0;
    int waitSecs = 1;   /* default to 1 second of waiting */
    struct sigaction sigact;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);

    if ( argc >= 2 ) {
       waitSecs = atoi ( argv[1] );
    }

    sigact.sa_handler = sigquit;
    if ( sigaction(SIGQUIT, &sigact, NULL) < 0 ) {
        perror("sigaction()");
        exit(1);
    }

    pid_t pid;
    /* get child process */
    if ( (pid = fork()) < 0 ) {
        perror("fork");
        exit(1);
    }

    if ( pid == 0 ) {
        /* child */
	printf ( "CHILD: my process id is %d\n", getpid() );
        for ( ;; ) { /* loop forever */
            printf ( "Second %d\n", seconds );
            seconds++;
            sleep ( 1 );
        }
    } else {
        /* parent */
        sigact.sa_handler = SIG_DFL;
        sigaction(SIGQUIT, &sigact, NULL);
        /* pid holds the id of child */
        sleep(waitSecs); /* pause for waitSecs secs */
        printf( "PARENT (%d): sending SIGQUIT/kill to %d after %d seconds\n", getpid(), pid, waitSecs );
        kill(pid,SIGQUIT);
    }

    return 0;
}

