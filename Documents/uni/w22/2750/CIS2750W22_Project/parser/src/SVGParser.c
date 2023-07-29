/*
NAME: Maneesh Wijewardhana
ID: 1125828
COURSE: CIS*2750 (module 1 and 2 from A1) (module 1,2,3, 3 bonus, from A2)
DUE DATE: MARCH 2, 2022
Some code snippets are from libXmlExample.c which I have commented on and cited
Using functions from LinkedListAPI.c to traverse some lists, insert elements, and toString
All of which have been cited when used

Thanks Denis!
*/

#include "SVGHelpers.h"
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define PI 3.14159265358979323846

/*
START MAIN FUNCTIONS (MODULE 1)
*/
SVG *createSVG(const char *filename) {
  // from libXmlExample.c
  xmlDoc *doc = xmlReadFile(filename, NULL, 0);

  // error checking and freeing memory if error
  if (doc == NULL) {
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return NULL;
  }
  // from libXmlExample.c
  xmlNode *root_element = xmlDocGetRootElement(doc);
  // allocating space for svg image
  SVG *img = (SVG *)malloc(sizeof(SVG));

  // init these to empty as without it, valgrind complains since we try to get strlen of them in svgtostring when uninitialized
  strcpy(img->title, "");
  strcpy(img->description, "");
  strcpy(img->namespace, "");

  // since doc is not null we know its valid svg and can grab the namespace out of it
  // remember truncate if more than 255
  strncpy(img->namespace, (char *)root_element->ns->href, 255);
  img->namespace[255] = '\0';

  // allocate lists on stack and returns the list struct for each
  // from LinkedListAPI.c
  img->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
  img->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
  img->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
  img->paths = initializeList(&pathToString, &deletePath, &comparePaths);
  img->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
  // looping through each child node until null
  // loop structure is from libxmlexample.c
  for (xmlNode *curr = root_element->children; curr != NULL; curr = curr->next) {
    if (curr->type == XML_ELEMENT_NODE) { // make sure valid node
      if (strcmp((char *)curr->name, "title") == 0) { // find title tag
        if (curr->children != NULL) { // make sure its not null
          //remember to truncate like namespace
          strncpy(img->title, (char *)curr->children->content, 255); // set svg image title to the content of this node
          img->title[255] = '\0';
        }
      }
      if (strcmp((char *)curr->name, "desc") == 0) { // find description tag
        if (curr->children != NULL) { // make sure its not null
          strncpy(img->description, (char *)curr->children->content, 255); // set svg desc to the content of node
          img->description[255] = '\0';
        }
      }
      if (strcmp((char *)curr->name, "rect") == 0) { // find rectangle tag
        // call function that goes thru each node attribute and sets the values
        // accordingly then adds to list takes in current node and then the list
        // for rectangles
        createAndAddRectangle(curr, img->rectangles);
      }
      if (strcmp((char *)curr->name, "circle") == 0) {
        createAndAddCircle(curr, img->circles);
      }
      if (strcmp((char *)curr->name, "path") == 0) {
        createAndAddPath(curr, img->paths);
      }
      if (strcmp((char *)curr->name, "g") == 0) {
        createAndAddGroup(curr, img->groups);
      }
    }
  }
  // finally, we can go through each attribute and add the properties of
  // otherattributes to its otherattributes
  // from libxmlexample.c 
  for (xmlAttr *attr = root_element->properties; attr != NULL; attr = attr->next) {
    // from LinkedListAPI.c
    insertBack(img->otherAttributes, createAttribute(attr));
  }
  // cleaning up memory (from libXmlExample.c)
  xmlCleanupParser();
  xmlFreeDoc(doc);
  return img;
}

