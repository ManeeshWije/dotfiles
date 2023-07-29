-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: APRIL 7
-- This file contains:
-- main QSort procedure to parse file
-- realQSort procedure that performs the quick sort algorithm
-- partition procedure that finds the partition position
-- swap helper procedure

with Ada.Text_IO;                   use Ada.Text_IO;
with Ada.Strings.Unbounded;         use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Directories;               use Ada.Directories;
with Ada.Real_Time;                 use Ada.Real_Time;

-- parses file and calls quick sort algorithm
procedure QSort is
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
    -- recursive quick sort algorithm
    procedure realQSort
       (Ints : in out Int_Array; low : in Integer; high : in Integer)
    is
        res : Integer := 0;
        -- procedure to find the partition position
        procedure partition
           (Ints   : in out Int_Array; low : in Integer; high : in Integer;
            result : in out Integer)
        is
            pivot : Integer;
            i     : Integer;
            -- helper procedure to swap two integers
            procedure swap (X, Y : in out Integer) is
                Temp : Integer;
            begin
                Temp := X;
                X    := Y;
                Y    := Temp;
            end swap;
        begin
            pivot := Ints (high);
            -- Pointer for greater element
            i     := low - 1;

            -- Traverse and compare with pivot
            for j in low .. high loop
                -- If smaller than pivot, swap with greater element which is i
                if Ints (j) < pivot then
                    i := i + 1;
                    swap (Ints (i), Ints (j));
                end if;
            end loop;

            -- swap pivot with greater elements specified by i
            swap (Ints (i + 1), Ints (high));

            -- return position where partition is done
            result := i + 1;
        end partition;

    begin
        if (low < high) then
            -- find pivot element such that element smaller is on left and greater is on right
            partition (Ints, low, high, res);
            realQSort (Ints, low, res - 1);
            realQSort (Ints, res + 1, high);
        end if;
    end realQSort;

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
        realQSort (Ints, 1, Count);
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
        Put("sortedA.txt has been created");
    end;
end QSort;
