/*
NAME: Maneesh Wijewardhana
ID: 1125828
COURSE: CIS*2750 (module 1 and 2 from A1) (module 1,2,3, 3 bonus, from A2)
DUE DATE: MARCH 2, 2022

This file contains functions that were created myself to aid in parsing an SVG
Some code snippets are from libXmlExample.c which I have commented on and cited
Using functions from LinkedListAPI.c to traverse some lists and insert elements

Thanks Denis!
*/
#include "SVGHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
START A1 HELPERS
*/
void createAndAddGroup(xmlNode *node, List *list) {
  Group *g = (Group *)malloc(sizeof(Group));
  // allocate lists on stack and returns the list struct for each
  // from LinkedListAPI.c
  g->otherAttributes =
      initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
  g->rectangles =
      initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
  g->circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
  g->paths = initializeList(&pathToString, &deletePath, &comparePaths);
  g->groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
  // now check each shape/attr
  // loop from libXmlExample.c
  for (xmlNode *curr = node->children; curr != NULL; curr = curr->next) {
    if (curr->type == XML_ELEMENT_NODE) { // make sure valid node
      // call function that goes thru each node attribute and sets the values
      // accordingly then adds to list
      if (strcmp((char *)curr->name, "rect") == 0) {
        createAndAddRectangle(curr, g->rectangles);
      }
      if (strcmp((char *)curr->name, "circle") == 0) {
        createAndAddCircle(curr, g->circles);
      }
      if (strcmp((char *)curr->name, "path") == 0) {
        createAndAddPath(curr, g->paths);
      }
      if (strcmp((char *)curr->name, "g") == 0) {
        createAndAddGroup(curr, g->groups);
      }
    }
  }
  // else its other attribute
  // loop from libxmlexample.c
  for (xmlAttr *attr = node->properties; attr != NULL; attr = attr->next) {
    // from LinkedListAPI.c
    insertBack(g->otherAttributes, createAttribute(attr));
  }
  // put everything into main group list
  // from LinkedListAPI.c
  insertBack(list, g);
}

void createAndAddRectangle(xmlNode *node, List *list) {
  Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));
  // because malloc is fucking stupid and valgrind complains so much
  r->x = 0;
  r->y = 0;
  r->width = 0;
  r->height = 0;
  strcpy(r->units, "");
  // from LinkedListAPI.c
  r->otherAttributes =
      initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

  // for strtof
  char *units = NULL;

  for (xmlAttr *attr = node->properties; attr != NULL; attr = attr->next) {
    if (strcmp((char *)attr->name, "x") == 0) {
      // if first elm has units, we assume units for all and vice versa
      r->x = strtof((char *)attr->children->content, &units);
    } else if (strcmp((char *)attr->name, "y") == 0) {
      r->y = strtof((char *)attr->children->content, NULL);
    } else if (strcmp((char *)attr->name, "width") == 0) {
      r->width = strtof((char *)attr->children->content, NULL);
    } else if (strcmp((char *)attr->name, "height") == 0) {
      r->height = strtof((char *)attr->children->content, NULL);
    } else { // if none, we know its other attributes
      // from LinkedListAPI.c
      insertBack(r->otherAttributes, createAttribute(attr));
    }
  }
  // now if that first units for r->x was not null, we can set those units for
  // it
  if (units != NULL) {
    strncpy(r->units, units, 49);
  }
  // add it now to rectangle list
  insertBack(list, r);
}

