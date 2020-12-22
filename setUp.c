#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "setUp.h"

void readEverything(FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, FileGroup *fileGroup){
    fread(&(headGroup->fileHd1.bfType), 2, 1, fileGroup->file1);
	fread(&(headGroup->fileHd2.bfType), 2, 1, fileGroup->file2);
	
	fread(&(headGroup->fileHd1.bfSize), 4, 1, fileGroup->file1);
	fread(&(headGroup->fileHd2.bfSize), 4, 1, fileGroup->file2);

	fread(&(headGroup->fileHd1.bfReserved1), 2, 1, fileGroup->file1);
	fread(&(headGroup->fileHd2.bfReserved1), 2, 1, fileGroup->file2);

	fread(&(headGroup->fileHd1.bfReserved2), 2, 1, fileGroup->file1);
	fread(&(headGroup->fileHd2.bfReserved2), 2, 1, fileGroup->file2);

	fread(&(headGroup->fileHd1.bfOffBits), 4, 1, fileGroup->file1);
	fread(&(headGroup->fileHd2.bfOffBits), 4, 1, fileGroup->file2);

	fread(&(infoGroup->infoHd1), sizeof(tagBITMAPINFOHEADER), 1, fileGroup->file1);
	fread(&(infoGroup->infoHd2), sizeof(tagBITMAPINFOHEADER), 1, fileGroup->file2);
}