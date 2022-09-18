# Robot and marker abstraction

## About

***First project*** at university, right after covering material regarding C programming language. 

It is about displaying a robot using a simple algorithm to search for a marker around a grid in a rectangular area, while avoiding four obstacles in the form of blocks.

There are *two layers* that are displayed while running the program:

 - ***Background layer***, which displays the grid, as well as an immovable reflective marker (gray filled square) and blocks (red filled squares), which are both randomly positioned at the start of the program. 

- ***Foreground layer***, which displays the robot (green triangle) moving around the grid. 

The robot has *x* and *y* coordinates, as well as the *direction* he is pointed at, which can be either north, east, south or west.

## Guide

Supplied files:

- ***drawapp-2.0.jar*** is the Java program that reads the instructions and displays the picture as a result.

 - ***graphics.h*** and ***graphics.c*** are files that allow us to write programs in C, which output instructions for drawing pictures comprised of lines, rectangles and other included shapes.

Added files:

- ***Report.pdf*** describes the features of the program, as well as commands for executing it.

- ***gamefinal.c*** includes the C code for accomplishing the robot and marker abstraction.