void createAndAddCircle(xmlNode *node, List *list) {
  Circle *c = (Circle *)malloc(sizeof(Circle));
  c->cx = 0;
  c->cy = 0;
  c->r = 0;
  strcpy(c->units, "");
  // from LinkedListAPI.c
  c->otherAttributes =
      initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

  // need for strtof
  char *units = NULL;

  for (xmlAttr *attr = node->properties; attr != NULL; attr = attr->next) {
    if (strcmp((char *)attr->name, "cx") == 0) {
      // if first elm has units, we assume units for all and vice versa
      c->cx = strtof((char *)attr->children->content, &units);
    } else if (strcmp((char *)attr->name, "cy") == 0) {
      c->cy = strtof((char *)attr->children->content, NULL);
    } else if (strcmp((char *)attr->name, "r") == 0) {
      c->r = strtof((char *)attr->children->content, NULL);
    } else {
      // from LinkedListAPI.c
      // inserting all attributes into otherattr list for circles
      insertBack(c->otherAttributes, createAttribute(attr));
    }
  }
  // only if there were units will we copy them over
  if (units != NULL) {
    strncpy(c->units, units, 49);
  }
  // from LinkedListAPI.c
  // insert everything back into main c list
  insertBack(list, c);
}

void createAndAddPath(xmlNode *node, List *list) {
  // Path* p = (Path*)malloc(sizeof(Path) + 10000000 * sizeof(char));
  Path *p = malloc(sizeof(Path) + 10000);
  strcpy(p->data, "");
  // from LinkedListAPI.c
  p->otherAttributes =
      initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

  // loop from libxmlexample.c
  for (xmlAttr *attr = node->properties; attr != NULL; attr = attr->next) {
    xmlNode *value = attr->children;
    char *content = (char *)(value->content);
    if (strcmp((char *)attr->name, "d") == 0) {
      p = realloc(p,
                  sizeof(Path) + (strlen(content) + 1) * sizeof(char) + 1000);
      strcpy(p->data, content);
    } else {
      // if its not "d", add otherattr to otherattr path list
      insertBack(p->otherAttributes, createAttribute(attr));
    }
  }
  // insert everything to main path list
  insertBack(list, p);
}

Attribute *createAttribute(xmlAttr *attr) {
  // need to malloc the size of the attribute + the length of the content * size
  // of char
  Attribute *attrToBeAdded = (Attribute *)malloc(
      sizeof(Attribute) + strlen((char *)attr->children->content) +
      10000 * sizeof(char));
  // need to malloc the length of the attribute name + 10000 for security lol *
  // size of char
  attrToBeAdded->name =
      (char *)malloc(strlen((char *)attr->name) + 10000 * sizeof(char));
  // now we can just copy to val prop and name prop making sure to typecast
  strcpy(attrToBeAdded->value, (char *)attr->children->content);
  strcpy(attrToBeAdded->name, (char *)attr->name);

  // now return the fully created attribute
  return attrToBeAdded;
}

void recurseGroups(List *list, Group *root) {
  // create iter to go through groups
  // from LinkedListAPI.c
  ListIterator iter = createIterator(root->groups);
  // g is the next element in list
  // from LinkedListAPI.c
  Group *g = nextElement(&iter);
  // add to list until no more groups left
  while (g != NULL) {
    recurseGroups(list, g); // keep going thru nested groups
    insertBack(list, g);    // add to list
    g = nextElement(&iter); // next
  }
}

/*
END A1 HELPERS
*/

/*
START A2 HELPERS
*/

