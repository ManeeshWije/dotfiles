NAME: MANEESH WIJEWARDHANA
ID: 1125828
EMAIL: mkandage@uoguelph.ca
COURSE: CIS\*3110
DUE DATE: APRIL 7, 2022

ASSIGNMENT 3 - MEMORY MANAGEMENT

# Compiling and Running

- Run make and then run the executable like this: ./holes <file> <first/best/worst/next>
- You can choose what algorithm to run but make sure filename is present and only 1 name of algorithm is present in the call

# Implementation

- Using a linked list to act as a queue using functions such as enqueue and dequeue (items are added in at the end and removed from the front)
- 1 queue for processes and their block size and 1 queue for the memory list that contains 1024 spots
- Swapping back in and out of process queue and memory list based on what type of algorithm is chosen

# Limitations

- file CANNOT contain a newline at the end!! Last entry should be the final contents of the text file
- EX:
  - 1 130
  - 2 99
  - 3 200 (NO NEWLINE AFTER THIS)
