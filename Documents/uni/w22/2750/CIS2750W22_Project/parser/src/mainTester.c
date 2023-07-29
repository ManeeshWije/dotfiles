#include "SVGParser.h"

int main(int argc, char** argv) {
  LIBXML_TEST_VERSION
  SVG *image = createValidSVG(argv[1], argv[2]);
  // SVG *image = JSONtoSVG("{\"title\":\"thisisatitleyes\",\"descr\":\"thisisadesricptionthisisadesricptionthisisadesricptionthisisadesricptionthisisadesricptionthisisadesricption\"}");
  // Rectangle *r = JSONtoRect("{\"x\":1,\"y\":2,\"w\":19,\"h\":15,\"units\":\"cm\"}");
  // Circle *c = JSONtoCircle("{\"cx\":32,\"cy\":32,\"r\":30,\"units\":\"\"}");
  // SVG *image = createSVG(argv[1]);
  char *temp = SVGToString(image);
  // char *temp17 = rectangleToString(r);
  // char *temp18 = circleToString(c);
  if (temp == NULL) {
    free(temp);
    // free(temp17);
    // free(temp18);
    // deleteRectangle(r);
    // deleteCircle(c);
    deleteSVG(image);
    return 0;
  }

  printf("%s\n", temp);
  // printf("%s\n", temp17);
  // printf("%s\n", temp18);


  // char attrName[] = "d";
  // char attrValue[] = "M200,300 L400,50 L600,300 L800,550 L1000,300, M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300,M200,300 L400,50 L600,300 L800,550 L1000,300";
  // Attribute *attr = NULL;
  // attr = (Attribute*)malloc(sizeof(Attribute) + strlen(attrValue) + 1 * sizeof(char));
  // strcpy(attr->value, attrValue);
  // attr->name = (char*)malloc(sizeof(char) * strlen(attrName) + 1);
  // strcpy(attr->name, attrName);

  char attrName2[] = "fill";
  char attrValue2[] = "reallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfillreallylongfill";
  Attribute *attr2 = NULL;
  attr2 = (Attribute*)malloc(sizeof(Attribute) + strlen(attrValue2) + 1 * sizeof(char));
  strcpy(attr2->value, attrValue2);
  attr2->name = (char*)malloc(sizeof(char) * strlen(attrName2) + 1);
  strcpy(attr2->name, attrName2);

  free(temp);
  // free(temp17);
  // free(temp18);
 
  if (validateSVG(image, argv[2]) == true) {
    setAttribute(image, SVG_IMG, 0, attr2);
  //   // setAttribute(image, PATH, 0, attr);
    // addComponent(image, RECT, r);
    // addComponent(image, CIRC, c);

    char *temp0 = SVGtoJSON(image);
    char *temp1 = attrListToJSON(image->otherAttributes);
    char *temp2 = circListToJSON(image->circles);
    char *temp3 = rectListToJSON(image->rectangles);
    char *temp4 = pathListToJSON(image->paths);
    char *temp5 = groupListToJSON(image->groups);

    printf("%s\n", temp0);
    printf("%s\n", temp1);
    printf("%s\n", temp2);
    printf("%s\n", temp3);
    printf("%s\n", temp4);
    printf("%s\n", temp5);

    free(temp0);
    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);
    free(temp5);
    writeSVG(image, "testing.svg");
  }
  // deleteRectangle(r);
  // deleteCircle(c);
  deleteSVG(image);
  return 0;
}