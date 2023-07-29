-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the signatures for the main subroutines to perform polynomial math as well as extra helper subroutines
with Polylinkedlist; use Polylinkedlist;

package Polymath is
    procedure addpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr);

    procedure subpoly
       (headNode : in out polyNodePtr; headNode2 : in out polyNodePtr;
        index    : in     Integer);

    procedure multpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr);

    procedure evalpoly (headNode : in polyNodePtr; headNode2 : in polyNodePtr);

    function isSame
       (headNode : polyNodePtr; headNode2 : polyNodePtr) return Boolean;
end Polymath;
