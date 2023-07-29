      *> NAME: MANEESH WIJEWARDHANA
      *> ID: 1125828
      *> COURSE: CIS*3190
      *> DUE DATE: MARCH 27, 2023
      *> This file contains the source code for the roman numeral converter

       identification division.
       program-id. roman-numeral.

       environment division.
           input-output section.  
      *> specify the name of the input file for dynamic user input
           file-control.
           select input-file assign to dynamic userFile
           organization is line sequential.

       data division.
           file section.
           fd input-file.
      *> define the description of the file record that is read
               01 input-record.
                   05 num   pic x(25).

           working-storage section.
      *> space for reading in the file
           01 input-data-record.
               02 in-r      pic x(15).
               02 filler    pic x(65).

      *> space for storing the roman numeral
           01 array-area.
               02 r         pic x(1) occurs 15 times.

      *> title in our output
           01 output-title-line.
               02 filler    pic x(28) value
               "  ROMAN NUMBER EQUIVALENTS  ".

      *> underline in our output
           01 output-underline-1.
               02 filler    pic x(30) value
               "------------------------------". 

      *> two headings in our output to show the roman number and decimal
           01 output-column-headings.
               02 filler    pic x(14) value
               "  ROMAN NUMBER". 
               02 filler    pic x(16) value
               "    DEC. EQUIV.". 

      *> underline in our output
           01 output-underline-2.
               02 filler    pic x(30) value
               " ---------------------------- ". 

      *> variable to indicate end of file
           77 eof-switch    pic 9   value 1.
           77 switch        pic 9.
           77 n             pic s9(2) comp.
           77 sum1          pic s9(8) comp.
           77 i             pic s9(2) comp.
           77 prev          pic s9(4) comp.
           77 d             pic s9(4) comp.

      *> error messages when invalid roman numeral is read
           01 output-error-mess.
               02 filler    pic x       value space.
               02 out-er-r  pic x(15).
               02 filler    pic x(24)   value
               "   ILLEGAL ROMAN NUMERAL". 

           01 output-table-record.
               02 filler    pic x       value space.
               02 out-r     pic x(15).
               02 filler    pic x(3)    value spaces.
               02 v         pic z(9).

      *> variable that the user will write for the name of file
           01 userFile      pic x(30).

      *> roman numeral key
           01 output-row-1 pic x(28) value "Roman Numeral to Decimal Key".
           01 output-row-2 pic x(15) value "I = 1".
           01 output-row-3 pic x(15) value "V = 5".
           01 output-row-4 pic x(15) value "X = 10".
           01 output-row-5 pic x(15) value "L = 50".
           01 output-row-6 pic x(15) value "C = 100".
           01 output-row-7 pic x(15) value "D = 500".
           01 output-row-8 pic x(15) value "M = 1000".

       procedure division.
           display output-row-1
           display output-row-2
           display output-row-3
           display output-row-4
           display output-row-5
           display output-row-6
           display output-row-7
           display output-row-8

           display "Enter name of the file containing roman numerals: ".

           accept userFile.
           display output-underline-1
           display output-title-line
           display output-underline-1
           display output-column-headings
           display output-underline-2

      *> after displaying the headings, open file and read it in
           open input input-file.
           read input-file into input-data-record
               at end move zero to eof-switch.
           perform proc-body
               until eof-switch is equal to zero.
           close input-file.
       stop run.
     
       proc-body.
           move in-r to array-area.
           move 1 to n.

           perform search-loop
               until r(n) is equal to space.

           compute n = n - 1.

           perform conv.

           if switch is equal to 1 then
               move sum1 to v 
               move array-area to out-r
               display output-table-record
           else continue
           end-if.
           read input-file into input-data-record
               at end move zero to eof-switch
           end-read.
     
       search-loop.
           compute n = n + 1.
     
       conv. 
           move zero to sum1.
           move 1001 to prev.
           move 1 to switch.

           perform conversion-loop

           varying i from 1 by 1

           until i is greater than n or 
               switch is equal to 2.
     
       conversion-loop.
      *> logic for converting roman numeral to decimal equivalent
           if r(i) is equal to "I" then
               move 1 to d
           else if r(i) is equal to "V"
               move 5 to d
           else if r(i) is equal to "X"
               move 10 to d
           else if r(i) is equal to "L"
               move 50 to d
           else if r(i) is equal to "C"
               move 100 to d
           else if r(i) is equal to "D"
               move 500 to d
           else if r(i) is equal to "M"
               move 1000 to d
      *> not valid so set switch to 2
           else move 2 to switch
               move array-area to out-er-r
               display output-error-mess
           end-if.

           compute sum1 = sum1 + d.

           if d is greater than prev then
               compute sum1 = sum1 - 2 * prev
           else continue
           end-if.

           move d to prev.
