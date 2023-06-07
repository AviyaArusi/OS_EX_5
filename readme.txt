# Reactor Project README
This project is a demonstration of the ActiveObject pattern using C.


##Getting Started
To build and run the server application, follow the instructions below:

##Prerequisites
You will need a C compiler (preferably GCC or similar).

##Building the project
The project includes a Makefile for easy compilation. Simply run:

##make
This will generate the executable: st_pipeline

##Running the st_pipeline
After successfully building the project, you can run it with the following command:

You can run it with or without the seed, if you don't insert it the seed will be time(NULL) by defulate.

./st_pipeline N(int) seed(int)  or ./st_pipeline N(int)


##Cleaning up
To clean up the generated files, you can run:

make clean
This command will delete the st_pipeline executable.
