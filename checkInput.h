#ifndef CHECKINPUT_H
#define CHECKINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"

//Checks if user put correct arguments
int checkArgs(int argc, char *argv[]);

//Makes sure that input files are openable bmps
FILE *openCheck(char *filename, char *mode);

void checkEverything(int argc, char *argv[], float *argRatio, 
	FileGroup* fileGroup);

#endif