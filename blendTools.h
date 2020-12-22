#ifndef BLENDTOOLS_H
#define BLENDTOOLS_H

//gets the RGB data from a pixel at (x,y)
unsigned char get(unsigned char *imageData, int x, int y, int width, char offset);


//sets teh RGB data for a pixel of the resulting image at (x,y)
void set(unsigned char *imageData, unsigned char val, int x, int y, int width, char offset);

//Blends two colors at a certain ratio
unsigned char getBlend(float argRatio, unsigned char val1, unsigned char val2);

//Gets the color of the bilinear result of 4 pixels (this is in case the pictures are not the same ratio)
unsigned char getBilnrClr(int x_1, int x_2, int y_1, int y_2, 
		float dx, float dy, int width, unsigned char *smallImage, int offset);

#endif