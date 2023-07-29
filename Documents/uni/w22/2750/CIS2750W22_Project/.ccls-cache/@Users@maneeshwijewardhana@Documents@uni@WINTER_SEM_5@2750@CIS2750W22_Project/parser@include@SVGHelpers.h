/*
NAME: Maneesh Wijewardhana
ID: 1125828
COURSE: CIS*2750 (module 1, 2 from A1, module 1, 2, 3, 3 bonus, from A2)
DUE DATE: MARCH 2, 2022

This file contains functions that were created myself to aid in parsing an SVG
Now updated for A2 functionality
*/

#include "SVGParser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
this function takes in an attribute and attempts to return an attribute that is filled with content
*/
Attribute* createAttribute(xmlAttr* attr);

/*
this function creates a rectangle and inits its other attributes
then it loops through its node properties to find each prop like x, y, etc
we use strtok to parse the end of each to find units but we assume if its there for the first, its there for all
*/
void createAndAddRectangle(xmlNode* node, List* list);

/*
same idea as createAndAddRectangle just with different properties to check for
*/
void createAndAddCircle(xmlNode* node, List* list);

/*
for this, we malloc more space for the path 
now we dont need to check for units so we just strcpy
*/
void createAndAddPath(xmlNode* node, List* list);

/*
creates group and traverses through each child node for shapes/attributes
then it calls on each helper function as well as itself if nested groups
similar to createsvg
*/
void createAndAddGroup(xmlNode* node, List* list);

/*
this function acts as a helper function for getGroups. 
Without recursion, getGroups will only get the first hierarchy of groups but 
if there were nested groups, it wouldn't catch those.
This function goes through the root group and keeps calling itself and adds them to the group list everytime.
In getGroups, we call this when iterating to get all nested groups
*/
void recurseGroups(List *list, Group *root);

/*
This function checks to see if a given xml is valid based on a schema file
With this, we can use it when creating a valid svg file
The return value will be used for creating a valid svg
*/
int isValidXml(xmlDoc *xml, const char *xsdFile);

/*
This functions helps to convert an svg to xmlDoc struct
With this, we can validate an a SVG image
*/
xmlDoc *svgToXmlDoc(const SVG *img);

/*
This function adds all rectangles in rectangles list into xml node
*/
void addRectsXML(List *list, xmlNode *node);

/*
This function adds all attributes in attributes list into xml node
*/
void addAttributesXML(List *list, xmlNode *node);

/*
This function adds all circles in circles list into xml node
*/
void addCirclesXML(List *list, xmlNode *node);

/*
This function adds all paths in paths list into xml node
*/
void addPathsXML(List *list, xmlNode *node);

/*
This function adds all groups in groups list into xml node
*/
void addGroupsXML(List *list, xmlNode *node);

/* 
This function validates rect list with the given header constraints 
*/
bool isValidRect(List *list);

/* 
This function validates attribute list with the given header constraints 
*/
bool isValidAttr(List *list);

/* 
This function validates circles list with the given header constraints 
*/
bool isValidCircle(List *list);

/* 
This function validates paths list with the given header constraints 
*/
bool isValidPath(List *list);

/* 
This function validates groups list with the given header constraints 
*/
bool isValidGroup(List *list);

// simple function that gets the summaries of a file and outputs json
char *fileToJSON(char *filename, char *schema);

// validates the created svg from createvalidsvg 
bool validateFile(char *filename, char *schema);

// allows me to get all info needed in json for displaying details of an svg image
char *imageToJSON(char *filename, char *schema);

// need get tile and get desc funcs because json.parse messes up with quotes in these fields so i need to send them seperatly
char *getTitle(char *filename, char *schema);
char *getDesc(char *filename, char *schema);

// function to send over attributes
char *getAttributes(char *filename, char *schema);

// function to save title
bool writeTitle(char *filename, char *schema, char *title);

// function to save description (same as title)
bool writeDesc(char *filename, char *schema, char *title);

// function to create an empty svg with no visible contents
bool createEmptySVG(char *filename, char *svgString);

// function to scale shape based on a factor
bool scaleShapes(char *filename, char *component, float factor);

// wrapper function to add a shape
bool addShape(char *filename, char *shape, char *svgString);

// wrapper function for setting an attribute
bool setAttributeWrapper(char *filename, char *elemType, int elementIndex, char *newOtherAttr, char *newOtherAttrVal);
