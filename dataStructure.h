#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int LONG;

typedef struct{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} tagBITMAPFILEHEADER;

typedef struct {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCOunt;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeters;
	DWORD biClrUsed;
	DWORD biClrImportant;
} tagBITMAPINFOHEADER;

typedef struct
{
    FILE* file1;
    FILE* file2;
    FILE* final;
} FileGroup;

typedef struct {
    tagBITMAPFILEHEADER fileHd1, fileHd2, finalFileHd;
} FileHeaderGroup;

typedef struct {
    tagBITMAPINFOHEADER infoHd1, infoHd2, finalInfoHd;
} InfoHeaderGroup;

typedef struct
{
    int width, height, padWidth, size;
	FILE* file;
} ImageAttributes;




#endif