char *SVGToString(const SVG *img) {
  // making sure img passed in is not NULL
  if (img == NULL) {
    return NULL;
  }
  // typecast temp variable
  SVG *temp = (SVG *)img;

  // calculating length of the default attributes so we can malloc the right size
  // int len = strlen(temp->namespace) + strlen(temp->title) + strlen(temp->description) + 1024;
  // nice
  char *str = (char *)malloc(strlen(temp->namespace) + strlen(temp->title) + strlen(temp->description) + 512 * sizeof(char));
  // printing the shit
  sprintf(str, "NAMESPACE: %s\n TITLE: %s\n DESCRIPTION: %s \n", temp->namespace, temp->title, temp->description);

  // this var is so we can dynamically allocate space for the rest of the shapes and attributes
  char *tempList = NULL;

  // get otherattributes stuff and dynamically allocate space
  // only do this if it actually exists
  if (img->otherAttributes->length > 0) {
    // appending otherattributes to the templist
    // using toString from LinkedListAPI.c
    tempList = toString(img->otherAttributes);
    // resizing original string with defaults to account for this templist
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    // concatenating it
    strcat(str, tempList);
    // freeing it here so we can use it again for the other shapes
    free(tempList);
  }

  // get rectangles and dynamically allocate space
  if (img->rectangles->length > 0) {
    // same shit
    // using toString from LinkedListAPI.c
    tempList = toString(img->rectangles);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (img->circles->length > 0) {
    // using toString from LinkedListAPI.c
    tempList = toString(img->circles);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (img->paths->length > 0) {
    // using toString from LinkedListAPI.c
    tempList = toString(img->paths);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (img->groups->length > 0) {
    // using toString from LinkedListAPI.c
    tempList = toString(img->groups);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  return str;
}

void deleteSVG(SVG *img) {
  // check for null
  if (img == NULL) {
    return;
  }
  // typecasting and then freeing each List from svg before freeing svg itself
  SVG *temp = (SVG *)img;
  // using freeList from LinkedListAPI.c to free entire list
  freeList(temp->otherAttributes);
  freeList(temp->rectangles);
  freeList(temp->circles);
  freeList(temp->paths);
  freeList(temp->groups);
  free(temp);
}
/*
END MAIN FUNCTIONS (MODULE 1)
*/

/*
START PROFS HELPER FUNCTIONS (MODULE 1)
*/
void deleteAttribute(void *data) {
  // check for null
  if (data == NULL) {
    return;
  }
  // typecast and free name part and free attr frees the value as well because flex array member
  Attribute *attr = (Attribute *)data;
  free(attr->name);
  free(attr);
}

char *attributeToString(void *data) {
  // check for null
  if (data == NULL) {
    return NULL;
  }
  // typecast temp
  Attribute *temp = (Attribute *)data;
  // calculating length of attributes so we can malloc our temp string
  // malloc it now
  char *tempStr = (char *)malloc(strlen(temp->name) + strlen(temp->value) + 1024 * sizeof(char));

  sprintf(tempStr, "attr-name: %s\nvalue: %s\n", temp->name, temp->value);

  return tempStr;
}

// just return 0
int compareAttributes(const void *first, const void *second) { 
  return 0; 
}

void deleteRectangle(void *data) {
  // check for null
  if (data == NULL) {
    return;
  }
  // typecast
  Rectangle *r = (Rectangle *)data;
  // since rec has otherattributes list, free that and then free rectangle itself
  // using freeList from LinkedListAPI.c to free otherattr list from recs
  freeList(r->otherAttributes);
  free(r);
}

char *rectangleToString(void *data) {
  // check for null
  if (data == NULL) {
    return NULL;
  }
  // malloc enough space for str
  // will also use this to dynamically allocate rectangle attributes
  char *str = (char *)malloc(sizeof(char) + 1024);
  Rectangle *r = (Rectangle *)data;
  sprintf(str, "RECTANGLE\nx: %.2f\ny: %.2f\nwidth: %.2f\nheight: %.2f\nunits: %s\n", r->x, r->y, r->width, r->height, r->units);

  // Get string descriptions for other attributes, dynamic sizing
  if (r->otherAttributes->length > 0) {
    // similar way of dynamically allocating like in svgtostring
    // using toString from LinkedListAPI.c to get otherattr from recs
    char *tempList = NULL;
    tempList = toString(r->otherAttributes);
    str = realloc(str, sizeof(char) * (strlen(str) + strlen(tempList) + 32));
    strcat(str, tempList);
    free(tempList);
  }
  return str;
}

// return 0 for this
int compareRectangles(const void *first, const void *second) { 
  return 0; 
}

void deleteCircle(void *data) {
  // check for null
  if (data == NULL) {
    return;
  }
  // same method as rectangles
  Circle *c = (Circle *)data;
  // using freeList from LinkedListAPI.c to free otherattr list from circs
  freeList(c->otherAttributes);
  free(c);
}

char *circleToString(void *data) {
  // check for null
  if (data == NULL) {
    return NULL;
  }
  // same way as rectangle but different values
  char *str = (char *)malloc(sizeof(char) + 256);
  Circle *c = (Circle *)data;
  sprintf(str, "CIRCLE\ncx: %.2f\ncy: %.2f\nr: %.2f\nunits: %s\n", c->cx, c->cy, c->r, c->units);

  if (c->otherAttributes->length > 0) {
    // using toString from LinkedListAPI.c to get otherattr from circles
    char *tempList = NULL;
    tempList = toString(c->otherAttributes);
    str = realloc(str, sizeof(char) * (strlen(str) + strlen(tempList) + 32));
    strcat(str, tempList);
    free(tempList);
  }
  return str;
}

// return 0 for this
int compareCircles(const void *first, const void *second) { 
  return 0; 
}

void deletePath(void *data) {
  // check for null
  if (data == NULL) {
    return;
  }
  // same as recs and circs
  Path *p = (Path *)data;
  // using freeList from LinkedListAPI.c to free otherattr from paths
  freeList(p->otherAttributes);
  free(p);
}

char *pathToString(void *data) {
  // check for null
  if (data == NULL) {
    return NULL;
  }
  // when mallocing, had to use more space than recs and circs
  Path *p = (Path *)data;
  char *str = (char *)malloc(strlen(p->data) * sizeof(char) + 1000000);
  // char *str = (char *)malloc(sizeof(char) + 200);

  sprintf(str, "PATH\n d: %s\n", p->data);

  // same as recs and circs
  if (p->otherAttributes->length > 0) {
    // using toString from LinkedListAPI.c to get otherattr from paths
    char *tempList = NULL;
    tempList = toString(p->otherAttributes);
    str = realloc(str, sizeof(char) * (strlen(str) + strlen(tempList) + 32));
    strcat(str, tempList);
    free(tempList);
  }
  return str;
}

// return 0 for this
int comparePaths(const void *first, const void *second) { 
  return 0; 
}

void deleteGroup(void *data) {
  // check for null
  if (data == NULL) {
    return;
  }
  // typecast and free all lists and data itself
  // using freeList from LinkedListAPI.c to free all shapes/attr from groups
  Group *g = (Group *)data;
  freeList(g->rectangles);
  freeList(g->circles);
  freeList(g->paths);
  freeList(g->otherAttributes);
  freeList(g->groups);
  free(g);
}

char *groupToString(void *data) {
  // need to check if group contains each attribute and then dynamically
  // allocate space for string similar to svgtostring where we call toString
  if (data == NULL) {
    return NULL;
  }
  Group *g = (Group *)data;
  char *tempList = NULL;
  char *str = (char *)malloc(sizeof(char) * 64);
  sprintf(str, "GROUP");

  if (g->otherAttributes->length > 0) {
    // using toString from LinkedListAPI.c to get otherattr from groups
    tempList = toString(g->otherAttributes);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (g->rectangles->length > 0) {
     // using toString from LinkedListAPI.c to get recs from groups
    tempList = toString(g->rectangles);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (g->circles->length > 0) {
    // using toString from LinkedListAPI.c to get circs from groups
    tempList = toString(g->circles);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (g->paths->length > 0) {
    // using toString from LinkedListAPI.c to get paths from groups
    tempList = toString(g->paths);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }

  if (g->groups->length > 0) {
    // using toString from LinkedListAPI.c to get groups from groups
    tempList = toString(g->groups);
    str = realloc(str, strlen(str) + strlen(tempList) + 8);
    strcat(str, tempList);
    free(tempList);
  }
  return str;
}

// return 0 for this
int compareGroups(const void *first, const void *second) { 
  return 0; 
}
/*
END PROFS HELPER FUNCTIONS (MODULE 1)
*/

/*
START ACCESSOR AND SEARCH FUNCTIONS (MODULE 2)
*/

// this is for delete functions to avoid double frees when running getters
void dummyDelete() {}

List *getRects(const SVG *img) {
  // check for null first
  if (img == NULL) {
    return NULL;
  }
  // init total rect list to get added into
  List *totalRect = initializeList(&rectangleToString, &dummyDelete, &compareRectangles);
  // get all rectangles in image
  for (Node *node = img->rectangles->head; node != NULL; node = node->next) {
    // using insertBack from LinkedListAPI.c to insert data into front of rect list
    insertBack(totalRect, node->data);
  }
  //get groups and check for rectangles in them
  List *groups = getGroups(img);
  //loop through groups and if rectangles exists, add them to total list
  for (Node *node = groups->head; node != NULL; node = node->next) {
    Group *g = node->data;
    if (g->rectangles != NULL) {
      for (Node *r = g->rectangles->head; r != NULL; r = r->next) {
        // using insertBack from LinkedListAPI.c to insert rect data from groups into front of rect list
        insertBack(totalRect, r->data);
      }
    }
  }
  // free groups list and return the total rectangles
  // using freeList from LinkedListAPI.c to free temp group list
  freeList(groups);
  return totalRect;
}

List *getCircles(const SVG *img) {
  // check for null first
  if (img == NULL) {
    return NULL;
  }
  // init total rect list to get added into
  List *totalCirc = initializeList(&circleToString, &dummyDelete, &compareCircles);
  // get all rectangles in image
  for (Node *node = img->circles->head; node != NULL; node = node->next) {
    // using insertBack from LinkedListAPI.c to insert circ data into front of circ list
    insertBack(totalCirc, node->data);
  }
  // get circles that are in a group element 
  //loop through them and if they exists, add to list
  List *groups = getGroups(img);
  for (Node *node = groups->head; node != NULL; node = node->next) {
    Group *g = node->data;
    if (g->circles != NULL) {
      for (Node *c = g->circles->head; c != NULL; c = c->next) {
        // using insertBack from LinkedListAPI.c to insert circ data from groups into front of circ list
        insertBack(totalCirc, c->data);
      }
    }
  }
  // free memory from groups and return filled list
  // using freeList from LinkedListAPI.c to free temp group list
  freeList(groups);
  return totalCirc;
}

List *getGroups(const SVG *img) {
  //check for null first
  if (img == NULL) {
    return NULL;
  }
  //init group list
  List *totalGroups = initializeList(&groupToString, &dummyDelete, &compareGroups);
  //use ListIterator from api to iterate through groups and get the next element
  ListIterator iter = createIterator(img->groups);
  // from LinkedListAPI.c
  Group *g = nextElement(&iter);
  while (g != NULL) {
    //get groups within groups
    recurseGroups(totalGroups, g);
    //add to list until theres no more to add
    // from LinkedListAPI.c
    insertBack(totalGroups, g);
    g = nextElement(&iter);
  }
  //return groups list
  return totalGroups;
}

List *getPaths(const SVG *img) {
  // check for null first
  if (img == NULL) {
    return NULL;
  }
  // init total paths list to get added into
  List *totalPaths = initializeList(&pathToString, &dummyDelete, &comparePaths);
  // get all paths in image
  for (Node *node = img->paths->head; node != NULL; node = node->next) {
    // from LinkedListAPI.c
    insertBack(totalPaths, node->data);
  }
  // get paths that are inside a group
  // traverse through and if not null, add those paths to original list
  List *groups = getGroups(img);
  for (Node *node = groups->head; node != NULL; node = node->next) {
    Group *g = node->data; 
    if (g->paths != NULL) {
      for (Node *p = g->paths->head; p != NULL; p = p->next) {
        // from LinkedListAPI.c
        insertBack(totalPaths, p->data);
      }
    }
  }
  //free groups and return total list
  // from LinkedListAPI.c
  freeList(groups);
  return totalPaths;
}

int numRectsWithArea(const SVG* img, float area) {
  //check for null image or negative area
  if (img == NULL || area < 0) {
    return 0;
  }
  //get total rectangles in image
  List *totalRecs = getRects(img);
  //use this to keep track of total rectangles that have area
  int counter = 0;
  //traverse through list and if width*height = area, increment counter
  //using ceiling function to simplify the float for continuity
  for (Node *r = totalRecs->head; r != NULL; r = r->next) {
    Rectangle *rect = r->data;
    float totalArea = rect->width * rect->height;
    if (ceilf(totalArea) == ceilf(area)) {
      counter++;
    }
  }
  //free totalrec list and return total counter
  // from LinkedListAPI.c
  freeList(totalRecs);
  return counter;
}

int numCirclesWithArea(const SVG* img, float area) {
  //check if image is null or area is negative
  if (img == NULL || area < 0) {
    return 0;
  }
  //get circles in image
  List *totalCirc = getCircles(img);
  //counter to keep track of which circles have same area
  int counter = 0; 
  //loop through list and if pi * r * r = given area, increment list
  //using ceiling function again to simplify float values
  for (Node *c = totalCirc->head; c != NULL; c = c->next) {
    Circle *circ = c->data;
    float totalArea = circ->r * circ->r * PI;
    if (ceilf(totalArea) == ceilf(area)) {
      counter++;
    }
  }
  //free total circle list and return total counter
  // from LinkedListAPI.c
  freeList(totalCirc);
  return counter;
}

int numPathsWithdata(const SVG* img, const char* data) {
  //check for null image or null data as well as empty string
  if (img == NULL || data == NULL || strcmp(data, "") == 0) {
    return 0;
  }
  //get total paths in image
  List *totalPaths = getPaths(img);
  //counter to keep track of which data matches given data
  int counter = 0;
  //loop through paths and if data = to given data, incremenet counter
  for (Node *p = totalPaths->head; p != NULL; p = p->next) {
    Path *path = p->data;
    if (strcmp(path->data, data) == 0) {
      counter++;
    }
  }
  //free total path list and return total counter
  // from LinkedListAPI.c
  freeList(totalPaths);
  return counter;
}

int numGroupsWithLen(const SVG* img, int len) {
  //check for null image or length that is negative
  if (img == NULL || len < 0) {
    return 0;
  }
  //get total groups in image
  List *totalGroups = getGroups(img);
  //counter to keep track of group lengths matching given length
  int counter = 0;
  //loop through total groups
  for (Node *g = totalGroups->head; g != NULL; g = g->next) {
    //get length of each shape
    int recLen = ((Group*)g->data)->rectangles->length;
    int circLen = ((Group*)g->data)->circles->length;
    int pathLen = ((Group*)g->data)->paths->length;
    int groupLen = ((Group*)g->data)->groups->length;
    //add them all together to get total length
    int totalLen = recLen + circLen + pathLen + groupLen;
    //increment if total length matches given length
    if (totalLen == len) {
      counter++;
    }
  }
  //free total groups list and return total counter
  // from LinkedListAPI.c
  freeList(totalGroups);
  return counter;
}

int numAttr(const SVG* img) {
  //check for null image
  if (img == NULL) {
    return 0;
  }
  //get base count of the length of other attributes in an image
  int totalCount = img->otherAttributes->length;
  //get total rectangles in image and add to total list
  List *totalLists = getRects(img);
  //go through rectangles and add the length of its other attributes to totalcount
  for (Node *node = totalLists->head; node != NULL; node = node->next) {
    totalCount += ((Rectangle*)(node->data))->otherAttributes->length;
  }
  //free this list as we need to use it for other shapes now
  // from LinkedListAPI.c
  freeList(totalLists);

  //moving onto circles in image
  totalLists = getCircles(img);
  //go through circles and keep adding other attributes length to totalcounter variable which holds recs now too
  for (Node *node = totalLists->head; node != NULL; node = node->next) {
    totalCount += ((Circle*)(node->data))->otherAttributes->length;
  }
  //free so we can use it for paths
  freeList(totalLists);

  //get paths in image
  totalLists = getPaths(img);
  //same idea
  for (Node *node = totalLists->head; node != NULL; node = node->next) {
    totalCount += ((Path*)(node->data))->otherAttributes->length;
  }
  //free to use it for groups
  freeList(totalLists);

  //same stuff
  totalLists = getGroups(img);
  //yep
  for (Node *node = totalLists->head; node != NULL; node = node->next) {
    totalCount += ((Group*)(node->data))->otherAttributes->length;
  }
  //last free
  freeList(totalLists);

  //return the total count we've been keeping track of
  return totalCount;
}
/*
END ACCESSOR FUNCTIONS MODULE 2 A1
*/

/*
START MODULE 1 A2
*/
SVG *createValidSVG(const char *fileName, const char *schemaFile) {
  // do basic checks first for file extensions and null files etc etc
  FILE *fp = fopen(fileName, "r");
  FILE *fp2 = fopen(schemaFile, "r");
  if (fileName == NULL || schemaFile == NULL || fp == NULL || fp2 == NULL || strcmp(".xsd", schemaFile + strlen(schemaFile) - 4) != 0 || strcmp(".svg", fileName + strlen(fileName) - 4) != 0) {
    return NULL;
  }
  SVG *img = NULL;
  xmlDocPtr doc = xmlReadFile(fileName, NULL, 0);
  if (doc == NULL) {
    xmlFreeDoc(doc);
    xmlCleanupParser();
  }
  int ret = isValidXml(doc, schemaFile);
  // svg is valid
  if (ret == 0) {
    img = createSVG(fileName);
  }
  xmlFreeDoc(doc);
  xmlCleanupParser();
  fclose(fp);
  fclose(fp2);
  return img;
}

bool writeSVG(const SVG *img, const char *fileName) {
  // check for file extension and null first
  if (img == NULL || fileName == NULL || strcmp(".svg", fileName + strlen(fileName) - 4) != 0) {
    return false;
  }
  // not sure if we have to check for shapes but it wont hurt to
  if (!isValidAttr(img->otherAttributes) || !isValidRect(img->rectangles) || !isValidCircle(img->circles) || !isValidPath(img->paths) || !isValidGroup(img->groups)) {
    return false;
  }
  // now convert
  xmlDoc *imgXML = svgToXmlDoc(img);
  // now write
  if (imgXML == NULL) {
    return false;
  } 
  int ret = xmlSaveFormatFileEnc(fileName, imgXML, "UTF-8", 1);
  xmlFreeDoc(imgXML);
  xmlCleanupParser();
  xmlMemoryDump();
  if (ret == -1) {
    return false;
  } else {
    return true;
  }
}

bool validateSVG(const SVG *img, const char *schemaFile) {
  // check for null image and schema first
  if (img == NULL || schemaFile == NULL) {
    return false;
  }
  // header constraints check using validate helper functions
  if (!isValidAttr(img->otherAttributes) || !isValidRect(img->rectangles) || !isValidCircle(img->circles) || !isValidPath(img->paths) || !isValidGroup(img->groups)) {
    return false;
  }
  // now check xsd
  xmlDoc *doc = svgToXmlDoc(img);
  int ret = isValidXml(doc, schemaFile);
  xmlFreeDoc(doc);
  if (ret == 0) {
    return true;
  } else {
    return false;
  }
}
/*
END MODULE 1 A2
*/

/*
START MODULE 2 A2
*/
bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
  // check for null args first
  if (img == NULL || newAttribute == NULL || newAttribute->name == NULL) {
    return false;
  }
  // make sure its a valid elemType
  if (elemType != SVG_IMG && elemType != RECT && elemType != CIRC && elemType != PATH && elemType != GROUP) {
    return false;
  }
  // check validity of shapes/attr
  if (!(isValidAttr(img->otherAttributes) && isValidRect(img->rectangles) && isValidCircle(img->circles) && isValidPath(img->paths) && isValidGroup(img->groups))) {
    return false;
  }

  // now do each elemtype
  if (elemType == SVG_IMG) {
    Attribute *attr = NULL;
    bool found = false;
    // iterate thru otherattr
    // from LinkedListAPI.c
    ListIterator iter = createIterator(img->otherAttributes);
    while ((attr = nextElement(&iter)) != NULL) {
      // if it exists already, copy it
    	if (strcmp(attr->name, newAttribute->name) == 0) {
        strcpy(attr->value, newAttribute->value);
        deleteAttribute(newAttribute);
        found = true;
        return true;
      }
    }
    // if not found
    if (found == false) {
      insertBack(img->otherAttributes, newAttribute);
      return true;
    }
  }

  // check for rect
  if (elemType == RECT) {
    // quick valid check
    if (elemIndex > img->rectangles->length - 1 || elemIndex < 0) {
      return false;
    }
    int index = 0;
    bool found = false;
    Rectangle *r = NULL;
    // iterate thru rectangles
    // from LinkedListAPI.c
    ListIterator iter = createIterator(img->rectangles);
    while ((r = nextElement(&iter)) != NULL) {
      // find index of rectangle
      if (index == elemIndex) {
        // now check if we need to update any of the rectangle attributes
        if (strcmp(newAttribute->name, "x") == 0) {
          r->x = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } else if (strcmp(newAttribute->name, "y") == 0) {
          r->y = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } else if (strcmp(newAttribute->name, "width") == 0) {
          r->width = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } else if (strcmp(newAttribute->name, "height") == 0) {
          r->height = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } 
        if (getLength(r->otherAttributes) != 0) { // we know its otherattrbutes
          Attribute *attr = NULL;
          // from LinkedListAPI.c
          ListIterator iter2 = createIterator(r->otherAttributes);
          while ((attr = nextElement(&iter2)) != NULL) {
            // check if that attribute exists
            if (strcmp(newAttribute->name, attr->name) == 0) {
              strcpy(attr->value, newAttribute->value);
              deleteAttribute(newAttribute);
              found = true;
              return true;
            } 
          }
          // if not found
          if (found == false) {
            insertBack(r->otherAttributes, newAttribute);
            return true;
          }
        } else {
          insertBack(r->otherAttributes, newAttribute);
          return true;
        }
      }
      index++;
    }
  }

  // check for circle
  if (elemType == CIRC) {
    // quick valid check
    if (elemIndex > img->circles->length - 1 || elemIndex < 0) {
      return false;
    }
    int index = 0;
    bool found = false;
    Circle *c = NULL;
    // iterate thru rectangles
    // from LinkedListAPI.c
    ListIterator iter = createIterator(img->circles);
    while ((c = nextElement(&iter)) != NULL) {
      // find index of rectangle
      if (index == elemIndex) {
        // now check if we need to update any of the circle attributes
        if (strcmp(newAttribute->name, "cx") == 0) {
          c->cx = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } else if (strcmp(newAttribute->name, "cy") == 0) {
          c->cy = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } else if (strcmp(newAttribute->name, "r") == 0) {
          c->r = atof(newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } 
        if (getLength(c->otherAttributes) != 0) { // we know its otherattrbutes
          Attribute *attr = NULL;
          // from LinkedListAPI.c
          ListIterator iter2 = createIterator(c->otherAttributes);
          while ((attr = nextElement(&iter2)) != NULL) {
            // check if that attribute exists
            if (strcmp(newAttribute->name, attr->name) == 0) {
              strcpy(attr->value, newAttribute->value);
              deleteAttribute(newAttribute);
              found = true;
              return true;
            }
          }
          // if not found
          if (found == false) {
            insertBack(c->otherAttributes, newAttribute);
            return true;
          } 
        } else {
          insertBack(c->otherAttributes, newAttribute);
          return true;
        }
      }
      index++;
    }
  }
  
  // check for paths
  if (elemType == PATH) {
    // quick valid check
    if (elemIndex > img->paths->length - 1 || elemIndex < 0) {
      return false;
    }
    int index = 0;
    bool found = false;
    Path *p = NULL;
    // iterate thru path
    // from LinkedListAPI.c
    ListIterator iter = createIterator(img->paths);
    while ((p = nextElement(&iter)) != NULL) {
      // find index of path
      if (index == elemIndex) {
        // now check if we need to update any of the path attributes
        if (strcmp(newAttribute->name, "d") == 0) {
          strcpy(p->data, newAttribute->value);
          deleteAttribute(newAttribute);
          found = true;
          return true;
        } 
        if (getLength(p->otherAttributes) != 0) { // we know its otherattrbutes
          Attribute *attr = NULL;
          // from LinkedListAPI.c
          ListIterator iter2 = createIterator(p->otherAttributes);
          while ((attr = nextElement(&iter2)) != NULL) {
            // check if that attribute exists
            if (strcmp(newAttribute->name, attr->name) == 0) {
              strcpy(attr->value, newAttribute->value);
              deleteAttribute(newAttribute);
              found = true;
              return true;
            } 
          }
          // if not found
          if (found == false) {
            insertBack(p->otherAttributes, newAttribute);
            return true;
          }
        } else {
          insertBack(p->otherAttributes, newAttribute);
          return true;
        }
      }
      index++;
    }
  }

  // finally, check group
  if (elemType == GROUP) {
    // quick valid check
    if (elemIndex > img->groups->length - 1 || elemIndex < 0) {
      return false;
    }
    int index = 0;
    bool found = false;
    Group *g = NULL;
    // iterate thru groups
    // from LinkedListAPI.c
    ListIterator iter = createIterator(img->groups); 
    while ((g = nextElement(&iter)) != NULL) {
      if (index == elemIndex) {
        if (getLength(g->otherAttributes) != 0) {
          // now that index is the same, iterate thru otherattr of group
          // from LinkedListAPI.c
          ListIterator iter2 = createIterator(g->otherAttributes);
          Attribute* attr = NULL;
          while ((attr = nextElement(&iter2)) != NULL) {
            if (strcmp(newAttribute->name, attr->name) == 0) {
              strcpy(attr->value, newAttribute->value);
              deleteAttribute(newAttribute);
              found = true;
              return true;
            }
          }
          // if not found
          if (found == false) {
            insertBack(g->otherAttributes, newAttribute);
            return true;
          } 
        } else {
          insertBack(g->otherAttributes, newAttribute);
          return true;
        }
      }
      index++;
    }
  }
  // if any check didnt return true, adding it failed so return false
  return false;
}

void addComponent(SVG* img, elementType type, void* newElement) {
  // check for null args
  if (img == NULL || newElement == NULL)  {
    return;
  }
  // make sure type is valid
  if (type != RECT && type != CIRC && type != PATH) {
    return;
  } 
  // make sure shapes are valid
  if (!(isValidAttr(img->otherAttributes) && isValidRect(img->rectangles) && isValidCircle(img->circles) && isValidPath(img->paths)) && isValidGroup(img->groups)) {
    return;
  } 
  // now check each type and add the new element
  if (type == RECT) {
    insertBack(img->rectangles, newElement);
  }
  else if (type == CIRC) {
    insertBack(img->circles, newElement);
  }
  else if (type == PATH) {
    insertBack(img->paths, newElement);
  }
}
/*
END MODULE 2 A2
*/

/*
START MODULE 3 A2
*/
char* attrToJSON(const Attribute *a) {
  // check args first and return empty json
  if (a == NULL) {
    return "{}";
  }
  // allocate space and write in the values
  char *str = malloc((strlen(a->name) + strlen(a->value) + 1000) * sizeof(char));
  sprintf(str, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);
  return str;
}

char* circleToJSON(const Circle *c) {
  // check args first and return empty json 
  if (c == NULL) {
    return "{}";
  }
  char *attrList = attrListToJSON(c->otherAttributes);
  // allocate space and write in the values
  char *str = malloc((strlen(c->units) + strlen(attrList) + 1000) * sizeof(char));
  sprintf(str, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\",\"otherAttrs\":%s}", c->cx, c->cy, c->r, c->otherAttributes->length, c->units, attrList);
  free(attrList);
  return str;
}

char* rectToJSON(const Rectangle *r) {
  // check args first and return empty json
  if (r == NULL) {
    return "{}";
  }
  char *attrList = attrListToJSON(r->otherAttributes);
  // allocate space and write in the values
  char *str = malloc((strlen(r->units) + strlen(attrList) + 1000) * sizeof(char));
  sprintf(str, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\",\"otherAttrs\":%s}", r->x, r->y, r->width, r->height, r->otherAttributes->length, r->units, attrList);
  free(attrList);
  return str;
}

char* pathToJSON(const Path *p) {
  // check args first and return empty json
  if (p == NULL) { 
    return "{}";
  }
  Path *temp = (Path*)p;
  char *str;
  char data[64] = "";
  // truncate as per pdf instructions
  strncpy(data, (char*)temp->data, 64);
  data[63] = '\0';
  char *attrList = attrListToJSON(p->otherAttributes);
  // allocate space to write in the values
  str = (char*)malloc(sizeof(char) + 1000000 + strlen(attrList));
  sprintf(str, "{\"d\":\"%s\",\"numAttr\":%d,\"otherAttrs\":%s}", data, temp->otherAttributes->length, attrList);
  free(attrList);
  return str;
}

char* groupToJSON(const Group *g) {
  // check args first and return empty json
  if (g == NULL) {
    return "{}";
  }
  char *attrList = attrListToJSON(g->otherAttributes);
  // allocate space to write in the values
  char *str = malloc(sizeof(char) + 128 + strlen(attrList));
  int length = g->rectangles->length + g->circles->length + g->paths->length + g->groups->length;
  sprintf(str, "{\"children\":%d,\"numAttr\":%d,\"otherAttrs\":%s}", length, g->otherAttributes->length, attrList);
  free(attrList);
  return str;
}

char* attrListToJSON(const List *list) {
  if (list == NULL || list->head == NULL) {
    char *invalidStr = malloc(sizeof(char) * 4);
    strcpy(invalidStr, "[]");
    return invalidStr;
  }
  // iterate thru and dynamically allocate space for the string
  ListIterator iter = createIterator((List*)list);
  Attribute *attr = NULL;
  char *str = malloc(sizeof(char) + 1024);
  // first char of string
  strcpy(str, "[");
  // now iterate
  while ((attr = nextElement(&iter)) != NULL) {
    char *jsonAttr = attrToJSON(attr);
    str = realloc(str, strlen(str) + strlen(jsonAttr) + 8);
    strcat(str, jsonAttr);
    strcat(str, ",");
    free(jsonAttr);
  }
  // now close of json string
  str[strlen(str) - 1] = ']';
  return str;
}

char* circListToJSON(const List *list) {
  // check args first and return empty []
  if (list == NULL || list->head == NULL) {
    char *invalidStr = malloc(sizeof(char) * 4);
    strcpy(invalidStr, "[]");
    return invalidStr;
  }
  // iterate thru and dynamically allocate space for the string
  ListIterator iter = createIterator((List*)list);
  Circle *c = NULL;
  char *str = malloc(sizeof(char) + 1024);
  // first char of string
  strcpy(str, "[");
  // now iterate
  while ((c = nextElement(&iter)) != NULL) {
    char *jsonCirc = circleToJSON(c);
    str = realloc(str, strlen(str) + strlen(jsonCirc) + 8);
    strcat(str, jsonCirc);
    strcat(str, ",");
    free(jsonCirc);
  }
  // now close of json string
  str[strlen(str) - 1] = ']';
  return str;
}

char* rectListToJSON(const List *list) {
  // check args first and return empty []
  if (list == NULL || list->head == NULL) {
    char *invalidStr = malloc(sizeof(char) * 4);
    strcpy(invalidStr, "[]");
    return invalidStr;
  }
  // iterate thru and dynamically allocate space for the string
  ListIterator iter = createIterator((List*)list);
  Rectangle *r = NULL;
  char *str = malloc(sizeof(char) + 1024);
  // first char of string
  strcpy(str, "[");
  // now iterate
  while ((r = nextElement(&iter)) != NULL) {
    char *jsonRect = rectToJSON(r);
    str = realloc(str, strlen(str) + strlen(jsonRect) + 8);
    strcat(str, jsonRect);
    strcat(str, ",");
    free(jsonRect);
  }
  // now close of json string
  str[strlen(str) - 1] = ']';
  return str;
}

char* pathListToJSON(const List *list) {
  // check args first and return empty []
  if (list == NULL || list->head == NULL) {
    char *invalidStr = malloc(sizeof(char) * 4);
    strcpy(invalidStr, "[]");
    return invalidStr;
  }
  // iterate thru and dynamically allocate space for the string
  ListIterator iter = createIterator((List*)list);
  Path *p = NULL;
  char *str = malloc(sizeof(char) + 1000000);
  // first char of string
  strcpy(str, "[");
  // now iterate
  while ((p = nextElement(&iter)) != NULL) {
    char *jsonPath = pathToJSON(p);
    str = realloc(str, strlen(str) + strlen(jsonPath) + 1000);
    strcat(str, jsonPath);
    strcat(str, ",");
    free(jsonPath);
  }
  // now close of json string
  str[strlen(str) - 1] = ']';
  return str;
}

char* groupListToJSON(const List *list) {
  // check args first and return empty []
  if (list == NULL || list->head == NULL) {
    char *invalidStr = malloc(sizeof(char) * 4);
    strcpy(invalidStr, "[]");
    return invalidStr;
  }
  // iterate thru and dynamically allocate space for the string
  ListIterator iter = createIterator((List*)list);
  Group *g = NULL;
  char *str = malloc(sizeof(char) + 1024);
  // first char of string
  strcpy(str, "[");
  // now iterate
  while ((g = nextElement(&iter)) != NULL) {
    char *jsonGroup = groupToJSON(g);
    str = realloc(str, strlen(str) + strlen(jsonGroup) + 8);
    strcat(str, jsonGroup);
    strcat(str, ",");
    free(jsonGroup);
  }
  // now close of json string
  str[strlen(str) - 1] = ']';
  return str;
}

char* SVGtoJSON(const SVG* img) {
  if (img == NULL) {
    return "{}";
  }
  char *str = malloc(sizeof(char) * 128);
  List *r = getRects(img);
  List *c = getCircles(img);
  List *p = getPaths(img);
  List *g = getGroups(img);
  sprintf(str, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", r->length, c->length, p->length, g->length);
  freeList(r);
  freeList(c);
  freeList(p);
  freeList(g);
  return str;
}
/*
END MODULE 3 A2
*/

/*
START BONUS FUNCS A2
*/
SVG* JSONtoSVG(const char* svgString) {
  // check for null args first
  if (svgString == NULL) {
    return NULL;
  }
  // allocated svg image and set title,desc and ns to empty
  // have to use calloc because malloc sets garbage value and valgrind gives conditional jump errors
  SVG *img = calloc(1, sizeof(SVG));
  strcpy(img->title, "");
  strcpy(img->description, "");
  strcpy(img->namespace, "");

  // init all lists as per pdf
  img->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
  img->rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
  img->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
  img->paths = initializeList(&pathToString, &deletePath, &comparePaths);
  img->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);

  // get the start string of the title and add 8 to get just "title"
  char *titleStart = "";
  titleStart = strstr(svgString, "title") + 8;
  // get the end of title which happens at the , seperating with desc
  char *titleEnd = "";
  titleEnd = strstr(titleStart, "\",\"");
  // calculate the length of those two to put as the buffer when copying over
  long len1 = titleEnd - titleStart;
  // set title
  strncpy(img->title, titleStart, len1);
  img->title[255] = '\0';

  // get the start of string of the description and add 8 to get just "descr"
  char *descStart = "";
  descStart = strstr(svgString, "descr") + 8;
  // get the end of descr which happens before the closing brace
  char *descEnd = "";
  descEnd = strstr(descStart, "\"}");
  // calculate the length of those two to put as the buffer when copying over
  long len2 = descEnd - descStart;
  // set description
  strncpy(img->description, descStart, len2);
  img->description[255] = '\0';
  
  // set namespace
  strncpy(img->namespace, "http://www.w3.org/2000/svg", 255);
  img->namespace[255] = '\0';
  return img;
}

Rectangle* JSONtoRect(const char* svgString) {
  // check for null args first
  if (svgString == NULL) {
    return NULL;
  }
  // create and init values for rectangle
  Rectangle *r = calloc(1, sizeof(Rectangle));
  r->x = 0;
  r->y = 0;
  r->width = 0;
  r->height = 0;
  strcpy(r->units, "");
  r->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
  char *xVal = "";
  char *yVal = "";
  char *wVal = "";
  char *hVal = "";
  char *unitsVal = "";
  char *end = "";
  long len = 0;
  // now search for each value using strstr + 3 to get exactly the value and then strtof the value to set it
  xVal = strstr(svgString, "x") + 3;
  r->x = strtof(xVal, NULL);
  yVal = strstr(svgString, "y") + 3;
  r->y = strtof(yVal, NULL);
  wVal = strstr(svgString, "w") + 3;
  r->width = strtof(wVal, NULL);
  hVal = strstr(svgString, "h") + 3;
  r->height = strtof(hVal, NULL);
  // can get units using similar method to getting title and desc in above function
  unitsVal = strstr(svgString, "units") + 8;
  end = strstr(unitsVal, "\"}");
  len = (end - unitsVal);
  strncpy(r->units, unitsVal, len);
  return r;
}

Circle* JSONtoCircle(const char* svgString) {
  // check for null args first
  if (svgString == NULL) {
    return NULL;
  }
  // create and init values for rectangle
  Circle *c = calloc(1, sizeof(Circle));
  c->cx = 0;
  c->cy = 0;
  c->r = 0;
  strcpy(c->units, "");
  c->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
  char *cxVal = "";
  char *cyVal = "";
  char *r = "";
  char *unitsVal = "";
  char *end = "";
  // now search for each value using strstr + 3 to get exactly the value and then strtof the value to set it
  cxVal = strstr(svgString, "cx") + 4;
  c->cx = strtof(cxVal, NULL);
  cyVal = strstr(svgString, "cy") + 4;
  c->cy = strtof(cyVal, NULL);
  r = strstr(svgString, "r") + 3;
  c->r = strtof(r, NULL);
  // can get units using similar method to getting title and desc in above function
  unitsVal = strstr(svgString, "units") + 8;
  end = strstr(unitsVal, "\"}");
  long len = end - unitsVal;
  strncpy(c->units, unitsVal, len);
  return c;
}
/*
END BONUS FUNCS A2
*/