xmlDoc *svgToXmlDoc(const SVG *img) {
  if (img == NULL) {
    return NULL;
  }
  // add basic properties like version, type, and namespace
  // need to typecast xmlChar for xml methods
  xmlDoc *imgXML = xmlNewDoc((xmlChar *)"1.0");
  xmlNode *root = xmlNewNode(NULL, (xmlChar *)"svg");
  // first use xmlnewns to create the namespace
  // then use xmlsetns to set the namespace for root node
  xmlNs *namespace = xmlNewNs(root, (xmlChar *)img->namespace, NULL);
  xmlSetNs(root, namespace);
  xmlDocSetRootElement(imgXML, root);
  // now do title and description but check for them first
  if (strlen(img->title) > 0) {
    xmlNode *imgTitle =
        xmlNewNode(xmlDocGetRootElement(imgXML)->ns, (xmlChar *)"title");
    xmlNodeSetContent(imgTitle, (xmlChar *)img->title);
    xmlAddChild(xmlDocGetRootElement(imgXML), imgTitle);
  }
  if (strlen(img->description) > 0) {
    xmlNode *imgDesc =
        xmlNewNode(xmlDocGetRootElement(imgXML)->ns, (xmlChar *)"desc");
    xmlNodeSetContent(imgDesc, (xmlChar *)img->description);
    xmlAddChild(xmlDocGetRootElement(imgXML), imgDesc);
  }
  // helper functions to add each shape/attr in the right order
  if (img->otherAttributes->length > 0) {
    addAttributesXML(img->otherAttributes, xmlDocGetRootElement(imgXML));
  }
  if (img->rectangles->length > 0) {
    addRectsXML(img->rectangles, xmlDocGetRootElement(imgXML));
  }
  if (img->circles->length > 0) {
    addCirclesXML(img->circles, xmlDocGetRootElement(imgXML));
  }
  if (img->paths->length > 0) {
    addPathsXML(img->paths, xmlDocGetRootElement(imgXML));
  }
  if (img->groups->length > 0) {
    addGroupsXML(img->groups, xmlDocGetRootElement(imgXML));
  }
  return imgXML;
}

void addRectsXML(List *list, xmlNode *node) {
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  Rectangle *r = NULL;
  // iterate until no more rects
  while ((r = nextElement(&iter)) != NULL) {
    xmlNode *tempNode = xmlNewNode(node->ns, (xmlChar *)"rect");
    // adds all the props to the new xml node
    char *val = malloc(sizeof(char) * 1024);
    sprintf(val, "%f%s", r->x, r->units);
    xmlNewProp(tempNode, (xmlChar *)"x", (xmlChar *)val);
    sprintf(val, "%f%s", r->y, r->units);
    xmlNewProp(tempNode, (xmlChar *)"y", (xmlChar *)val);
    sprintf(val, "%f%s", r->width, r->units);
    xmlNewProp(tempNode, (xmlChar *)"width", (xmlChar *)val);
    sprintf(val, "%f%s", r->height, r->units);
    xmlNewProp(tempNode, (xmlChar *)"height", (xmlChar *)val);
    addAttributesXML(r->otherAttributes, tempNode);
    // adds new node to svg doc
    xmlAddChild(node, tempNode);
    free(val);
  }
}

void addAttributesXML(List *list, xmlNode *node) {
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  Attribute *attr = NULL;
  // traverse until attr is null
  while ((attr = nextElement(&iter)) != NULL) {
    xmlNewProp(node, (xmlChar *)attr->name, (xmlChar *)attr->value);
  }
}

void addCirclesXML(List *list, xmlNode *node) {
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  Circle *c = NULL;
  // traverse until circles are null
  while ((c = nextElement(&iter)) != NULL) {
    xmlNode *tempNode = xmlNewNode(node->ns, (xmlChar *)"circle");
    // adds all the props to the new xml node
    char *val = malloc(sizeof(char) * 1024);
    sprintf(val, "%f%s", c->cx, c->units);
    xmlNewProp(tempNode, (xmlChar *)"cx", (xmlChar *)val);
    sprintf(val, "%f%s", c->cy, c->units);
    xmlNewProp(tempNode, (xmlChar *)"cy", (xmlChar *)val);
    sprintf(val, "%f%s", c->r, c->units);
    xmlNewProp(tempNode, (xmlChar *)"r", (xmlChar *)val);
    addAttributesXML(c->otherAttributes, tempNode);
    // adds new node to svg doc
    xmlAddChild(node, tempNode);
    free(val);
  }
}

void addPathsXML(List *list, xmlNode *node) {
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  Path *p = NULL;
  // traverse until no more paths
  while ((p = nextElement(&iter)) != NULL) {
    xmlNode *tempNode = xmlNewNode(node->ns, (xmlChar *)"path");
    // adds all the props to the new xml node
    char *val = malloc(sizeof(char) * (strlen(p->data) + 1000000));
    sprintf(val, "%s", p->data);
    xmlNewProp(tempNode, (xmlChar *)"d", (xmlChar *)val);
    addAttributesXML(p->otherAttributes, tempNode);
    // adds new node to svg doc
    xmlAddChild(node, tempNode);
    free(val);
  }
}

