-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: APRIL 7
-- This file contains:
-- main Dobosort procedure to parse file and perform dobosort
-- getNextGap procedure which finds the next gap using shrink factor
with Ada.Text_IO;                   use Ada.Text_IO;
with Ada.Strings.Unbounded;         use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Directories;               use Ada.Directories;
with Ada.Real_Time;                 use Ada.Real_Time;

procedure Dobosort is
    type Int_Array is array (Positive range <>) of Integer;
    infp                  : File_Type;
    sline                 : Unbounded_String;
    fname                 : Unbounded_String;
    nameOK                : Boolean         := False;
    Count                 : Integer         := 0;
    swapped               : Boolean;
    Start_Time, Stop_Time : Time;
    Elapsed_Time          : Time_Span;
    outputFilename        : constant String := "sortedA.txt";
    F                     : File_Type;

    -- procedure to calculate next gap position
    procedure getNextGap (gap : in out Integer) is
    begin
        -- shrink gap by shrink factor
        gap := (gap * 10) / 13;
        if gap < 1 then
            gap := 1;
        end if;
    end getNextGap;

    -- helper procedure to swap two integers
    procedure swap (X, Y : in out Integer) is
        Temp : Integer;
    begin
        Temp := X;
        X    := Y;
        Y    := Temp;
    end swap;

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
        Ints    : Int_Array (1 .. Count);
        tempGap : Integer;
    begin
        -- Reset file position to start of file
        Reset (infp);

        -- Read integers from file and store in Ints array
        for I in Ints'Range loop
            exit when End_Of_File (infp);
            Get_Line (infp, sline);
            Ints (I) := Integer'Value (To_String (sline));
        end loop;

        Start_Time := Clock;
        -- perform dobosort algorithm
        tempGap    := Count;
        -- keep running while gap is more than 1 and last iteration caused a swap
        swapped    := True;

        while tempGap /= 1 or swapped loop
            getNextGap (tempGap);
            -- init to false so we can check if swap happened
            swapped := False;
            -- compare all elements with current gap
            for i in 1 .. Count - tempGap loop
                if Ints (i) > Ints (i + tempGap) then
                    swap (Ints (i), Ints (i + tempGap));
                    swapped := True;
                end if;
            end loop;
        end loop;
        Stop_Time := Clock;

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
end Dobosort;
