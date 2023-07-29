-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the implementation for the main subroutines to add and delete nodes in a linkedlist
with Ada.Text_IO; use Ada.Text_IO;

package body Polylinkedlist is
    -- this procedure will add a node to a linkedlist that contains an exponent value, coeffecient, and pointer to the next node
    procedure addPolyNode
       (power       : in     Integer; coeff : in Integer; update : in Boolean;
        newPolyNode : in out polyNodePtr)
    is
        currNode : polyNodePtr;
        prevNode : polyNodePtr;
        found    : Boolean := False;
    begin
        currNode := newPolyNode;
        prevNode := null;

        -- check if the power already exists
        while currNode /= null loop
            if currNode.power = power then
                found := True;
                if update then
                    -- update the coefficient of the existing term
                    currNode.coeff := currNode.coeff + coeff;
                else
                    if coeff = 0 then
                        Put ("Skipping 0 element");
                        New_Line;
                        New_Line;
                    end if;
                    -- add a new term to the list
                    addPolyNode (power, coeff, False, currNode.next);
                end if;
                exit;
            end if;

            prevNode := currNode;
            currNode := currNode.next;
        end loop;

        if not found then
            -- add a new term to the list
            currNode := new polyNode'(power, coeff, null);
            if coeff = 0 then
                Put ("Skipping 0 element");
                New_Line;
                New_Line;
            elsif prevNode = null then
                newPolyNode := currNode;
            else
                prevNode.next := currNode;
            end if;
        end if;
    end addPolyNode;

    -- This procedure will delete a node as well as the list itself
    procedure deletePolyNode (headNode : in out polyNodePtr) is
        currNode : polyNodePtr := headNode;
        nextNode : polyNodePtr;
    begin
        while currNode /= null loop
            nextNode := currNode.next;
            currNode := nextNode;
        end loop;
        headNode := null;
    end deletePolyNode;
end Polylinkedlist;
