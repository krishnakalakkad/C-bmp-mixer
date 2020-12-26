## C-bmp-mixer

# What is this project?

Like the title indicates, this program takes two bitmap images and blends them according to an input ratio. For examples, if the user took this bitmap image

![lion](https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/lion.png?raw=true)

and this image

![wolf](https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/wolf.png?raw=true)

and input these images into the mixer with a ratio of 0.5, the resulting output of the program would be this.

![lolf](https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/lolf.png?raw=true)


# How to use this program 

To compile the program, enter

`make`

into the terminal. To execute, enter

`./blend [imagefile1] [imagefile2] [ratio] [outputfile]`

Where `imagefile1` and `imagefile2` are the images you want to blend, `ratio` is the percentage of each image you want to blend (for example, a `ratio` of 0.7 would mean that the final image would be 70% of `imagefile1` and 30% of `imagefile2`),  and `outputfile` is the where you want to store your final result.


# Why I made this project and what I learned from it

I designed this program for my systems programming class. This project tested my foundations of allocated memory and data structures on the heap. I also learned how to implement bilinear interpolation such the program could blend images of different sizes seemlessly. 

## Challenges I faced

# Memory allocation

**The Problem**

When I was first taught about memory and using `malloc`, I would allocate small primitive data structures and, if I was feeling a little ambitious, a small paragraph of chars. That's why this project was so daunting. I couldn't just `fread()` all the information from the bitmap into the `filetagheader`, `infotagheader`, and the image data at one shot because I would always run into corruption problems.

**My approach**
I used pen and paper to draw what the memory allocated for the `filetagheader` looked like. I probably spent more time drawing what the memory looked like in front of a piece of paper than in my actual IDE. What I discovered was that there was a lot of padding within the filetagheader data structure, which is why the brutish method of trying to `fread()` all the data at one shot would not work. As such, I had to `fread()` every single primitive data structure in the `filetagheader`. At the same time, writing a bunch of `fread()` statements in my main makes the code hard to read for other contributers, and it makes debugging the code a pain. So decided to make a C file called `setUp.c`, and write a function called `void readEverything(FileHeaderGroup *headGroup, InfoHeaderGroup *infoGroup, FileGroup *fileGroup);` such that if there was an error that occurred during any one of the `fread`s, I could easily trace it back and set my breakpoints a lot more efficiently, whether I was in GDB or some other IDE. 

**Effects that this approach had on organization**
I applied this organization style of compartmentalizing functions into different C files, whick reduced my main function by over 300 lines. To do this, I had to pass many thing through reference, so I needed to create a lot of different data structures to organize all the data I had to keep track of. These are the supplementary data structures that helped me:



Compartmentalizing everything makes the debugging process much more transparent on all debugging applications because the backtrace from a debugging software shows the cause of the error much more clearly.

**What I gained from this experience**

Through this exercise I learned how deal with scanning and handling different media formats. While it is true that the BMP format is pretty obselete in a time where JPG, PNG, and TIFF files reign superior, I definitely improved my ability to visualize data structures that seem daunting and unfamiliar at first. In general, I feel that my ability to visualize how different functions like `fread()` handle data structures I initialize on the heap. 