void addGroupsXML(List *list, xmlNode *node) {
  // from LinkedListAPi.c
  ListIterator iter = createIterator(list);
  Group *g = NULL;
  // traverse through until no more groups
  while ((g = nextElement(&iter)) != NULL) {
    xmlNode *tempNode = xmlNewNode(node->ns, (xmlChar *)"g");
    // adds all the props to the new xml node
    addAttributesXML(g->otherAttributes, tempNode);
    addRectsXML(g->rectangles, tempNode);
    addCirclesXML(g->circles, tempNode);
    addPathsXML(g->paths, tempNode);
    addGroupsXML(g->groups, tempNode);
    // adds new node to svg doc
    xmlAddChild(node, tempNode);
  }
}

bool fileExists(char *fileName) {
  if (fileName == NULL)
    return false;
  FILE *file = fopen(fileName, "r");
  if (file == NULL)
    return false;
  fclose(file);
  return true;
}

int isValidXml(xmlDoc *xml, const char *xsdFile) {
  // all xml variables
  xmlSchemaParserCtxt *parserContext = NULL;
  xmlSchema *schema = NULL;
  xmlSchemaValidCtxt *validator = NULL;
  int ret = -1;

  FILE *fp = fopen(xsdFile, "r");
  parserContext = xmlSchemaNewParserCtxt(xsdFile);
  schema = xmlSchemaParse(parserContext);
  validator = xmlSchemaNewValidCtxt(schema);

  // all xml validation against schema files
  if (xml == NULL || xsdFile == NULL || fp == NULL || parserContext == NULL ||
      schema == NULL || validator == NULL) {
    xmlFreeDoc(xml);
  } else {
    ret = xmlSchemaValidateDoc(validator, xml);
    if (parserContext != NULL) {
      xmlSchemaFreeParserCtxt(parserContext);
    }
    if (schema != NULL) {
      xmlSchemaFree(schema);
    }
    if (validator != NULL) {
      xmlSchemaFreeValidCtxt(validator);
    }
  }
  fclose(fp);
  return ret;
}

bool isValidAttr(List *list) {
  // check for null list first
  if (list == NULL) {
    return false;
  }
  // now iterate thru and check for null values
  Attribute *attr = NULL;
  ListIterator iter = createIterator(list);
  while ((attr = nextElement(&iter)) != NULL) {
    if (attr->name == NULL) {
      return false;
    }
  }
  return true;
}

bool isValidRect(List *list) {
  // check for null list first
  if (list == NULL) {
    return false;
  }
  // now iterate thru and check for null values
  Rectangle *r = NULL;
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  while ((r = nextElement(&iter)) != NULL) {
    if (r->width < 0 || r->height < 0 || r->otherAttributes == NULL ||
        !isValidAttr(r->otherAttributes)) {
      return false;
    }
  }
  return true;
}

bool isValidCircle(List *list) {
  // check for null list first
  if (list == NULL) {
    return false;
  }
  // now iterate thru and check for null values as well as negative radius
  Circle *c = NULL;
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  while ((c = nextElement(&iter)) != NULL) {
    if (c->r < 0 || c->otherAttributes == NULL ||
        !isValidAttr(c->otherAttributes)) {
      return false;
    }
  }
  return true;
}

bool isValidPath(List *list) {
  // check for null list first
  if (list == NULL) {
    return false;
  }
  // now iterate thru and check for null values
  Path *p = NULL;
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  while ((p = nextElement(&iter)) != NULL) {
    if (p->data == NULL || p->otherAttributes == NULL ||
        !isValidAttr(p->otherAttributes)) {
      return false;
    }
  }
  return true;
}

