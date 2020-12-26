# C-bmp-mixer

## What is this project?

This program takes two bitmap images and blends them according to an input ratio. For example, if the user took bitmap images of a lion and a wolf and blended them with a 0.5 ratio using the program, the result would look like this:


| Image A | Image B | Blended @ 50% |
|------|-------| ------ |
| <img src="https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/lion.png?raw=true" align="center" width="300"> | <img src="https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/wolf.png?raw=true" align="center" width="300"> | <img src="https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/lolf.png?raw=true" align="center" width="300"> |


## Project Motivation & Goals

I designed this program for my systems programming class. This project tested my foundations of allocated memory and data structures on the heap. I also learned how to implement bilinear interpolation such that the program could blend images of different sizes seemlessly. 

## Challenges

### Memory allocation

Dynamic memory is set up in such a way that I couldn't `fread()` all the information from the bitmap into the `filetagheader` at one shot because I would always run into corruption problems.

### My approach

I discovered that there was a lot of padding within the filetagheader data structure, which is why the brutish method of trying to `fread()` all the data at one shot would not work. 

As such, I had to `fread()` every single primitive data structure in the `filetagheader`. At the same time, writing a several of `fread()` statements in my main makes the code hard to read for other contributers, and it makes debugging the code more difficult than it needs to be. Thus, I decided to make a C file called `setUp.c`, and write a function called `void readEverything();` such that if there was an error that occurred during any one of the `fread`s, I could easily trace it back and set my breakpoints a lot more efficiently, whether I was in GDB or some other IDE. 

Here is my `readEverything()` function.

```
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
```

#### Result
I applied this organization style of compartmentalizing functions across my entire program, and I organized my code in specific C and header files, which reduced my main function by over 300 lines. To do this, I had to pass many things through reference, so I needed to create different data structures to manage everything I had to pass by reference. These are the supplementary data structures that helped me accomplish this:

```
// Sample supplementary data stucture found in datastructures.h

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

```


Compartmentalizing everything makes the debugging process more transparent on all debugging applications because the backtrace from a debugging software shows the cause of the error much more clearly.

## Project Learnings

I improved my ability to visualize data structures that are unfamiliar with me. Whenever I come across a different media format, I always put importance on the visualization of dynamic memory and organization before attempting to write any code. In general, I feel that I improved my ability to visualize how different functions like `fread()` scan information into data structures allocated on the heap. 

## How to use this program 

To compile the program, enter

`make`

into the terminal. To execute, enter

`./blend [imagefile1] [imagefile2] [ratio] [outputfile]`

Where `imagefile1` and `imagefile2` are the images you want to blend, `ratio` is the percentage of each image you want to blend (for example, a `ratio` of 0.7 would mean that the final image would be 70% of `imagefile1` and 30% of `imagefile2`),  and `outputfile` is the where you want to store your final result.

