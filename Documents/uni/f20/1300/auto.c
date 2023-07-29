#include <stdio.h>
#include <string.h>

int main(){

int prices[] = {35, 19, 7, 12};
char *services[] = {"Oil change", "Tire rotation", "Car wash", "Car wax"};


printf("Davy's auto shop services\n");
printf("Oil change -- $35\n");
printf("Tire rotation -- $19\n");
printf("Car wash -- $7\n");
printf("Car wax -- $12\n");

printf("Select first service:\n");
scanf("%s", *services);
printf("Select second service:\n");
scanf("%s", *services);

printf("Davy's auto shop invoice\n");

if (strcmp(*services, "Oil change") == 0)
{
   
}

return 0;
}