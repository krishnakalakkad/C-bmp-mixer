
#include <stdlib.h>
#include <stdio.h>
#include "dataStructure.h"

void attributeInitializer(ImageAttributes *attributes, tagBITMAPINFOHEADER infoHd, FILE* fp){
    attributes->width = infoHd.biWidth;
    attributes->padWidth = attributes->width * 3; //Every pixel has 3 bytes, each to account for RBG values respectively
    if ((attributes->padWidth) % 4 != 0)
        attributes->padWidth = (infoHd.biWidth * 3) + 4 - 
            (infoHd.biWidth * 3) % 4;
    attributes->height = infoHd.biHeight;
    attributes->size = infoHd.biSizeImage;
    attributes->file = fp; 
}

void setBigAttributes(ImageAttributes *bigAttributes, ImageAttributes *smallAttributes,
    FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, FileGroup *fileGroup, int image){
    if (image == 1){
        attributeInitializer(bigAttributes, infoGroup->infoHd1, fileGroup->file1);
        attributeInitializer(smallAttributes, infoGroup->infoHd2, fileGroup->file2);
    }else{
        attributeInitializer(bigAttributes, infoGroup->infoHd2, fileGroup->file2);
        attributeInitializer(smallAttributes, infoGroup->infoHd1, fileGroup->file1);
    }

}


int compareSizes(ImageAttributes *bigAttributes, ImageAttributes *smallAttributes, 
    FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, 
    FileGroup *fileGroup){
    if (infoGroup->infoHd1.biWidth > infoGroup->infoHd2.biWidth){
            headGroup->finalFileHd = headGroup->fileHd1;
            infoGroup->finalInfoHd = infoGroup->infoHd1;
            /*bigWidth = infoGroup.infoHd1.biWidth;
            bigpadWidth = bigWidth * 3; //Every pixel has 3 bytes, each to account for RBG values respectively
            if ((bigWidth * 3) % 4 != 0)
                bigpadWidth = (infoGroup.infoHd1.biWidth * 3) + 4 - 
                    (infoGroup.infoHd1.biWidth * 3) % 4;
            bigHeight = infoGroup.infoHd1.biHeight;
            bigSize = infoGroup.infoHd1.biSizeImage;
            setBigAttributes(bigAttributes);*/
            setBigAttributes(bigAttributes, smallAttributes, headGroup, infoGroup, fileGroup, 1);
            
            //DONT FORGET THIS NEXT LINE AT THE END
            
            /*bigImage = (unsigned char *)malloc(infoGroup->infoHd1.biSizeImage);
            fread(bigImage, infoGroup->infoHd1.biSizeImage, 1, fileGroup->file1);
            
            smallWidth = infoGroup->infoHd2.biWidth;
            smallpadWidth = smallWidth * 3;
            if ((smallWidth * 3) % 4 != 0)
                smallpadWidth = (infoGroup.infoHd2.biWidth * 3) + 4 -
                    (infoGroup.infoHd2.biWidth * 3) % 4;
            smallHeight = infoGroup.infoHd2.biHeight;
            smallImage = (unsigned char *)malloc(infoGroup.infoHd2.biSizeImage);
            fread(smallImage, infoGroup.infoHd2.biSizeImage, 1, fileGroup.file2);*/
            fseek(bigAttributes->file, headGroup->fileHd1.bfOffBits, SEEK_SET);
	        fseek(smallAttributes->file, headGroup->fileHd2.bfOffBits, SEEK_SET);
            return 1;
        }		
        else {
            headGroup->finalFileHd = headGroup->fileHd2;
            infoGroup->finalInfoHd = infoGroup->infoHd2;
            setBigAttributes(bigAttributes, smallAttributes, headGroup, infoGroup, fileGroup, 0);
            fseek(bigAttributes->file, headGroup->fileHd2.bfOffBits, SEEK_SET);
	        fseek(smallAttributes->file, headGroup->fileHd1.bfOffBits, SEEK_SET);
            /*bigImage = (unsigned char *)malloc(infoGroup->infoHd2.biSizeImage);
            fread(bigImage, infoGroup->infoHd2.biSizeImage, 1, fileGroup->file2);
            smallImage = (unsigned char *)malloc(infoGroup->infoHd1.biSizeImage);
            fread(smallImage, infoGroup->infoHd1.biSizeImage, 1, fileGroup->file1);*/
            return 0;
        }
}