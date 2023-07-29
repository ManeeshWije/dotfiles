#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int entries(char *filebase) {
    char filename[BUFFER];
    int ent;

    //puts idx extension
    strcpy(filename, filebase);
    strcat(filename, ".idx");
    // reads index file
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    ent = ftell(fp) / sizeof(long);
    fclose(fp);

    return ent;
}

void query(int negative1, char *str, int indexOfString) {
    //hardcoding "code" as file name
    char *v1 = "code";
    //usually always negative 1 when calling
    int i1 = negative1; 
    char *v2 = str;
    int i2 = indexOfString;

    // "code"
    int n1 = entries(v1);
    // string like building, room, subject, etc
    int n2 = entries(v2);

    char filename[BUFFER];
    char setFileName[BUFFER];
    char strIndex[BUFFER];
    //used to add index number in filename
    sprintf(strIndex, "%d", i2);
    
    //making rel files
    strcpy(filename, v1);
    strcat(filename, "_");
    strcat(filename, v2);
    strcat(filename, ".rel");

    if (strcmp("subject", str) != 0 && strcmp("courseno", str) != 0 && strcmp("days", str) != 0 && strcmp("from", str) != 0 && strcmp("to", str) != 0) {
        //create set file for index
        strcpy(setFileName, str);
        strcat(setFileName, "_");
        strcat(setFileName, strIndex);
        strcat(setFileName, ".set");
    } else {
        strcpy(setFileName, str);
        strcat(setFileName, ".set");
    }

    FILE *fp = fopen(filename, "rb");
    char *array = malloc(n1 * n2);
    fread(array, 1, n1 * n2, fp);
    fclose(fp);

    // writes into set file
    fp = fopen(setFileName, "wb");
    if ((i1 == -1) && (i2 >= 0)) {
        for (int i = 0; i < n1; i++) {
            int index = i * n2 + i2;
            fwrite(array + index, 1, 1, fp);
        }
    }

    if ((i1 > 0) && (i2 == -1)) {
        for (int j = 0; j < n2; j++) {
            int index = i1 * n2 + j;
            fwrite(array + index, 1, 1, fp);
        }
    }
    free(array);
    fclose(fp);
}

void and(char filename1[], char filename2[], char filename3[]) {
	//first two files are set files made and last one is the one we write to
    FILE *fp1 = fopen(filename1, "rb");
    FILE *fp2 = fopen(filename2, "rb");
    FILE *fp3 = fopen(filename3, "wb");
    char b1, b2, b3;

    while ( fread( &b1, 1, 1, fp1 )==1 && fread( &b2, 1, 1, fp2 ) ) {
        b3 = b1&&b2;
        fwrite( &b3, 1, 1, fp3 );
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3); 
}

char* getString(char *str, int index) {
    char *basename = str;
    int idx, idx2;
    idx = index;

    char txtfile[BUFFER];
    char idxfile[BUFFER];
    char *buffer = malloc(sizeof(BUFFER));

    FILE *fptxt, *fpidx;

    strcpy(txtfile, basename);
    strcat(txtfile, ".txt");

    strcpy(idxfile, basename);
    strcat(idxfile, ".idx");

    fptxt = fopen(txtfile, "r");
    fpidx = fopen(idxfile, "r");

    fseek( fpidx, sizeof(long)*idx, SEEK_SET );
    
    if ( fread( &idx2, sizeof(long), 1, fpidx ) != 1 ) {
        fprintf( stderr, "Error: invalid index\n" );
        exit(-1);
    }

    fclose(fpidx);

    fseek(fptxt, idx2, SEEK_SET);
    fgets(buffer, BUFFER, fptxt);
    //getting rid of new line
	buffer[strlen(buffer) - 1] = '\0';

    /*printf("%s", buffer);*/
    return buffer;
    fclose(fptxt); 
}

void set2idx(char filename[]) {
    char boolean;
    FILE *fp = fopen(filename, "rb" );
    for (int i=0; fread(&boolean,1,1,fp)==1; i++) {
        if (boolean)
        //printing index 
        printf( "%d\n", i );
	    fclose(fp);
    } 
    fclose(fp);
}

int saveIdx(char filename[]) {
    char boolean;
    FILE *fp = fopen(filename, "rb" );
    for (int i=0; fread(&boolean,1,1,fp)==1; i++) {
        if (boolean) {
            //returning index to use later
	    fclose(fp);
            return i;
        }
    }
    fclose(fp);
    return 0; 
}