bool isValidGroup(List *list) {
  // check for null list first
  if (list == NULL) {
    return false;
  }
  // now iterate thru and check for null values using above helper funcs
  Group *g = NULL;
  // from LinkedListAPI.c
  ListIterator iter = createIterator(list);
  while ((g = nextElement(&iter)) != NULL) {
    if (!isValidAttr(g->otherAttributes) || !isValidRect(g->rectangles) ||
        !isValidCircle(g->circles) || !isValidPath(g->paths) ||
        !isValidGroup(g->groups)) {
      return false;
    }
  }
  return true;
}

/*
END A2 HELPERS
*/

// SOME HELPERS FOR A3
char *fileToJSON(char *filename, char *schema) {
  // checknull args first
  if (filename == NULL || schema == NULL) {
    return NULL;
  }
  // create the svg
  SVG *img = createValidSVG(filename, schema);
  // get summary of it
  char *imageJSON = SVGtoJSON(img);
  // free it
  deleteSVG(img);
  // return it
  return imageJSON;
}

bool validateFile(char *filename, char *schema) {
  // check for null args
  if (filename == NULL || schema == NULL) {
    return false;
  }
  // create the svg
  SVG *img = createValidSVG(filename, schema);
  // if its null then its not valid
  if (img == NULL) {
    return false;
  } else { // its valid and return true but free image
    deleteSVG(img);
    return true;
  }
}

char *imageToJSON(char *filename, char *schema) {
  // check for null args first
  if (filename == NULL || schema == NULL) {
    return NULL;
  }
  // create the image and check for null image
  SVG *img = createValidSVG(filename, schema);
  if (img == NULL) {
    return NULL;
  }
  // use getters to get each shape and use list functions to get json string of
  // it
  List *rects = getRects(img);
  char *rectsJSON = rectListToJSON(rects);
  List *circles = getCircles(img);
  char *circlesJSON = circListToJSON(circles);
  List *paths = getPaths(img);
  char *pathsJSON = pathListToJSON(paths);
  List *groups = getGroups(img);
  char *groupsJSON = groupListToJSON(groups);

  // allocate memory for final json string
  char *str = calloc(strlen(rectsJSON) + strlen(circlesJSON) +
                         strlen(pathsJSON) + strlen(groupsJSON) + 128,
                     sizeof(char));

  sprintf(str, "{\"rectangles\":%s,\"circles\":%s,\"paths\":%s,\"groups\":%s}",
          rectsJSON, circlesJSON, pathsJSON, groupsJSON);

  // free all memory and return the json string
  deleteSVG(img);
  freeList(rects);
  free(rectsJSON);
  freeList(circles);
  free(circlesJSON);
  freeList(paths);
  free(pathsJSON);
  freeList(groups);
  free(groupsJSON);

  return str;
}

char *getTitle(char *filename, char *schema) {
  // check for null args first
  if (filename == NULL || schema == NULL) {
    return NULL;
  }
  // create the image and check for null image
  SVG *img = createValidSVG(filename, schema);
  if (img == NULL) {
    return NULL;
  }

  // allocate memory for final json string
  char *str = calloc(strlen(img->title) + 128, sizeof(char));
  strcpy(str, img->title);
  deleteSVG(img);
  return str;
}

char *getDesc(char *filename, char *schema) {
  // check for null args first
  if (filename == NULL || schema == NULL) {
    return NULL;
  }
  // create the image and check for null image
  SVG *img = createValidSVG(filename, schema);
  if (img == NULL) {
    return NULL;
  }

  // allocate memory for final json string
  char *str = calloc(strlen(img->description) + 128, sizeof(char));
  strcpy(str, img->description);
  deleteSVG(img);
  return str;
}

bool writeTitle(char *filename, char *schema, char *title) {
  // check for null args first
  if (filename == NULL || schema == NULL || title == NULL) {
    return false;
  }
  // create the svg and check for null
  SVG *img = createValidSVG(filename, schema);
  if (img == NULL) {
    return false;
  }
  // copy over the new title and write the svg file
  strcpy(img->title, title);
  bool ret = writeSVG(img, filename);
  // free memory
  deleteSVG(img);

  return ret;
}

