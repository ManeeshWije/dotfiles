-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the implementations for the main subroutines to perform polynomial math as well as extra helper subroutines

with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Polylink;            use Polylink;

package body Polymath is
    procedure addpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr)
    is
        tempNode  : polyNodePtr;
        tempNode2 : polyNodePtr;
        newNode   : polyNodePtr;
    begin
        if headNode = null or headNode2 = null then
            Put ("ERROR: head node is null, cannot add, if you would like to add the same polynomial, please input it");
            New_Line;
            New_Line;
        else

            tempNode  := headNode;
            tempNode2 := headNode2;

            -- loop through both lists and add the coeff if the powers are the same then move on
            while tempNode /= null and tempNode2 /= null loop
                if tempNode.power = tempNode2.power then
                    addPolyNode
                       (tempNode.power, tempNode.coeff + tempNode2.coeff,
                        false, newNode);
                    tempNode  := tempNode.next;
                    tempNode2 := tempNode2.next;
                -- if the power is bigger then we just add a new node with power
                elsif tempNode.power > tempNode2.power then
                    addPolyNode
                       (tempNode.power, tempNode.coeff, false, newNode);
                    tempNode := tempNode.next;
                else
                    -- otherwise we add the second list node with that power
                    addPolyNode
                       (tempNode2.power, tempNode2.coeff, false, newNode);
                    tempNode2 := tempNode2.next;
                end if;
            end loop;

            -- add remaining terms from first and second polynomial
            while tempNode /= null loop
                addPolyNode (tempNode.power, tempNode.coeff, false, newNode);
                tempNode := tempNode.next;
            end loop;

            while tempNode2 /= null loop
                addPolyNode (tempNode2.power, tempNode2.coeff, false, newNode);
                tempNode2 := tempNode2.next;
            end loop;

            -- sort and print to screen
            sortPOLY (newNode);
            writePOLY (newNode);
        end if;
    end addpoly;

    procedure subpoly
       (headNode : in out polyNodePtr; headNode2 : in out polyNodePtr;
        index    : in     Integer)
    is
        tempNode       : polyNodePtr;
        tempNode2      : polyNodePtr;
        finalTempNode  : polyNodePtr := headNode;
        finalTempNode2 : polyNodePtr := headNode2;
    begin
        if headNode = null or headNode2 = null then
            Put ("ERROR: head node is null, cannot subtract, if you would like to subtract the same polynomial, please input it");
            New_Line;
            New_Line;
        else
            -- if two polys are equal, result is always 0
            if isSame (headNode, headNode2) = True then
                Put ("0");
                New_Line;
            else

                tempNode  := headNode;
                tempNode2 := headNode2;

                -- use index to determine which polynomial we are subtracting from
                if index = 1 then
                    -- first we will convert all terms to negative values
                    while tempNode2 /= null loop
                        tempNode2.coeff := tempNode2.coeff * (-1);
                        tempNode2       := tempNode2.next;
                    end loop;

                    -- then we can use our add procedure to simply add them all up
                    addpoly (headNode, headNode2);
                    headNode2 := finalTempNode2;

                    -- revert back to keep original polynomial
                    while finalTempNode2 /= null loop
                        finalTempNode2.coeff := finalTempNode2.coeff * (-1);
                        finalTempNode2       := finalTempNode2.next;
                    end loop;
                elsif index = 2 then
                    -- do the same thing but with headNode2
                    while tempNode /= null loop
                        tempNode.coeff := tempNode.coeff * (-1);
                        tempNode       := tempNode.next;
                    end loop;

                    addpoly (headNode, headNode2);
                    headNode := finalTempNode;

                    -- revert back to keep original polynomial
                    while finalTempNode /= null loop
                        finalTempNode.coeff := finalTempNode.coeff * (-1);
                        finalTempNode       := finalTempNode.next;
                    end loop;
                else
                    Put ("ERROR: Invalid index, please enter 1 or 2");
                    New_Line;
                    New_Line;
                end if;
            end if;
        end if;
    end subpoly;

    procedure multpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr)
    is
        tempNode  : polyNodePtr;
        tempNode2 : polyNodePtr;
        newNode   : polyNodePtr;
    begin

        if headNode = null or headNode2 = null then
            Put ("ERROR: head node is null, cannot multiply, if you would like to multiply the same polynomial, please input it");
            New_Line;
            New_Line;
        else

            tempNode := headNode;
            newNode  := null;

            -- we will loop through the first list and at each node, multiply the coeff by all the coeff in the second list and adding the powers accordingly
            -- addPolyNode will take care of adding up like terms since we gave it the True flag
            while tempNode /= null loop
                tempNode2 := headNode2;
                while tempNode2 /= null loop
                    addPolyNode
                       (tempNode.power + tempNode2.power,
                        tempNode.coeff * tempNode2.coeff, true, newNode);
                    tempNode2 := tempNode2.next;
                end loop;
                tempNode := tempNode.next;
            end loop;

            -- sort and print the list
            sortPOLY (newNode);
            writePOLY (newNode);
        end if;
    end multpoly;

    procedure evalpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr)
    is
        choice   : Integer;
        tempNode : polyNodePtr;
        xVal     : Integer;
        res      : Integer;
    begin
        if headNode = null and headNode2 = null then
            Put ("ERROR: You have no polynomials to evaluate for");
            New_Line;
            New_Line;
        else
            -- give user choice for which of the two polynomials to solve for
            Put ("Which polynomial would you like to solve? Enter 1 or 2: ");
            Get (choice);

            if choice = 1 then
                if headNode = null then
                    Put ("ERROR: head node is null, cannot evaluate for a non-existing polynomial");
                    New_Line;
                    New_Line;
                else

                    tempNode := headNode;
                    res      := 0;

                    Put ("Enter x value: ");
                    Get (xVal);

                    -- loop through list and sum res each time to coeff * xVal^power
                    while tempNode /= null loop
                        res := res + ((xVal**tempNode.power) * tempNode.coeff);
                        tempNode := tempNode.next;
                    end loop;

                    Put ("Result:" & Integer'Image (res));
                    New_Line;
                    New_Line;
                end if;
            -- do the same thing if the user chooses the second polynomial to solve for
            elsif choice = 2 then
                if headNode2 = null then
                    Put ("ERROR: head node is null, cannot evaluate for a non-existing polynomial");
                    New_Line;
                    New_Line;
                else

                    tempNode := headNode2;
                    res      := 0;

                    Put ("Enter x value: ");
                    Get (xVal);

                    -- loop through list and sum res each time to coeff * xVal^power
                    while tempNode /= null loop
                        res := res + ((xVal**tempNode.power) * tempNode.coeff);
                        tempNode := tempNode.next;
                    end loop;

                    Put ("Result:" & Integer'Image (res));
                    New_Line;
                    New_Line;
                end if;
            else
                Put ("ERROR: Invalid option, please select 1 or 2");
                New_Line;
                New_Line;
            end if;
        end if;
    end evalpoly;

    -- this function simply checks if two linked lists are equal and returns true or false
    function isSame
       (headNode : polyNodePtr; headNode2 : polyNodePtr) return Boolean
    is
        tempNode  : polyNodePtr;
        tempNode2 : polyNodePtr;
    begin

        tempNode  := headNode;
        tempNode2 := headNode2;

        -- iterate through both lists and check if powers and coeff are not equal at any point
        while tempNode /= null and tempNode2 /= null loop
            if tempNode.power /= tempNode2.power or
               tempNode.coeff /= tempNode2.coeff
            then
                return False;
            end if;
            tempNode  := tempNode.next;
            tempNode2 := tempNode2.next;
        end loop;

        -- check if both lists ended at the same time
        if (tempNode = null and tempNode2 /= null) or
           (tempNode /= null and tempNode2 = null)
        then
            return False;
        end if;

        -- if no differences then they are equal
        return True;
    end isSame;
end Polymath;