void print(char filename[]) {
    char boolean;

    FILE *fp = fopen(filename, "rb");

    for (int i=0; fread(&boolean,1,1,fp)==1; i++) {
        if (boolean) {
            int counter = 0;
            /*int counter = 0;*/
            /*char **tempSubject = malloc(sizeof(char) * BUFFER);*/
            /*char **tempCourseno = malloc(sizeof(char) * BUFFER);*/
            /*char **tempDay= malloc(sizeof(char) * BUFFER);*/
            /*char **tempFrom = malloc(sizeof(char) * BUFFER);*/
            /*char **tempTo = malloc(sizeof(char) * BUFFER);*/
            //making set files based on indices
            query(i, "subject", -1);
            query(i, "courseno", -1);
            query(i, "days", -1);
            query(i, "from", -1);
            query(i, "to", -1);

            //saving the index in order to getstring it. Do for all
            int subjectIdx = saveIdx("subject.set");
            int coursenoIdx = saveIdx("courseno.set");
            int daysIdx = saveIdx("days.set");
            int fromIdx = saveIdx("from.set");
            int toIdx = saveIdx("to.set");
            
            char *subject = getString("subject", subjectIdx);
            char *courseno = getString("courseno", coursenoIdx);
            char *days = getString("days", daysIdx);
            char *from = getString("from", fromIdx);
            char *to = getString("to", toIdx);
            
            /*tempSubject[i] = getString("subject", subjectIdx);*/
            /*tempCourseno[i] = getString("courseno", coursenoIdx);*/
            /*tempDay[i] = getString("days", daysIdx);*/
            /*tempFrom[i] = getString("from", fromIdx);*/
            /*tempTo[i] = getString("to", toIdx);*/

            /*if ((strcmp(&subject[i-1], &subject[i]) == 0) && strcmp(&courseno[i-1], &courseno[i]) == 0 && strcmp(&days[i-1], &days[i]) == 0 && strcmp(&from[i-1], &from[i]) == 0 && strcmp(&to[i-1], &to[i]) == 0) {*/
                /*counter++;*/
                /*printf("%s*%s %s %s - %s\n", subject, courseno, days, from, to);*/
            /*}*/
            /*if(counter == 0) {*/
                /*printf("%s*%s %s %s - %s\n", subject, courseno, days, from, to);*/
            /*}*/
            printf("%s*%s %s %s - %s\n", subject, courseno, days, from, to);
        }
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    long hash_table_building[HASHSIZE];
    long hash_table_room[HASHSIZE];

    //error checking
    if (argc != 3) {
        fprintf(stderr, "Usage: %s bulding room\n", argv[0]);
        exit(-1);
    }

    // load hashtable from file into memory
    get_hashtable("building", hash_table_building);
    get_hashtable("room", hash_table_room);

    // open text file
    FILE *idxBuildingFile = fopen("building.idx", "r");
    FILE *txtBuildingFile = fopen("building.txt", "r");

    // print result of hash_lookup
    long buildingIdx = hash_lookup(argv[1], hash_table_building, idxBuildingFile, txtBuildingFile);

    /*printf("%ld\n", buildingIdx);*/

    fclose(idxBuildingFile);
    fclose(txtBuildingFile);

    //same thing as building except for room
    FILE *idxRoomFile = fopen("room.idx", "r");
    FILE *txtRoomFile = fopen("room.txt", "r");

    long roomIdx = hash_lookup(argv[2], hash_table_room, idxRoomFile, txtRoomFile);
    /*printf("%ld\n", roomIdx);*/

    fclose(idxRoomFile);
    fclose(txtRoomFile);

    //making each set file based on index
    query(-1, "building", buildingIdx);
    query(-1, "room", roomIdx);
    
    //for intersections
    char filename[BUFFER], filename1[BUFFER], filename2[BUFFER], filename3[BUFFER];

    char strIdxBuilding[BUFFER];
    char strIdxRoom[BUFFER];

    //creates building set file
    sprintf(strIdxBuilding, "%ld", buildingIdx);
    strcpy(filename1, "building_");
    strcat(filename1, strIdxBuilding);
    strcat(filename1, ".set");

    //creates room set file
    sprintf(strIdxRoom, "%ld", roomIdx);
    strcpy(filename2, "room_");
    strcat(filename2, strIdxRoom);
    strcat(filename2, ".set");

    //set file to be compute to
    strcpy(filename3, argv[1]);
    strcat(filename3, argv[2]);
    strcat(filename3, ".set" );

    //getting intersection
    and(filename1, filename2, filename3);

    //print all 
    strcpy(filename, argv[1]);
    strcat(filename, argv[2]);
    strcat(filename, ".set");
    print(filename);

    return 0;
}
