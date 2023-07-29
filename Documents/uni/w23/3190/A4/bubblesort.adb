-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: APRIL 7
-- This file contains:
-- main Bubblesort procedure to parse file and perform bubblesort
with Ada.Text_IO;                   use Ada.Text_IO;
with Ada.Strings.Unbounded;         use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Directories;               use Ada.Directories;
with Ada.Real_Time;                 use Ada.Real_Time;

procedure Bubblesort is
    type Int_Array is array (Positive range <>) of Integer;
    infp                  : File_Type;
    sline                 : Unbounded_String;
    fname                 : Unbounded_String;
    nameOK                : Boolean         := False;
    Count                 : Integer         := 0;
    Start_Time, Stop_Time : Time;
    Elapsed_Time          : Time_Span;
    outputFilename        : constant String := "sortedA.txt";
    F                     : File_Type;
begin
    Put_Line ("Enter the filename: ");
    loop
        exit when nameOK;
        Get_Line (fname);
        nameOK := Exists (To_String (fname));
    end loop;

    Open (infp, In_File, To_String (fname));

    -- Count the number of integers in the file
    while not End_Of_File (infp) loop
        Get_Line (infp, sline);
        Count := Count + 1;
    end loop;

    -- Allocate the Ints array dynamically based on the number of integers
    declare
        Ints : Int_Array (1 .. Count);
        temp : Integer;
    begin
        -- Reset file position to start of file
        Reset (infp);

        -- Read integers from file and store in Ints array
        for I in Ints'Range loop
            exit when End_Of_File (infp);
            Get_Line (infp, sline);
            Ints (I) := Integer'Value (To_String (sline));
        end loop;

        -- perform bubblesort algorithm
        Start_Time := Clock;
        for K in 0 .. Ints'Length loop
            for L in 1 .. Ints'Length - K - 1 loop
                --  traverse the array from 0 to n-i-1
                -- Swap if the element found is greater
                -- than the next element
                if Ints (L) > Ints (L + 1) then
                    temp         := Ints (L);
                    Ints (L)     := Ints (L + 1);
                    Ints (L + 1) := temp;
                end if;
            end loop;
        end loop;
        Stop_Time    := Clock;
        Elapsed_Time := (Stop_Time - Start_Time) * 1_000;
        Put_Line
           ("Elapsed time: " & Duration'Image (To_Duration (Elapsed_Time)) &
            " ms");
        Create (F, Out_File, outputFilename);

        -- output to file
        for J in 1 .. Ints'Length loop
            Put_Line (F, Ints (J)'Image);
        end loop;
        Close (F);
        Put ("sortedA.txt has been created");
    end;
end Bubblesort;
