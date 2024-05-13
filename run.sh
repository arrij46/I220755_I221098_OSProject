#!/bin/bash

#clear 

# Compile main.c and link necessary libraries
gcc main.c -o Executable -lGL -lGLU -lglut

# Run the executable
./Executable