bool writeDesc(char *filename, char *schema, char *desc) {
  // check for null args first
  if (filename == NULL || schema == NULL || desc == NULL) {
    return false;
  }
  // create the svg and check for null
  SVG *img = createValidSVG(filename, schema);
  if (img == NULL) {
    return false;
  }
  // else copy the new description, write the file, and free memory
  strcpy(img->description, desc);
  bool ret = writeSVG(img, filename);
  // free
  deleteSVG(img);
  return ret;
}

bool createEmptySVG(char *filename, char *svgString) {
  SVG *img = JSONtoSVG(svgString);
  if (img && validateSVG(img, "parser/svg.xsd")) {
    writeSVG(img, filename);
    return true;
  }
  return false;
}

bool scaleShapes(char *filename, char *component, float factor) {
  SVG *img = createValidSVG(filename, "parser/svg.xsd");
  List *shapes;
  bool ret = false;
  if (img != NULL) {
    if (strcmp(component, "Rectangle") == 0) {
      shapes = getRects(img);
    } else {
      shapes = getCircles(img);
    }
    if (shapes != NULL) {
      void *elm;
      ListIterator iter = createIterator(shapes);
      while ((elm = nextElement(&iter)) != NULL) {
       if (strcmp(component, "Rectangle") == 0) {
          Rectangle *rect = (Rectangle *)elm;
          rect->height = (rect->height) * factor;
          rect->width = (rect->width) * factor;
        } else {
          Circle *circ = (Circle *)elm;
          circ->r = (circ->r) * factor;
        }
      }
      freeList(shapes);
      if (validateSVG(img, "parser/svg.xsd")) {
        ret = true;
        writeSVG(img, filename);
      }
    }
    deleteSVG(img);
  }
  return ret;
}

bool addShape(char *filename, char *shape, char *svgString) {
  bool ret = false;
  SVG *img = createValidSVG(filename, "parser/svg.xsd");
  if (img != NULL) {
    void *comp = NULL;
    elementType type;
    if (strcmp(shape, "RECT") == 0) {//rectangle
      comp = JSONtoRect(svgString);
      type = RECT;
    } else { //circle
      comp = JSONtoCircle(svgString);
      type = CIRC;
    }
    addComponent(img, type, comp);
    if (validateSVG(img, "parser/svg.xsd")) {
      ret = true;
      writeSVG(img, filename);
    }
    //fail
  } else {
    ret = false;
  }
  deleteSVG(img);
  return ret;
}

bool setAttributeWrapper(char *filename, char *elemType, int elementIndex, char *newOtherAttr, char *newOtherAttrVal) {
  bool ret = false;
  SVG *img = createValidSVG(filename, "parser/svg.xsd");
  elementType type;
  // check what type we need to add
  if (strcmp("Rectangles", elemType) == 0) {
    type = RECT;
  } else if (strcmp("Circles", elemType) == 0) {
    type = CIRC;
  } else if (strcmp("Paths", elemType) == 0) {
    type = PATH;
  } else if (strcmp("Groups", elemType) == 0) {
    type = GROUP;
  } else {
    type = SVG_IMG;
  }
  // make new attr and copy over value
  Attribute *newAttr = (Attribute *)calloc(1, sizeof(Attribute));
  newAttr->name = (char *)calloc(strlen(newOtherAttr) + 1 + strlen(newAttr->value), sizeof(char));
  strcpy(newAttr->name, newOtherAttr);
  strcpy(newAttr->value, newOtherAttrVal);
  // set the attribute
  setAttribute(img, type, elementIndex, newAttr);
  // now validate to make sure before writing
  if (validateSVG(img, "parser/svg.xsd")) {
    ret = true;
    writeSVG(img, filename);
  }
  deleteSVG(img);
  return ret;
}
