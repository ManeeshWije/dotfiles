# mash (maneesh's shell)

## Compilation and Running

```
make
./mash
```

## Functions Implemented

-   "exit" command which terminates the shell and kills all child processes
-   A command with no arguments such as "ls"
-   A command with arguments such as "ls -lt"
-   A command with or without arguments executed in background using "&"
-   A command with or without arguments whose output is redirected to a file using ">"
-   A command with or without arguments whose input is redirected from a file using "<"
-   A command with or without arguments whose output is piped to the input of another command using "|"
    -   multiple redirects using pipe works
-   The history built-in command with flags like -c and n numbers
    -   .mash_history gets made in the users home directory
-   The cd built-in command

## Assumptions Made

-   "&" has to be at the end of the command statement for bg processes
-   Commands need to be spaced out properly so sort<foo will not work, sort < foo will

## How I Tested The Functions

-   "exit" was tested by calling multiple other commands as well as bg processes then typing exit would exit the shell as well as kill any background, zombie, and child processes
-   No arg command was tested by typing in commands in /bin and /usr/bin and making sure the output was identical to bash
    -   ls, pwd, mkdir folder, cat filename, vim filename, etc
-   Command with args was tested by typing in appropriate flags for different commands and making sure the output was identical to bash,
    -   ls -lt, ls -a, rm -rf, etc
-   A command in the background using & was tested using sleep n &, making sure when typing "ps" the process was still there until n number of seconds
    -   sleep 3 &, ls &, pwd &, etc
-   Output redirect to file was tested using ls -lt > filename and making sure the file contents mirrored the command output
    -   ls -lt > filename, cat filename > filename2, pwd > filename
-   Input redirect from file was tested using sort < filename and making sure the contents were sorted
    -   sort < filename
-   Piping was tested using functions such as sort, more, less, cat, wc, etc
    -   ls -lt | more, cat filename | sort, ls -lt | wc, head -4 < foo | sort > sorted
-   "history" was tested by making sure the output was identical to bash's history command
-   "cd" was tested by making sure navigation results weer accurate and was the same functionality as bash

## Limitations

-   Could not implement "export" command
-   Could not implement proper env variables such as myHOME, myPATH, myHISTFILE (history still works and I was only able to print the home and path directories)
-   Could not implement a profile file on init
-   Multiple redirects may not work but will work using pipe command
