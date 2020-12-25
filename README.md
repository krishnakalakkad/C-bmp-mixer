## C-bmp-mixer

# What is this project?

Like the title indicates, this program takes two bitmap images and blends them according to an input ratio. For examples, if the user took this bitmap image

![lion](https://github.com/krishnakalakkad/C-bmp-mixer/blob/master/Screen Shot 2020-12-25 at 1.55.36 PM.png?raw=true)

and this image


wolf

and input these images into the mixer with a ratio of 0.5, the resulting output of the program would be this.

Test


# How to use this program 

To compile the program, enter

`make`

into the terminal. To execute, enter

`./blend [imagefile1] [imagefile2] [ratio] [outputfile]`

Where `imagefile1` and `imagefile2` are the images you want to blend, `ratio` is the percentage of each image you want to blend (for example, a `ratio` of 0.7 would mean that the final image would be 70% of `imagefile1` and 30% of `imagefile2`),  and `outputfile` is the where you want to store your final result.


# Why I made this project and what I learned from it

I designed this program for my systems programming class. This project truly tested my foundations of allocated memory and how it relates data structures on the heap. I also learned how to implement bilinear interpolation such that images of different ratios could be blended seemlessly
