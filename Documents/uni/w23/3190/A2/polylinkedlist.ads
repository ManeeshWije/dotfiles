-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the signatures and structures for the main subroutines to add and delete nodes in a linkedlist
package Polylinkedlist is

    type polyNode;
    type polyNodePtr is access polyNode;

    type polyNode is record
        power : Integer;
        coeff : Integer;
        next  : polyNodePtr;
    end record;

    procedure addPolyNode
       (power       :        Integer; coeff : Integer; update : in Boolean;
        newPolyNode : in out polyNodePtr);

    procedure deletePolyNode (headNode : in out polyNodePtr);

end Polylinkedlist;
