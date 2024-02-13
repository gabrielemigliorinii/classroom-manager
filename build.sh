#!/bin/bash

# Build config
 cmake -S . -B build

# Project compile
cmake --build build

# Execute program
./build/debug/main ../../data/STUDENTS.dat ../../data/INDEX.dat 31

# Permission
#chmod +x build_and_run.sh

# Execution of this file
# ./build_and_run.sh