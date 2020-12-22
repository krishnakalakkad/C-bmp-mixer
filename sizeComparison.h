#ifndef SIZECOMPARISON_H
#define SIZECOMPARISON_H


void attributeInitializer(ImageAttributes *attributes, tagBITMAPINFOHEADER infoHd, FILE* fp);

void setBigAttributes(ImageAttributes *bigAttributes, ImageAttributes *smallAttributes,
    FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, FileGroup *fileGroup, int image);

int compareSizes(ImageAttributes *bigAttributes, ImageAttributes *smallAttributes, 
    FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, 
    FileGroup *fileGroup);


#endif