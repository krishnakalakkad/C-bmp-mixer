#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "blendTools.h"


unsigned char get(unsigned char *imageData, int x, int y, int width, char offset){
	return imageData[x*3 + y * width + offset];
}

void set(unsigned char *imageData, unsigned char val, int x, int y, int width, char offset){
	imageData[x*3 + y*width + offset] = val;
}

unsigned char getBlend(float argRatio, unsigned char val1, unsigned char val2){
	return argRatio * (val1) + (1 - argRatio) * (val2);
}

unsigned char getBilnrClr(int x_1, int x_2, int y_1, int y_2, 
		float dx, float dy, int width, unsigned char *smallImage, int offset){
	int leftUpper = get(smallImage, x_1, y_2, width, offset),
		rightUpper = get(smallImage, x_2, y_2, width, offset), 
		leftLower = get(smallImage, x_1, y_1, width, offset), 
		rightLower = get(smallImage, x_2, y_1, width, offset),
		left, right, result;
	left = leftUpper * (1 - dy) + leftLower * dy;
	right = rightUpper * (1 - dy) + rightLower * dy;
	result = left * (1 - dx) + right * dx;
	return result;
}