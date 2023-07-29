-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the menu loop that the user interacts with throughout the program
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.IO_Exceptions;
with Polylinkedlist;      use Polylinkedlist;
with Polylink;            use Polylink;
with Polymath;            use Polymath;

procedure Poly is
    choice     : Integer;
    headNode   : polyNodePtr;
    headNode2  : polyNodePtr;
    writeIndex : Integer;
    subIndex   : Integer;
begin
    loop
        -- Menu loop to appear after an operation has been completed
        Put_Line ("POLYNOMIAL Arithmetic");
        Put_Line ("Please select an option:");
        Put_Line ("1. Input a polynomial");
        Put_Line ("2. Output a polynomial");
        Put_Line ("3. Add polynomials");
        Put_Line ("4. Subtract polynomials");
        Put_Line ("5. Multiply polynomials");
        Put_Line ("6. Evaluate polynomial");
        Put_Line ("7. Exit");

        begin
            Get (choice);

            case choice is
                when 1 =>
                    readPOLY (headNode, headNode2);
                when 2 =>
                    Put ("Which polynomial would you like to print? (Enter 1 or 2): ");
                    Get (writeIndex);
                    writePOLYmain (headNode, headNode2, writeIndex);
                when 3 =>
                    addpoly (headNode, headNode2);
                when 4 =>
                    Put ("To do a - b, enter 1. For b - a, enter 2: ");
                    Get (subIndex);
                    subpoly (headNode, headNode2, subIndex);
                when 5 =>
                    multpoly (headNode, headNode2);
                when 6 =>
                    evalpoly (headNode, headNode2);
                when 7 =>
                    exit;
                when others =>
                    Put_Line ("ERROR: Invalid input, please try again");
                    New_Line;
                    New_Line;
            end case;
        exception
            when Ada.IO_Exceptions.Data_Error =>
                Put_Line ("ERROR: Invalid input, please enter an integer");
                Skip_Line;
                New_Line;
                New_Line;
        end;
    end loop;
end Poly;
