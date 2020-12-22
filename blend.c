#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dataStructure.h"
#include "blendTools.h"
#include "checkInput.h"
#include "setUp.h"
#include "sizeComparison.h"

int main(int argc, char *argv[]){
	int x, y, bigImageFirst = 0, x_1, y_1, x_2, y_2, finalSize;
	
	float dx, dy, orntX, orntY, argRatio;

	FileHeaderGroup headGroup;
	InfoHeaderGroup infoGroup;

	ImageAttributes bigAttributes, smallAttributes;

	unsigned char *smallImage, *bigImage, *finalImage,
		      bilnrPt, blend;

	FileGroup fileGroup;

	checkEverything(argc, argv, &argRatio, &fileGroup);

	readEverything(&headGroup, &infoGroup, &fileGroup);
	
	bigImageFirst = compareSizes(&bigAttributes, &smallAttributes, &headGroup, &infoGroup, &fileGroup);

	bigImage = (unsigned char *)malloc(bigAttributes.size);
    fread(bigImage, bigAttributes.size, 1, bigAttributes.file);
    smallImage = (unsigned char *)malloc(smallAttributes.size);
    fread(smallImage, smallAttributes.size, 1, smallAttributes.file);

	finalSize = bigAttributes.size;
	finalImage = (unsigned char *)malloc(finalSize);
	dx = (float)smallAttributes.width / bigAttributes.width;
	dy = (float)smallAttributes.height / bigAttributes.height;

	for(x = 0; x < bigAttributes.width; x++){
		for(y = 0; y < bigAttributes.height; y++){
			orntX = x * dx;
			orntY = y * dy;
			x_1 = (int)floor(orntX);
			x_2 = (int)ceil(orntX);
			y_1 = (int)floor(orntY);
			y_2 = (int)ceil(orntY);
			for (int z = 0; z < 3; z++){
				bilnrPt = getBilnrClr(x_1, x_2, y_1, y_2, dx, dy, smallAttributes.padWidth, 
						smallImage, z);
				if(bigImageFirst)
					blend = getBlend(argRatio, get(bigImage,x,y,bigAttributes.padWidth,z), bilnrPt);
				else
					blend = getBlend(argRatio, bilnrPt, get(bigImage,x,y,bigAttributes.padWidth, z));	
				
				set(finalImage,blend,x,y,bigAttributes.padWidth, z);
			}
	
		}
	}

	fwrite(&(headGroup.finalFileHd.bfType), 2, 1, fileGroup.final);
	
    fwrite(&(headGroup.finalFileHd.bfSize), 4, 1, fileGroup.final);

	fwrite(&(headGroup.finalFileHd.bfReserved1), 2, 1, fileGroup.final);

	fwrite(&(headGroup.finalFileHd.bfReserved2), 2, 1, fileGroup.final);

	fwrite(&(headGroup.finalFileHd.bfOffBits), 4, 1, fileGroup.final);
	
	fwrite(&infoGroup.finalInfoHd, sizeof(tagBITMAPINFOHEADER), 1, fileGroup.final);
	fwrite(finalImage, infoGroup.finalInfoHd.biSizeImage, 1, fileGroup.final);
	
	fclose(fileGroup.file1);
	fclose(fileGroup.file2);
	fclose(fileGroup.final);
	free(bigImage);
	free(smallImage);
	free(finalImage);

	return 0;
}
