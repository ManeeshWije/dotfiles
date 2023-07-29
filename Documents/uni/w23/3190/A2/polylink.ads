-- NAME: MANEESH WIJEWARDHANA
-- ID: 1125828
-- COURSE: CIS*3190
-- DUE DATE: MARCH 6
-- This file contains the signatures for the main subroutines that read and write user input as well as some helper subroutines
with Polylinkedlist; use Polylinkedlist;

package Polylink is
    procedure readPOLY
       (headNode : in out polyNodePtr; headNode2 : in out polyNodePtr);

    procedure writePOLY (headNode : in polyNodePtr);

    procedure writePOLYmain
       (headNode : in polyNodePtr; headNode2 : in polyNodePtr;
        index    : in Integer);

    procedure sortPOLY (headNode : in polyNodePtr);
end Polylink;
