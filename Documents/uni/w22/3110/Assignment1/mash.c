#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <string.h>     /* Strings */
#include <signal.h>     /* Signals */

int main(int argc, char *argv[]) { 
  // argc for arg count and argv for command
  char *argv2[100]; //command after pipe
  pid_t childpid;  // child's process id
  pid_t pid2; // for pipe func, check for child or parent
  int status = 0;   // for parent process: child's exit status
  char *line; // command line
  const char s[2] = " "; // delimiter for strtok
  char *token; // each token for strtok
  size_t length = 0; // length of string
  ssize_t nread = 0; // for getline()
  char dir[100]; // cd target
  char *myHISTFILE; // history
  char *myPATH; // path
  char *myHOME; // home
  char c; // readfile

  int background = 0; // bg check
  int hist = 0; // history check
  int histClear = 0; // history clear check
  char histNumber[100]; // history number check
  int out = 0; // output check
  int in = 0; // input check
  int fd[2]; // break up pipe
  int p = 0; // pipe check
  int cd = 0; // cd check
  int outPos = 0; // pos of >
  int inPos = 0; // pos of <
  int bgPos = 0; // pos of &
  int pipePos = 0; // pos of |
  int pipeOut = 0; // pos of pipe with >
  int pipeIn = 0; // pos of pipe with <
  int count = 0; // count when setting in and out positions

  // allocating space for command line, path, history, and home
  line = (char *)malloc(500);
  myPATH = (char *)malloc(500);
  myHISTFILE = (char *)malloc(500);
  myHOME = (char *)malloc(500);

  // this is where the history file will be located
  strcpy(myHISTFILE, getenv("HOME"));
  strcat(myHISTFILE, "/.mash_history");
  // printf("HISTORY: %s\n", myHISTFILE);

  // only got this far for myPATH
  strcpy(myPATH, getenv("PATH"));
  // printf("PATH: %s\n", myPATH);

  // only got this far for myHOME
  strcpy(myHOME, getenv("HOME"));
  // printf("HOME: %s\n", myHOME);

  // initial prompt
  printf("Welcome to mash\n");
  while (1) {
    // prompt
    printf("%s> ", getcwd(dir, 100));
    
    // read command line
    nread = getline(&line, &length, stdin);

    //removing newline
    strtok(line, "\n");

    // opening history file for append and create if it doesnt exist
    FILE *fptr = fopen(myHISTFILE, "a");

    // writing each command thats written in to the file
    fprintf(fptr, "%s\n", line);  
    
    // close file
    fclose(fptr);

    // checking if user wants to exit shell
    if (strncmp(line, "exit", 4) == 0) {
      // kill all processes
      printf("mash terminating...\n");
      kill(0, SIGKILL);
      exit(EXIT_SUCCESS);
    }

    // tokenize input on every space
    token = strtok(line, s);
    int i = 0;
    while (token != NULL) {
      argv[i] = token;      
      token = strtok(NULL, s);
      i++;
    }
    
    // set last value to NULL for execvp
    argv[i] = NULL; 

    // count for args
    argc = i; 

    // check for cd
    if (strcmp(argv[0], "cd") == 0) {
      cd = 1;
    }
    // check for history
    if (strcmp(argv[0], "history") == 0) {
      hist = 1;
      strcpy(histNumber, argv[argc - 1]);
      // now check for flags
      if (strcmp(argv[argc - 1], "-c") == 0) {
        histClear = 1;
      }
    }

    // loop through count for args
    // do all character checks here
    for (int j = 0; j < argc; j++) {
      // if background
      if (strcmp(argv[j], "&") == 0) {
        // printf("this is a background process\n");
        // set bg var
        background = 1;
        // record pos of &
        bgPos = j;
        // argv[argc - 1] = NULL;
      } 
      // check for 2 or more arguments
      if (argc >= 2) {
        // if output
        if (strcmp(argv[j], ">") == 0) {
          // printf("this is redirecting output\n");
          // set output var
          out = 1; 
          // record position of char
          outPos = j;
          // if pipe was also set, set pipeout
          if (p == 1) {
            pipeOut = 1;
          }
        }
        // if input
        if (strcmp(argv[j], "<") == 0) {
          // printf("this is redirecting input\n");
          // set input var
          in = 1;
          // record position of char
          inPos = j;
          // if pipe was also set, set pipein
          if (p == 1) {
            pipeIn = 1;
          }
        }
        //if pipe command
        if (strcmp(argv[j], "|") == 0) {
          // printf("this is a pipe\n");
          // argv2[0] = argv[argc - 1];
          // argv2[1] = NULL;
          // set pipe var
          p = 1;
          // record position of char
          pipePos = j;
        }
      }
    }
    
    // if pipe was set
    if (p == 1) {
      count = 0;
      // loop through args and set positions of < and > if they are to the left or right of pipe
      for (int k = pipePos + 1; k < argc; k++) {
        argv2[count] = argv[k];
        if (strcmp(argv2[count], ">") == 0) {
          outPos = count;
        } else if (strcmp(argv2[count], "<") == 0) {
          inPos = count;
        }
        count++;
      }
      argv2[count] = NULL;
    }

    // printf("%s\n", argv[0]);
    // printf("%s\n", argv2[0]);

    // fork child
    childpid = fork(); 

    if (childpid >= 0) {
      // this is the child process
      if (childpid == 0) {
        // if out was set, we know its output redirected to a file
        if (out == 1) {
          // open file for reading and create if its not there
          FILE *fp = freopen(argv[argc - 1], "w+", stdout);
          // delete symbol for execvp
          argv[argc - 2] = NULL;
          status = execvp(argv[0], argv);
          exit(status);
          fclose(fp);
        } else if (in == 1) {
          // if in was set, we know its input redirected from a file
          // open file for reading but file has to exist
          FILE *fp = freopen(argv[argc - 1], "r+", stdin);
          // delete symbol for execvp
          argv[argc - 2] = NULL; 
          status = execvp(argv[0], argv);
          exit(status);
          fclose(fp);
        } else if (p == 1) { // if pipe symobl
          // configure pipe
          if (pipe(fd) == -1) {
            return 1;
          }
          argv[pipePos] = NULL;
          // fork child
          pid2 = fork();
          // fork failed
          if (pid2 < 0) { 
            perror("fork");
            kill(0, SIGKILL);
            exit(-1);
            // this is the child process
          } else if (pid2 == 0) { 
            // setting pipe for output
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            // if out is set and no pipe, use freopen to open file with w+ and stdout
            if (out == 1 && pipeOut == 0) {
              FILE *fp = freopen(argv[pipePos - 1], "w+", stdout);
              // remove symbol for execvp
              argv[outPos] = NULL; 
              status = execvp(argv[0], argv);
              fclose(fp);
              // if in is set and no pipe, use freopen to open file for reading stdin
            } else if (in == 1 && pipeIn == 0) {
              FILE *fp = freopen(argv[pipePos - 1], "r+", stdin);
              // remove symbol for execvp
              argv[inPos] = NULL;
              status = execvp(argv[0], argv);
              fclose(fp);
            } else {
              status = execvp(argv[0], argv);
            }
          } else { //parent
            // setting pipe for input
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            // wait for child first
            waitpid(pid2, NULL, 0);
            waitpid(childpid, NULL, 0);
            // if out is set and pipe is found on output side
            if (out == 1 && pipeOut == 1) {
              // use argv2 which holds 2nd command
              FILE *fp = freopen(argv2[count - 1], "w+", stdout);
              // remove symbol for execvp
              argv2[outPos] = NULL; 
              // exec 2nd command
              status = execvp(argv2[0], argv2);
              fclose(fp);
              // if in is set and pipe is found on input side
            } else if (in == 1 && pipeIn == 1) {
              // use argv2 which holds second command
              FILE *fp = freopen(argv2[count - 1], "r+", stdin);
              // remove symbol for execvp
              argv2[inPos] = NULL;
              // exec 2nd command
              status = execvp(argv2[0], argv2);
              fclose(fp);
            } else {
              // if no flags set, execute 2nd command
              status = execvp(argv2[0], argv2);
            }
          }
          close(fd[0]);
          close(fd[1]);
          exit(status);
        } else { // no pipe
          // if cd was the command, we use chdir to change directories
          if (cd == 1) {
            chdir(argv[argc - 1]);
          } else if (hist == 1 && histClear == 0) {
            // if history was the command without the -c flag
            // open the hist file that we have been appending to all this time 
            fptr = fopen(myHISTFILE, "r");
            if (fptr == NULL) {
              printf("Cannot open file \n");
              exit(0);
            } 
            // number for history
            int fileCount = 1; 
            // this is the number at the end if user puts it
            int n = atoi(argv[argc - 1]);
            // if no number was set, n would be 0 in which case we just print the contents regularly
            if (n == 0) {
              while (fgets(line, 100, fptr)) {
                printf(" %d  %s", fileCount, line);
                fileCount++;
              }
              // if there was a number, we use fseek to go to the end of file and print n lines
            } else {
              while (fgets(line, 100, fptr)) {
                fileCount++;
              }
              long int pos;
              int counter = 0;
              char b[100];
              fseek(fptr, 0, SEEK_END);
              pos = ftell(fptr);

              while (pos) {
                fseek(fptr, --pos, SEEK_SET);
                // once counter = to user inputted number we can stop there 
                if (fgetc(fptr) =='\n') {   
                  if (counter++ == n) 
                  break;
                }
              }
              // print contents
              while (fgets(b, sizeof(b), fptr)) {
                printf(" %d  %s", fileCount, b);
                fileCount++;
              }
            }
            fclose(fptr);
            // if -c flag was used, simply overwrite the file which will delete all contents
          } else if (hist == 1 && histClear == 1) {
            fptr = fopen(myHISTFILE, "w");
            if (fptr == NULL) {
              printf("Cannot open file \n");
              exit(0);
            } 
            fclose(fptr);
          } else { // check for background first
            if (background == 1) {
              argv[bgPos] = NULL;
            }
            // otherwise execute command like normal
            status = execvp(argv[0], argv);
            fprintf(stderr, "mash: %s: command not found\n", argv[0]);
            exit(status);
          }
        }
        // Parent process
      } else {
        // waitpid if it was a background process
        if (background == 1) {
          waitpid(childpid, &status, WNOHANG);
          background = 0;
        } else { // otherwise wait normally
          wait(NULL);
        }
      } 
    } else { //if fork fails
      perror("fork");
      kill(0, SIGKILL);
      exit(-1);
    }
    // resetting my set vars and pos vars
    out = 0;
    in = 0;
    p = 0;
    cd = 0;
    hist = 0;
    histClear = 0;
    outPos = 0; 
    inPos = 0;
    pipePos = 0; 
    pipeOut = 0;
    pipeIn = 0;
    count = 0;
    bgPos = 0;
  }
  // freeing malloced space
  free(line);
  free(myPATH);
  free(myHISTFILE);
  free(myHOME);
}
