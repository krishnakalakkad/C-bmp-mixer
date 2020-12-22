#include <stdio.h>
#include <stdlib.h>
#include "checkInput.h"
#include "dataStructure.h"

int checkArgs(int argc, char *argv[]){
	float check;
	if (argc < 5){
		printf("usage: [programname] [imagefile1.bmp] [imagefile2.bmp] [ratio] [outputfile.bmp]");
		exit(1);	
	}
	if (sscanf(argv[3], "%f", &check) == EOF){
		printf("the ratio entered was not valid");
		exit(1);
	}
	if (check < 0 || check > 1){
		printf("the ratio entered was not valid");
		exit(1);
	}
}

FILE *openCheck(char *filename, char *mode){
	FILE *file;
	if ((file = fopen(filename, mode)) == NULL){
		printf("%s was not found", filename);
		exit(1);
	}

	return file;
}

void checkEverything(int argc, char *argv[], float *argRatio, 
	FileGroup* fileGroup){
	checkArgs(argc, argv);
	
	sscanf(argv[3], "%f", argRatio);
	fileGroup->file1 = openCheck(argv[1], "rb"), 
	fileGroup->file2 = openCheck(argv[2], "rb"),
	fileGroup->final = openCheck(argv[4], "wb");
}