-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the implementation for the main subroutines that read and write user input as well as some helper subroutines
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.IO_Exceptions;

package body Polylink is
    -- This procedure will read in multiple values for 2 polynomials
    procedure readPOLY
       (headNode : in out polyNodePtr; headNode2 : in out polyNodePtr)
    is
        userCoeff  : Integer;
        userPower  : Integer;
        overwrite  : Integer;
        isNegative : Integer;
    begin

        Put ("You may enter 2 polynomials, if already inputted, you will be asked to overwrite the corresponding polynomial");
        New_Line;
        Put ("NOTE: To enter just a coefficient, use a 0 exponent");
        New_Line;
        Put ("NOTE: If you enter the same exponent, the coefficients will be added together");
        New_Line;
        New_Line;

        -- if polynomials already exist, delete them and user inputs new one
        if headNode /= null and headNode2 /= null then

            Put ("Which polynomial would you like to overwrite? (Enter 1 or 2): ");
            Get (overwrite);

            -- if deleted the first poly we want to override headnode
            if overwrite = 1 then
                deletePolyNode (headNode);

                Put ("Enter information for 1st polynomial");
                New_Line;

                loop
                    isNegative := 0;

                    Put ("Enter Exponent (Enter 999 to move onto second polynomial): ");
                    Get (userPower);

                    if userPower = 999 then
                        exit;
                    elsif userPower < 0 then
                        isNegative := 1;
                    end if;

                    Put ("Enter corresponding coefficient: ");
                    Get (userCoeff);

                    if isNegative = 1 then
                        Put ("ERROR: cannot input negative exponent");
                        New_Line;
                        New_Line;
                    else
                        addPolyNode (userPower, userCoeff, true, headNode);
                    end if;
                end loop;

                sortPOLY (headNode);
                writePOLY (headNode);
                -- if deleted the second poly we want to override headnode2
            elsif overwrite = 2 then
                deletePolyNode (headNode2);

                Put ("Enter information for 2nd polynomial");
                New_Line;

                loop
                    isNegative := 0;

                    Put ("Enter Exponent (Enter 999 to finish): ");
                    Get (userPower);

                    if userPower = 999 then
                        exit;
                    elsif userPower < 0 then
                        isNegative := 1;
                    end if;

                    Put ("Enter corresponding coefficient: ");
                    Get (userCoeff);

                    if isNegative = 1 then
                        Put ("ERROR: cannot input negative exponent");
                        New_Line;
                        New_Line;
                    else
                        addPolyNode (userPower, userCoeff, true, headNode2);
                    end if;
                end loop;

                sortPOLY (headNode2);
                writePOLY (headNode2);
            else
                Put ("ERROR: There are 2 polynomials, please enter 1 or 2");
                New_Line;
                New_Line;
            end if;
        else
            -- when adding nodes, we ask for exponent then coefficient
            -- the user can input 999 to move onto the second and then to finish
            Put ("Enter information for 1st polynomial");
            New_Line;
            loop
                isNegative := 0;

                Put ("Enter Exponent (Enter 999 to move onto second polynomial): ");
                Get (userPower);

                if userPower = 999 then
                    exit;
                elsif userPower < 0 then
                    isNegative := 1;
                end if;

                Put ("Enter corresponding coefficient: ");
                Get (userCoeff);

                if isNegative = 1 then
                    Put ("ERROR: cannot input negative exponent");
                    New_Line;
                    New_Line;
                else
                    addPolyNode (userPower, userCoeff, true, headNode);
                end if;
            end loop;

            sortPOLY (headNode);
            writePOLY (headNode);

            Put ("Enter information for 2nd polynomial");
            New_Line;
            loop
                isNegative := 0;

                Put ("Enter Exponent (Enter 999 to finish): ");
                Get (userPower);

                if userPower = 999 then
                    exit;
                elsif userPower < 0 then
                    isNegative := 1;
                end if;

                Put ("Enter corresponding coefficient: ");
                Get (userCoeff);

                if isNegative = 1 then
                    Put ("ERROR: cannot input negative exponent");
                    New_Line;
                    New_Line;
                else
                    addPolyNode (userPower, userCoeff, true, headNode2);
                end if;
            end loop;

            sortPOLY (headNode2);
            writePOLY (headNode2);
        end if;
    exception
        when Ada.IO_Exceptions.Data_Error =>
            Put_Line ("ERROR: Invalid input. Please try again.");
            New_Line;
            New_Line;
            Skip_Line;
    end readPOLY;

    -- This procedure will print to the console, polynomials with the correct symbols and signs
    procedure writePOLY (headNode : in polyNodePtr) is
        tempNode  : polyNodePtr;
        polyCount : Integer := 0;
    begin
        if headNode = null then
            Put ("ERROR: head node is null");
            New_Line;
            New_Line;
        else

            tempNode := headNode;

            while tempNode /= null loop
                -- we want to print the signs when exists more than 1 node
                if polyCount /= 0 then
                    -- to indicate positive coefficient
                    -- since the use will enter '-' for negative, that covers negative
                    if tempNode.coeff > 0 then
                        Put ("+");
                    end if;
                end if;

                -- make sure we dont print 0s on exp or 1s on coeff
                if tempNode.coeff /= 0 then
                    if tempNode.coeff = 1 then
                        if tempNode.power = 1 then
                            Put ("x");
                        -- x^0 will always result in coeff^1 which is just the coeff
                        elsif tempNode.power = 0 then
                            Put (Integer'Image (tempNode.coeff));
                        else
                            Put ("x^" & Integer'Image (tempNode.power));
                        end if;
                    elsif tempNode.coeff = -1 then
                        if tempNode.power = 1 then
                            Put ("-x");
                        elsif tempNode.power = 0 then
                            Put (Integer'Image (tempNode.coeff));
                        else
                            Put ("-x^" & Integer'Image (tempNode.power));
                        end if;
                    else
                        if tempNode.power = 1 then
                            Put (Integer'Image (tempNode.coeff) & "x");
                        -- x^0 will always result in coeff^1 which is just the coeff
                        elsif tempNode.power = 0 then
                            Put (Integer'Image (tempNode.coeff));
                        else
                            Put (Integer'Image (tempNode.coeff) & "x^" &
                                Integer'Image (tempNode.power));
                        end if;
                    end if;
                end if;
                tempNode  := tempNode.next;
                polyCount := polyCount + 1;
            end loop;
            New_Line;
        end if;
    exception
        when Ada.IO_Exceptions.Data_Error =>
            Put_Line ("ERROR: Invalid input. Please try again.");
            New_Line;
            New_Line;
            Skip_Line;
    end writePOLY;

    -- This procedure will sort a polynomial from greatest to least based on exponent value
    procedure sortPOLY (headNode : polyNodePtr) is
        slow      : polyNodePtr;
        fast      : polyNodePtr;
        tempExp   : Integer;
        tempCoeff : Integer;
    begin
        if headNode = null then
            Put ("ERROR: list is empty, cannot sort");
            New_Line;
            New_Line;
        else

            slow := headNode;

            -- we will sort using a modified bubble sort algo
            -- slow will always be behind the fast pointer
            while slow /= null loop
                fast := slow.next;
                while fast /= null loop
                    -- we want to sort on power values from greatest to least
                    if slow.power < fast.power then
                        tempExp    := slow.power;
                        tempCoeff  := slow.coeff;
                        slow.power := fast.power;
                        slow.coeff := fast.coeff;
                        fast.power := tempExp;
                        fast.coeff := tempCoeff;
                    end if;
                    fast := fast.next;
                end loop;
                slow := slow.next;
            end loop;
        end if;
    end sortPOLY;

    -- this procedure is a modified writePOLY that exists when the user wants to output a specific polynomial from the menu
    -- only difference is we take in an index which the user provides
    procedure writePOLYmain
       (headNode : in polyNodePtr; headNode2 : in polyNodePtr;
        index    : in Integer)
    is
        tempNode  : polyNodePtr;
        polyCount : Integer := 0;
    begin
        if index = 1 then
            if headNode = null then
                Put ("ERROR: head node is null");
                New_Line;
                New_Line;
            else
                tempNode := headNode;
            end if;
        elsif index = 2 then
            if headNode2 = null then
                Put ("ERROR: head node is null");
                New_Line;
                New_Line;
            else
                tempNode := headNode2;
            end if;
        else
            Put ("ERROR: There are only 2 polynomials, please enter 1 or 2");
            New_Line;
            New_Line;
        end if;

        while tempNode /= null loop
            -- we want to print the signs when exists more than 1 node
            if polyCount /= 0 then
                -- to indicate positive coefficient
                -- since the use will enter '-' for negative, that covers negative
                if tempNode.coeff > 0 then
                    Put ("+");
                end if;
            end if;

            -- make sure we dont print 0s on exp or 1s on coeff
            if tempNode.coeff /= 0 then
                if tempNode.coeff = 1 then
                    if tempNode.power = 1 then
                        Put ("x");
                        -- x^0 will always result in coeff^1 which is just the coeff
                    elsif tempNode.power = 0 then
                        Put (Integer'Image (tempNode.coeff));
                    else
                        Put ("x^" & Integer'Image (tempNode.power));
                    end if;
                elsif tempNode.coeff = -1 then
                    if tempNode.power = 1 then
                        Put ("-x");
                    elsif tempNode.power = 0 then
                        Put (Integer'Image (tempNode.coeff));
                    else
                        Put ("-x^" & Integer'Image (tempNode.power));
                    end if;
                else
                    if tempNode.power = 1 then
                        Put (Integer'Image (tempNode.coeff) & "x");
                        -- x^0 will always result in coeff^1 which is just the coeff
                    elsif tempNode.power = 0 then
                        Put (Integer'Image (tempNode.coeff));
                    else
                        Put (Integer'Image (tempNode.coeff) & "x^" &
                            Integer'Image (tempNode.power));
                    end if;
                end if;
            end if;
            tempNode  := tempNode.next;
            polyCount := polyCount + 1;
        end loop;
        New_Line;
    end writePOLYmain;
end Polylink;
